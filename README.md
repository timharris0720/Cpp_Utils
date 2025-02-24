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
//#include <Utils/FileIO/Read.h> // Includes read only
//#include <Utils/FileIO/Write.h>  Includes read only

```
