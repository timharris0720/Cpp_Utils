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
	inline bool writeToLogFile_Global = true;
	inline std::string FileStartPath = "";

	inline void InitWkd(){
		char path[1024]; 
		getcwd(path, sizeof(path));

		Log::FileStartPath = path;
	}
	inline void Debug(const char* fmt,const char* path, ...){
		#ifndef NDEBUG
		std::string newP;
		if (path == nullptr || std::strlen(path) == 0) {
			newP = std::string(FileStartPath + "/Log.txt").c_str();
		}
		else{
			newP = std::string(FileStartPath + "/" + path).c_str();
		}

		std::cout << path << std::endl;
		#ifdef WIN32
		
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				WORD originalAttributes = csbi.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "[ DEBUG : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
				
				SetConsoleTextAttribute(hConsole, originalAttributes);
		#else
		
				std::cout << "\033[32;1m [ DEBUG : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";
		
		#endif //_WIN32
		
		va_list args;
		va_start(args, newP.c_str());

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);
		



		if (Log::writeToLogFile_Global == true) {
			FILE* file = fopen(newP.c_str(), "a");
			if (!file) {
				printf("Failed to open log file: %s\n", newP.c_str());
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
	
		#endif // DEBUG
				
		
	}
	inline void Error(const char* fmt, const char* path, ...) {
		std::string newP;
		if (path == nullptr || std::strlen(path) == 0) {
			newP = std::string(FileStartPath + "/Log.txt").c_str();
		}
		else{
			newP = std::string(FileStartPath + "/" + path).c_str();
		}
	#ifdef WIN32
	
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		WORD originalAttributes = csbi.wAttributes;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "[ ERROR : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
	#else
	
		std::cout << "\033[31;1m [ ERROR : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";

	#endif
	
		va_list args;
		va_start(args, newP.c_str());

		std::string line = std::string(fmt);
		line += "\n";

		vprintf(line.c_str(), args);
		



		if (Log::writeToLogFile_Global == true) {
			FILE* file = fopen(newP.c_str(), "a");
			if (!file) {
				printf("Failed to open log file: %s\n", newP.c_str());
				return;
			}
			vfprintf(file, line.c_str(), args);
			fclose(file);
		}
		va_end(args);
		
		}
	inline void Info(const char* fmt,const char* path, ...) {
		std::string newP;
		if (path == nullptr || std::strlen(path) == 0) {
			newP = std::string(FileStartPath + "/Log.txt").c_str();
		}
		else{
			newP = std::string(FileStartPath + "/" + path).c_str();
		}

		#ifdef WIN32

				CONSOLE_SCREEN_BUFFER_INFO csbi;
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo(hConsole, &csbi);
				WORD originalAttributes = csbi.wAttributes;
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				std::cout << "[ INFO : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
				SetConsoleTextAttribute(hConsole, originalAttributes);
		#else

				std::cout << "\033[34;1m: [ INFO : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";
				
		#endif
				va_list args;
				va_start(args, newP.c_str());

				std::string line = std::string(fmt);
				line += "\n";

				vprintf(line.c_str(), args);
				



				if (Log::writeToLogFile_Global == true) {
					FILE* file = fopen(newP.c_str(), "a");
					if (!file) {
						printf("Failed to open log file: %s\n", newP.c_str());
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
	std::string logPath = "";
	void writeFile(std::string fileData, std::string path) {			
	
		std::ofstream file(path, std::ios::app);

		file << fileData + "\n";
		file.close();
	}

public:
	Logger() = default;
	Logger(std::string loggerName, std::string pathLogFile = "Log.txt", bool fileLog = true, std::string exeLocation = "") {
		LoggerName = loggerName;
		LogFile=pathLogFile;
		logPath = exeLocation;
		LogToFile = fileLog;

		if (LogFile.c_str() == nullptr || std::strlen(LogFile.c_str()) == 0) {
			LogFile = std::string(logPath + "/Log.txt").c_str();
		}
		else{
			LogFile = std::string(logPath +  "/" + LogFile).c_str();
		}

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
		std::cout << "[ DEBUG : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[32;1m [ DEBUG : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";

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
		std::cout << "[ ERROR : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[31;1m [ ERROR : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";

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
		std::cout << "[ INFO : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : ";
		SetConsoleTextAttribute(hConsole, originalAttributes);
#else

		std::cout << "\033[34;1m [ INFO : " + Time::getDate_DD_MM_YYYY() + " -  " + Time::GetTime_HH_MM_SS_MMM() + " ] : \033[0m";

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