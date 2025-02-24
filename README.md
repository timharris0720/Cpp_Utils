# Cpp_UTILS

## Available Utils

### Logger

```cpp

#include <Utils/Logger.h>

Logger logger = Logger("name", "logFilePath", true);

// Info Log
logger.InfoLog("THIS IS A LOG")

// Info Log with format
logger.InfoLog("THIS IS A LOG my name is %s", logger.getLoggerName())

```
