#pragma once
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <string>
#include <fstream>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "Strings.h"
namespace Log {
	inline bool writeToLogFile_Global = true;
	


	inline void Debug(const char* fmt,const char* path, ...) {
		#ifndef NDEBUG
		#ifdef WIN32
		
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				WORD originalAttributes = csbi.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "[ DEBUG ] : ";
				
				SetConsoleTextAttribute(hConsole, originalAttributes);
		#else
		
				std::cout << "\033[32;1m [ DEBUG ] : \033[0m";
		
		#endif //_WIN32
		
		va_list args;
		va_start(args, path);

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);
		



		if (Log::writeToLogFile_Global == true) {
			FILE* file = fopen(path, "a");
			if (!file) {
				printf("Failed to open log file: %s\n", path);
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
	
		#endif // DEBUG
				
		
	}
	inline void Error(const char* fmt, const char* path, ...) {

		if (path == nullptr || std::strlen(path) == 0) {
			path = "Log.txt";
		}
	#ifdef WIN32
	
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "[ ERROR ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
	#else
	
		std::cout << "\033[31;1m [ ERROR ] : \033[0m";

	#endif
	
		va_list args;
		va_start(args, path);

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);
		



		if (Log::writeToLogFile_Global == true) {
			FILE* file = fopen(path, "a");
			if (!file) {
				printf("Failed to open log file: %s\n", path);
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
		
		}
	inline void Info(const char* fmt,const char* path, ...) {
		if (path == nullptr || std::strlen(path) == 0) {
			path = "Log.txt";
		}
		#ifdef WIN32

				CONSOLE_SCREEN_BUFFER_INFO csbi;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				WORD originalAttributes = csbi.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << "[ INFO ] : ";
				SetConsoleTextAttribute(hConsole, originalAttributes);
		#else

				std::cout << "\033[34;1m: [ INFO ] : \033[0m";
				
		#endif
				va_list args;
				va_start(args, path);

				std::string line = std::string(fmt);
				line += "\n";

				vprintf(line.c_str(), args);
				



				if (Log::writeToLogFile_Global == true) {
					FILE* file = fopen(path, "a");
					if (!file) {
						printf("Failed to open log file: %s\n", path);
						return;
					}
					vfprintf(file, line.c_str(), args);
					fclose(file);
				}
				va_end(args);
	}
}


class Logger {
private:
	std::string LogFile;
	bool LogToFile = false;
	std::string LoggerName;
	
	void writeFile(std::string fileData, std::string path) {			
	
		std::ofstream file(path, std::ios::app);

		file << fileData + "\n";
		file.close();
	}

public:
	Logger() = default;
	Logger(std::string loggerName, std::string pathLogFile = "Log.txt", bool fileLog = true) {
		LoggerName = loggerName;
		LogFile=pathLogFile;
		LogToFile = fileLog;
	}
	void ToggleFileLog(){
		LogToFile = !LogToFile;
	}
	void ToggleFileLog(bool decider){
		LogToFile = decider;
	}
	void setLoggerName(std::string name_){
		LoggerName = name_;
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
		std::cout << "[ DEBUG ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[32;1m [ DEBUG ] : \033[0m";

#endif //_WIN32

		va_list args;
		va_start(args, fmt);

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);




		if (LogToFile == true || Log::writeToLogFile_Global == true) {
			FILE* file = fopen(LogFile.c_str(), "a");
			if (!file) {
				printf("Failed to open log file: %s\n", LogFile.c_str());
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
			
#endif // DEBUG
		

	}
	void ErrorLog(const char* fmt, ...) {
#ifdef WIN32

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "[ ERROR ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[31;1m [ ERROR ] : \033[0m";

#endif

		va_list args;
		va_start(args, fmt);

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);




		if (LogToFile == true || Log::writeToLogFile_Global == true) {
			FILE* file = fopen(LogFile.c_str(), "a");
			if (!file) {
				printf("Failed to open log file: %s\n", LogFile.c_str());
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
	}
	void InfoLog(const char* fmt, ...) {
		
#ifdef WIN32

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << "[ ERROR ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[34;1m [ ERROR ] : \033[0m";

#endif

		va_list args;
		va_start(args, fmt);

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);




		if (LogToFile == true || Log::writeToLogFile_Global == true) {
			FILE* file = fopen(LogFile.c_str(), "a");
			if (!file) {
				printf("Failed to open log file: %s\n", LogFile.c_str());
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
	}

};