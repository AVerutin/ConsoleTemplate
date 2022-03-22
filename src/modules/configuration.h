#ifndef LEVEL15_CONFIGURATION_H
#define LEVEL15_CONFIGURATION_H

#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "logger.h"
#include "connectionparams.h"

class Configuration
{
public:
    Configuration();
    ~Configuration();
    [[nodiscard]] std::shared_ptr<ConnectionParams> mysqlParams() const;
    [[nodiscard]] std::shared_ptr<ConnectionParams> postgresqlParams() const;
    [[nodiscard]] int timeout() const;
    [[nodiscard]] int waiting() const;
    [[nodiscard]] int difference() const;
    [[nodiscard]] std::string last_clear() const;
    [[nodiscard]] int minutes_rewind() const;
    void set_clear(std::string_view time_start);

private:
    std::shared_ptr<Logger> m_logger;
    std::shared_ptr<ConnectionParams> m_mysqlParams;
    std::shared_ptr<ConnectionParams> m_postgresqlParams;
    int m_timeout;
    int m_waiting;
    int m_difference;
    std::string m_lastClear;
    int m_minutesRewind;
};


#endif //LEVEL15_CONFIGURATION_H
