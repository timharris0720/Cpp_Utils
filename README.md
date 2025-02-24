# Cpp_UTILS

## Available Utils

### Logger

```cpp

#include <Utils/Logger.h>

Logger logger = Logger("name", "logFilePath", true);

// Info Log
logger.InfoLog("THIS IS A LOG");

// Info Log with format
logger.InfoLog("THIS IS A LOG my name is %s", logger.getLoggerName());

```

### File Writing

```cpp

#include <Utils/FileIO.h> // Includes both write and read files
//#include <Utils/FileIO/Write.h>  Includes read only
FileIO::WriteFile(filename, stringData); // Append - default
FileIO::WriteFile(filename, stringData, FileIO::Overwrite); // Overwrite a file

std::vector<char> data = {'H', 'e', 'l', 'l', 'o', 0, 'B', 'i', 'n', 'a', 'r', 'y'};
FileIO::WriteFile_Binary(filename, data, WriteType::Overwrite); // Overwrite a binary file

std::vector<char> additionalData = {'!', '!', '!', 0};
FileIO::WriteFile_Binary(filename, additionalData, WriteType::Append); // Append to a binary file

```

### File Reading

```cpp

#include <Utils/FileIO.h> // Includes both write and read files
#include <Utils/FileIO/Read.h> // Includes read only
'''
To read certain parts of a file use the memory headers and their functions for reading files, specific to binary related tasks and have more read options
'''
std::vector<char> fileContent = FileIO::readFileBinary(filename); // read a whole binary file 
std::string fileContent_String = FileIO::readFile(filename);

```
