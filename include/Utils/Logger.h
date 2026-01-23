#pragma once
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>
#include <fstream>
#include <direct.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include "Time.h"
#include "Strings.h"

namespace Log {
    namespace LogGlobals {
        inline bool writeToLogFile_Global = true;
	    inline std::string FileStartPath = "";  
	    inline std::string path = FileStartPath + "/Log.txt";  

        enum class LogType {
            Debug,
            Info,
            Error
        };

        #ifdef WIN32
        static WORD GetColor(LogType type) {
            switch (type) {
                case LogType::Error: return FOREGROUND_RED | FOREGROUND_INTENSITY;
                case LogType::Info:  return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                case LogType::Debug: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
            return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
        #else
        static const char* GetColor(LogType type) {
            switch (type) {
                case LogType::Error: return "\033[31;1m";
                case LogType::Info:  return "\033[32;1m";
                case LogType::Debug: return "\033[34;1m";
            }
            return "\033[0m";
        }
        #endif


        inline void InitWorkingDir(){
            char m_path[1024]; 
            getcwd(m_path, sizeof(m_path));

            FileStartPath = m_path;
        }
        inline void SetLoggingFile(std::string _path){
            path = FileStartPath + "/" + _path;
        }

        inline void PrintBase(LogType type,  const char* fmt, va_list args){
            
             // Format message
            char buffer[4096];
            vsnprintf(buffer, sizeof(buffer), fmt, args);

            std::string timeStr = Time::getDate_DD_MM_YYYY() + " - " + Time::GetTime_HH_MM_SS_MMM();

            const char* typeStr =
                (type == LogType::Error) ? "ERROR" :
                (type == LogType::Info)  ? "INFO"  : "DEBUG";

            std::string finalLine = "[ " + std::string(typeStr) + " : " + timeStr + " ] : " + buffer + "\n";

            // ---- Console output ----
        #ifdef WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hConsole, &csbi);

            SetConsoleTextAttribute(hConsole, GetColor(type));
            std::cout << finalLine;
            SetConsoleTextAttribute(hConsole, csbi.wAttributes);
        #else
            std::cout << GetColor(type) << finalLine << "\033[0m";
        #endif

            // ---- File output ----
            if (writeToLogFile_Global) {
                FILE* file = fopen(path.c_str(), "a");
                if (file) {
                    fputs(finalLine.c_str(), file);
                    fclose(file);
                }
            }
        }
    }

    void ErrorLog(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogGlobals::PrintBase(LogGlobals::LogType::Error, fmt, args);
        va_end(args);
    }
    void InfoLog(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogGlobals::PrintBase(LogGlobals::LogType::Info, fmt, args);
        va_end(args);
    }
    void DebugLog(const char* fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        LogGlobals::PrintBase(LogGlobals::LogType::Debug, fmt, args);
        va_end(args);
    }
}