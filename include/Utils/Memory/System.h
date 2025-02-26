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
    #include "Strings/stringOps.h"
    using PID_TYPE = DWORD;
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
    uintptr_t ScanMemory(PID_TYPE pid, uintptr_t start, uintptr_t end, T value) {
        const size_t chunkSize = 4096;  // Read memory in chunks
        std::vector<char> buffer(chunkSize);

        for (uintptr_t addr = start; addr < end; addr += chunkSize) {
            if (ReadMemory(pid, addr, buffer)) {
                for (size_t i = 0; i < chunkSize - sizeof(T); i++) {
                    T* data = reinterpret_cast<T*>(&buffer[i]);
                    if (*data == value) {
                        return addr + i;
                    }
                }
            }
        }
        return 0;
    }
    PROCESS GetProcessID(const std::string& processName) {
        #ifdef _WIN32
        int pid = 0;
        PROCESS proc;
        WTS_PROCESS_INFOA* proc_info;
        DWORD pi_count = 0;
        if (!WTSEnumerateProcessesA(WTS_CURRENT_SERVER_HANDLE, 0, 1, &proc_info, &pi_count))
            return proc;

        for (int i = 0; i < pi_count; i++) {
            if (lstrcmpiA(processName.c_str(), proc_info[i].pProcessName) == 0) {
                proc.Found = true;
                proc.ProcessID = proc_info[i].ProcessId;
                proc.processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.ProcessID);
                break;
            }
        }
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
        return PROCESS{};  // Process not found
    }
}