#ifndef LEVEL15_CONNECTIONPARAMS_H
#define LEVEL15_CONNECTIONPARAMS_H

#include <string>

class ConnectionParams
{
public:
    explicit ConnectionParams();
    explicit ConnectionParams(std::string_view host,
                              int port,
                              std::string_view database,
                              std::string_view user,
                              std::string_view password);
    ~ConnectionParams();
    [[nodiscard]] std::string host() const;
    [[nodiscard]] int port() const;
    [[nodiscard]] std::string database() const;
    [[nodiscard]] std::string user() const;
    [[nodiscard]] std::string password() const;
    void host(std::string_view hostName);
    void port(int port);
    void database(std::string_view database);
    void user(std::string_view userName);
    void password(std::string_view password);

private:
    std::string m_dbHost;
    int m_dbPort;
    std::string m_dbName;
    std::string m_dbUser;
    std::string m_dbPass;
};


#endif //LEVEL15_CONNECTIONPARAMS_H
