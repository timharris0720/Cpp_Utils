#pragma once
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#endif

bool WriteLogFile = true;

class Logger {
private:
    std::string LogFile;
    bool LogToFile = false;
    std::string InfoLogTitle;
    std::string DebuLogTitle;
    std::string ErroLogTitle;
	std::string LoggerName;
	
	void writeFile(std::string fileData, std::string path) {			
    
        std::ofstream file(path, std::ios::app);

        file << fileData + "\n";
        file.close();
	}

public:
    Logger() = default;
    Logger(std::string loggerName, std::string pathLogFile, bool fileLogging = true) {LoggerName = loggerName;LogFile=pathLogFile; InfoLogTitle = "[ INFO | " + LoggerName + "] : "; DebuLogTitle = "[ DEBUG | " + LoggerName + "] : "; ErroLogTitle = "[ ERROR | " + LoggerName + "] : ";LogToFile = fileLogging;}
    void ToggleFileLogging(){
        LogToFile = !LogToFile;
		WriteLogFile  = LogToFile;
    }
    void ToggleFileLogging(bool decider){
        LogToFile = decider;
		WriteLogFile  = LogToFile;
    }
	void setLoggerName(std::string name_){
		LoggerName = name_;
		InfoLogTitle = "[ INFO | " + LoggerName + "] : "; DebuLogTitle = "[ DEBUG | " + LoggerName + "] : "; ErroLogTitle = "[ ERROR | " + LoggerName + "] : ";
	}
	std::string getLoggerName(){
		return LoggerName;
	}
    void DebugLog(const char* fmt, ...) {
#ifndef NDEBUG
#ifdef WIN32

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << DebuLogTitle;
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[32;1m" << DebuLogTitle << " \033[0m";

#endif //_WIN32

		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		
		va_end(args);
		

		// Return the formatted string as a std::string
		std::cout << std::endl;
		if (LogToFile == true) {
			va_list args;
			va_start(args, fmt);

			// Determine the size of the formatted string
			size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;  // Include space for '\0'
			va_end(args);  // Reset va_list for the second use

			// Allocate the necessary buffer in a C++ std::string
			std::vector<char> buffer(size);
			va_start(args, fmt);  // Restart the variadic argument list
			std::vsnprintf(buffer.data(), size, fmt, args);  // Format the string into the buffer
			va_end(args);

			writeFile(DebuLogTitle + std::string(buffer.data()), LogFile);
		}
	
#endif // DEBUG
		

	}
	void ErrorLog(const char* fmt, ...) {
#ifdef WIN32

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ErroLogTitle ;
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[31;1m" << ErroLogTitle << "\033[0m";

#endif

		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
		std::cout << std::endl;

		if (LogToFile == true) {
			va_list args;
			va_start(args, fmt);

			// Determine the size of the formatted string
			size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;  // Include space for '\0'
			va_end(args);  // Reset va_list for the second use

			// Allocate the necessary buffer in a C++ std::string
			std::vector<char> buffer(size);
			va_start(args, fmt);  // Restart the variadic argument list
			std::vsnprintf(buffer.data(), size, fmt, args);  // Format the string into the buffer
			va_end(args);

			writeFile(ErroLogTitle + std::string(buffer.data()), LogFile);
		}
	}
	void InfoLog(const char* fmt, ...) {
        
#ifdef WIN32

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << InfoLogTitle;
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[34;1m:" << InfoLogTitle << "\033[0m";

#endif

		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
		std::cout << std::endl;

		if (LogToFile == true) {
			va_list args;
			va_start(args, fmt);
			size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;
			va_end(args);
			std::vector<char> buffer(size);
			va_start(args, fmt);
			std::vsnprintf(buffer.data(), size, fmt, args); 
			va_end(args);

			writeFile(InfoLogTitle + std::string(buffer.data()), LogFile);
		}
	}
};