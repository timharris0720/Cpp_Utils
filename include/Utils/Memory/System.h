#pragma once
#include <iostream>
#include <vector>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
    using PID_TYPE = DWORD;
#else
    #include <sys/ptrace.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <sys/uio.h>  // For process_vm_readv/process_vm_writev
    using PID_TYPE = pid_t;
#endif
namespace Memory {
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
}