#include "configuration.h"

Configuration::Configuration() :
    m_logger{nullptr},
    m_mysqlParams{nullptr},
    m_postgresqlParams{nullptr}
{
    this->m_logger = std::make_shared<Logger>("Configuration");

    // Получение имени файла с параметрами подключения к БД
    boost::property_tree::ptree pt;
    auto full_path = std::filesystem::current_path();
    std::string path = full_path.string() + "\\config.ini";

    // Чтение параметров подключения к БД из файла
    try
    {
        boost::property_tree::ini_parser::read_ini(path, pt);
    }
    catch (boost::property_tree::ini_parser::ini_parser_error& err)
    {
        std::string msg = "Не удалось прочитать параметры [" + err.message() + "]";
        this->m_logger->error(msg);
        return;
    }

    // Формирование строки подключения к БД MySQL
    auto host = pt.get<std::string>("Level15.host");
    auto port = std::stoi(pt.get<std::string>("Level15.port"));
    auto database = pt.get<std::string>("Level15.database");
    auto user = pt.get<std::string>("Level15.username");
    auto password = pt.get<std::string>("Level15.password");
    this->m_mysqlParams = std::make_shared<ConnectionParams>(host, port, database, user, password);

    // Формирование строки подключения к БД PostgreSQL
    host = pt.get<std::string>("Espc.host");
    port = std::stoi(pt.get<std::string>("Espc.port"));
    database = pt.get<std::string>("Espc.database");
    user = pt.get<std::string>("Espc.username");
    password = pt.get<std::string>("Espc.password");
    this->m_postgresqlParams = std::make_shared<ConnectionParams>(host, port, database, user, password);

    // Параметры оценки соответствия расхода материалов
    this->m_waiting = std::stoi(pt.get<std::string>("Evaluating.waiting"));
    this->m_difference = std::stoi(pt.get<std::string>("Evaluating.time_difference"));


    this->m_timeout = std::stoi(pt.get<std::string>("Clear.timeout"));
    this->m_lastClear = pt.get<std::string>("Clear.previous");
    this->m_minutesRewind = std::stoi(pt.get<std::string>("Clear.minutes_rewind"));
}


int Configuration::timeout() const
{
    return this->m_timeout;
}


std::string Configuration::last_clear() const
{
    return this->m_lastClear;
}


void Configuration::set_clear(std::string_view time_start)
{
    // Получение имени файла с параметрами подключения к БД
    boost::property_tree::ptree pt;
    auto full_path = std::filesystem::current_path();
    std::string path = full_path.string() + "\\config.ini";

    // Чтение параметров подключения к БД из файла
    try
    {
        boost::property_tree::ini_parser::read_ini(path, pt);
    }
    catch (boost::property_tree::ini_parser::ini_parser_error& err)
    {
        std::string msg = "Не удалось прочитать параметры [" + err.message() + "]";
        this->m_logger->error(msg);
        return;
    }

    try
    {
        pt.put("Clear.previous", time_start);
        boost::property_tree::ini_parser::write_ini(path, pt);
    }
    catch (boost::property_tree::ptree_bad_data& err)
    {
        std::string msg = "Не удалось установить время предыдущей очистки [";
        msg.append(err.what());
        msg.append("]");
        this->m_logger->error(msg);
        return;
    }

    // Установим время последней проверки
    this->m_lastClear = time_start;
}


int Configuration::minutes_rewind() const
{
    return this->m_minutesRewind;
}


std::shared_ptr<ConnectionParams> Configuration::postgresqlParams() const
{
    return this->m_postgresqlParams;
}


std::shared_ptr<ConnectionParams> Configuration::mysqlParams() const
{
    return this->m_mysqlParams;
}


int Configuration::waiting() const
{
    return this->m_waiting;
}


int Configuration::difference() const
{
    return this->m_difference;
}


Configuration::~Configuration() = default;
