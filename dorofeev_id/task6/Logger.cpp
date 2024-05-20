#include "Logger.h"

Logger::Logger(const std::string& filename) 
{
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile) 
    {
        throw std::runtime_error("Error opening log file.");
    }
}

Logger::~Logger() 
{
    if (logFile.is_open()) 
    {
        logFile.close();
    }
}

void Logger::log(const std::string& message) 
{
    logFile << message << std::endl;
}
