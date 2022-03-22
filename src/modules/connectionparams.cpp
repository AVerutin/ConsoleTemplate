#include "connectionparams.h"

ConnectionParams::ConnectionParams() :
    m_dbHost{},
    m_dbPort{0},
    m_dbName{},
    m_dbUser{},
    m_dbPass{}
{
}

ConnectionParams::ConnectionParams(std::string_view host, int port, std::string_view database, std::string_view user,
                                   std::string_view password)
{
    this->m_dbHost = host;
    this->m_dbPort = port >= 0 ? port : 0;
    this->m_dbName = database;
    this->m_dbUser = user;
    this->m_dbPass = password;
}

ConnectionParams::~ConnectionParams() = default;


std::string ConnectionParams::host() const
{
    return this->m_dbHost;
}


int ConnectionParams::port() const
{
    return this->m_dbPort;
}


std::string ConnectionParams::database() const
{
    return this->m_dbName;
}


std::string ConnectionParams::user() const
{
    return this->m_dbUser;
}


std::string ConnectionParams::password() const
{
    return this->m_dbPass;
}


void ConnectionParams::host(std::string_view hostName)
{
    this->m_dbHost = hostName;
}


void ConnectionParams::port(int port)
{
    this->m_dbPort = port >= 0 ? port : 0;
}


void ConnectionParams::database(std::string_view database)
{
    this->m_dbName = database;
}


void ConnectionParams::user(std::string_view userName)
{
    this->m_dbUser = userName;
}


void ConnectionParams::password(std::string_view password)
{
    this->m_dbPass = password;
}
