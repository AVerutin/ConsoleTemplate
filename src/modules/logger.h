#ifndef MTSDB_LOGGER_H
#define MTSDB_LOGGER_H

#include <fstream>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <chrono>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <boost/property_tree/ini_parser.hpp>
#include "definitions.h"

class Logger
{
public:
    explicit Logger(std::string_view unitName);
    ~Logger();
    void debug(std::string_view message) const;
    void info(std::string_view message) const;
    void warning(std::string_view message) const;
    void error(std::string_view message) const;
private:
    void readParameters();
    [[nodiscard]] int logLevel() const;
    void writeMessage(std::string_view message, LogType logType) const;
    [[nodiscard]] std::string logName() const;
    void clearLogs() const;

    std::string m_unitName;
    int m_fileAge;
    LogType m_logLevel;
};

#endif //MTSDB_LOGGER_H
