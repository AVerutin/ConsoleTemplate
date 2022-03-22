#include <iostream>
#include "logger.h"

Logger::Logger(std::string_view unitName) :
    m_unitName{unitName},
    m_fileAge{0},
    m_logLevel{LogType::Default}
{
    this->readParameters();
}

Logger::~Logger() = default;

/**
 * Вывод отладочного сообщения в файл.
 * @param msg Текст сообщения.
 */
void Logger::debug(std::string_view msg) const
{
    if (!msg.empty() && this->logLevel() & static_cast<int>(LogType::Debug))
        writeMessage(msg, LogType::Debug);
}

/**
 * Вывод информационного сообщения
 * @param msg Текст сообщения
 */
void Logger::info(std::string_view msg) const
{
    if (!msg.empty() && this->logLevel() & static_cast<int>(LogType::Information))
        writeMessage(msg, LogType::Information);
}

/**
 * Вывод предупреждающего сообщения
 * @param msg Текст сообщения
 */
void Logger::warning(std::string_view msg) const
{
    if (!msg.empty() && this->logLevel() & static_cast<int>(LogType::Warning))
        writeMessage(msg, LogType::Warning);
}

/**
 * Вывод сообщения об ошибке
 * @param msg Текст сообщения
 */
void Logger::error(std::string_view msg) const
{
    if (!msg.empty())
        writeMessage(msg, LogType::Error);
}

/**
 * Запись сообщения в файл
 * @param msg Текст сообщения
 * @param logType Тип сообщения
 */
void Logger::writeMessage(std::string_view msg, LogType logType) const
{
    std::string type;

    // Определение типа информационного сообщения
    switch (logType)
    {
        case LogType::Debug : type = "DEB"; break;
        case LogType::Information : type = "INF"; break;
        case LogType::Warning : type = "WRN"; break;
        case LogType::Error : type = "ERR"; break;
        default: break;
    }

    // Получение времени вывода сообщения
    std::time_t time = std::time(nullptr);
    std::tm now = *std::localtime(&time);
    auto date = std::put_time(&now, "%d.%m.%Y %H:%M:%S");

    // Формирование строки сообщения
    std::stringstream message;
    message <<"[" <<date <<"] ( "<<type <<" : " <<this->m_unitName <<" ) => Message: " <<msg;

    // Запись сообщения в файл
    std::string log = this->logName();
    std::ofstream out(log, std::ios::app);

    // Если файл удалось открыть
    if (out.is_open())
        out <<message.str() << std::endl;

    out.close();
}

/**
 * Получить имя файла лога по текущей дате
 * @return Имя файла
 */
std::string Logger::logName() const
{
    // Получить текущую дату
    std::time_t time = std::time(nullptr);
    std::tm now = *std::localtime(&time);
    auto date = std::put_time(&now, "%Y-%m-%d");

    // Получить имя каталога для сохранения логов
    auto full_path = std::filesystem::current_path();
    std::string path = full_path.string() + "\\Logs\\";

    // Проверим, существует ли каталог для хранения логов
    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    // Сформируем полное имя файла
    std::stringstream logName;
    logName <<path <<date <<".log";

    this->clearLogs();
    return logName.str();
}

/**
 * Удаление логов, созданных более, чем задано в параметрах дней назад
 */
void Logger::clearLogs() const
{
    // Получить имя каталога для сохранения логов
    auto full_path = std::filesystem::current_path();
    std::string path = full_path.string() + "\\Logs\\";

    // cycle through the directory
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
    {
        std::string file = entry.path().string();

        // Время последней записи в файл
        auto fTime = std::filesystem::last_write_time(file);
        std::time_t cTime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(fTime));
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Если получили правильное время
        if ( now != static_cast<std::time_t>(-1) && cTime != static_cast<std::time_t>(-1) )
        {
            double difference = std::round(std::difftime(now, cTime) / (60 * 60 * 24));

            if (difference > this->m_fileAge)
            {
                std::filesystem::remove(file);
            }
        }
    }
}

/**
 * Чтение параметров логирования из файла настроек
 */
void Logger::readParameters()
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
        std::string msg = "Не удалось прочитать параметры подключения к БД [" + err.message() + "]";
        this->error(msg);
        return;
    }

    // Формирование строки подключения к БД
    auto logLevel = pt.get<std::string>("Logging.level");
    this->m_fileAge = std::stoi(pt.get<std::string>("Logging.age"));

    if (logLevel == "Debug")
    {
        this->m_logLevel = LogType::Debug;
    }
    else if (logLevel == "Information")
    {
        this->m_logLevel = LogType::Information;
    }
    else if (logLevel == "Warning")
    {
        this->m_logLevel = LogType::Warning;
    }
    else if (logLevel == "Error")
    {
        this->m_logLevel = LogType::Error;
    }
    else
    {
        this->m_logLevel = LogType::Default;
    }
}

/**
 * Получить текущий уровень детализации логов
 * @return Уровень детализации логов
 */
int Logger::logLevel() const
{
    int result = 0;

    switch (m_logLevel)
    {
        case LogType::Debug : {
            result |= static_cast<int>(LogType::Debug);
            result |= static_cast<int>(LogType::Information);
            result |= static_cast<int>(LogType::Warning);
            result |= static_cast<int>(LogType::Error);
            break;
        }
        case LogType::Information : {
            result |= static_cast<int>(LogType::Information);
            result |= static_cast<int>(LogType::Warning);
            result |= static_cast<int>(LogType::Error);
            break;
        }
        case LogType::Warning : {
            result |= static_cast<int>(LogType::Warning);
            result |= static_cast<int>(LogType::Error);
            break;
        }
        case LogType::Error : {
            result |= static_cast<int>(LogType::Error);
            break;
        }
        default :
        {
            result |= static_cast<int>(LogType::Default);
            break;
        }
    }

    return result;
}
