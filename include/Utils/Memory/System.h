#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <stdio.h>
    #include <psapi.h>
    #include <wtsapi32.h>
    #include <winuser.h>
    #include <tlhelp32.h>
    #include <stdio.h>
    #include <iostream>
    #include <string>
    #include <tchar.h>
    #include <string_view>
    #include "Strings/Strings.h"
    using PID_TYPE = DWORD;
    #pragma comment(lib, "Wtsapi32.lib")
#else
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <cstring>
    #include <fstream>
    #include <unistd.h>
    #include <sys/uio.h>  // For process_vm_readv/process_vm_writev
    using PID_TYPE = pid_t;
#endif
namespace Memory {
    struct PROCESS {
        bool Found = false;
        HANDLE processHandle = NULL;
        UINT64 ModuleAddrs = 0;
        int ProcessID = 0;
    };


    template <typename T>
    bool ReadMemory(PID_TYPE pid, uintptr_t address, T& buffer) {
    #ifdef _WIN32
        HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
        if (!hProcess) {
            std::cerr << "[ERROR] OpenProcess failed: " << GetLastError() << std::endl;
            return false;
        }
    
        SIZE_T bytesRead;
        if (!ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), &bytesRead)) {
            std::cerr << "[ERROR] ReadProcessMemory failed: " << GetLastError() << std::endl;
            CloseHandle(hProcess);
            return false;
        }
    
        CloseHandle(hProcess);
    #else
        struct iovec local[1];
        struct iovec remote[1];
    
        local[0].iov_base = &buffer;
        local[0].iov_len = sizeof(T);
        remote[0].iov_base = (void*)address;
        remote[0].iov_len = sizeof(T);
    
        if (process_vm_readv(pid, local, 1, remote, 1, 0) == -1) {
            std::cerr << "[ERROR] process_vm_readv failed!" << std::endl;
            return false;
        }
    #endif
        return true;
    }
    template <typename T>
    bool WriteMemory(PID_TYPE pid, uintptr_t address, const T& buffer) {
    #ifdef _WIN32
        HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
        if (!hProcess) {
            std::cerr << "[ERROR] OpenProcess failed: " << GetLastError() << std::endl;
            return false;
        }
    
        SIZE_T bytesWritten;
        if (!WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(T), &bytesWritten)) {
            std::cerr << "[ERROR] WriteProcessMemory failed: " << GetLastError() << std::endl;
            CloseHandle(hProcess);
            return false;
        }
    
        CloseHandle(hProcess);
    #else
        struct iovec local[1];
        struct iovec remote[1];
    
        local[0].iov_base = (void*)&buffer;
        local[0].iov_len = sizeof(T);
        remote[0].iov_base = (void*)address;
        remote[0].iov_len = sizeof(T);
    
        if (process_vm_writev(pid, local, 1, remote, 1, 0) == -1) {
            std::cerr << "[ERROR] process_vm_writev failed!" << std::endl;
            return false;
        }
    #endif
        return true;
    }

    template <typename T>
    std::vector<uintptr_t> ScanProcessMemory(DWORD processID, T targetValue) {
        std::vector<uintptr_t> foundAddresses;
        #ifdef _WIN32
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    
        if (!hProcess) {
            std::cerr << "[ERROR] Failed to open process! Error: " << GetLastError() << std::endl;
            return foundAddresses;
        }
    
        MEMORY_BASIC_INFORMATION mbi;
        unsigned char* address = nullptr;  // Start at NULL and iterate through memory
    
        while (VirtualQueryEx(hProcess, address, &mbi, sizeof(mbi))) {
            if (mbi.State == MEM_COMMIT && (mbi.Protect & PAGE_READWRITE)) {
                std::vector<T> buffer(mbi.RegionSize / sizeof(T));
    
                SIZE_T bytesRead;
                if (ReadProcessMemory(hProcess, address, buffer.data(), mbi.RegionSize, &bytesRead)) {
                    for (size_t i = 0; i < bytesRead / sizeof(T); i++) {
                        if (buffer[i] == targetValue) {
                            uintptr_t foundAddress = reinterpret_cast<uintptr_t>(address + i * sizeof(T));
                            foundAddresses.push_back(foundAddress);
                            //std::cout << "[FOUND] Value " << targetValue << " at address: " << std::hex << foundAddress << std::endl;
                        }
                    }
                }
            }
            address += mbi.RegionSize;  // Move to the next region
        }
    
        CloseHandle(hProcess);
        #endif
        return foundAddresses;
    }
    uintptr_t GetModuleAddress(const char* procname, DWORD dwProcID) noexcept
    {
        uintptr_t ModuleBaseAddress = 0;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            MODULEENTRY32 ModuleEntry32;
            ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

            if (Module32First(hSnapshot, &ModuleEntry32))
            {
                do
                {
                    if (lstrcmpiA(procname, (LPCSTR)ModuleEntry32.szModule) == 0)
                    {
                        ModuleBaseAddress = (uintptr_t)ModuleEntry32.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnapshot, &ModuleEntry32));
            }
            CloseHandle(hSnapshot);
        }
        return ModuleBaseAddress;


    }
    PID_TYPE GetProcessID(const char* procname) {
        #ifdef _WIN32
            int pid = 0;
            WTS_PROCESS_INFOA* proc_info;
            DWORD pi_count = 0;
            if (!WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &proc_info, &pi_count))
                return 0;
        
            for (int i = 0; i < pi_count; i++) {
                if (lstrcmpiA(procname, proc_info[i].pProcessName) == 0) {
                    pid = proc_info[i].ProcessId;
                    break;
                }
            }
            return pid;
        
        #else
            DIR* dir = opendir("/proc");
            if (!dir) {
                std::cerr << "[ERROR] Failed to open /proc directory!" << std::endl;
                return 0;
            }
        
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (!isdigit(entry->d_name[0])) continue;  // Ignore non-numeric entries (not PIDs)
        
                std::string pid = entry->d_name;
                std::ifstream cmdline("/proc/" + pid + "/cmdline");
                std::string cmd;
                std::getline(cmdline, cmd, '\0');  // Read first argument (executable path)
        
                if (cmd.find(processName) != std::string::npos) {
                    closedir(dir);
                    return std::stoi(pid);
                }
            }
        
            closedir(dir);
        #endif
        return 0;  // Process not found
    }
}