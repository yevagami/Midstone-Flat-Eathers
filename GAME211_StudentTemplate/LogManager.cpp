#include "LogManager.h"
#include <cstdio> // for sprintf
#include <ctime>  // for time_t, struct tm
#include <iomanip>
#include <chrono>
#include <sstream>

const char* LogManager::createLogFileDir() {
    string dateAndTime = giveDateTimeString();
    ostringstream formattedFileDir;
   
    formattedFileDir 
        << logFileDir << " " 
        << dateAndTime 
        << fileExtension;

    return formattedFileDir.str().c_str();
}

bool LogManager::logTo(string content, const char* fileDirectory) {
    if (fileCreate(fileDirectory)) {
        fileInsert(content, fileDirectory);
        return true;
    }
    else {
        return false;
    }
}

bool LogManager::logToFile(std::string content) {
    if (logTo(content, createLogFileDir())) {
        return true; }

    return false;
}


string LogManager::giveDateTimeString() {
    auto now = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::to_time_t(now);
    struct tm timeInfo;

    localtime_s(&timeInfo, &currentTime);
    
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

    return std::string(buffer);
}
