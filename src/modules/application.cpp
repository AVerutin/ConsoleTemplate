#include "application.h"

/**
 * Главный цикл обработки событий
 * @return Код завершения главного цикла обработки событий
 */
int Application::run()
{
    while (this->p_stop_loop == 0)
    {
        // Do anything
        this->do_work();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::string msg = "Exit with code [" + std::to_string(this->p_stop_loop) + "]";
    this->p_logger->error(msg);

    return this->p_stop_loop;
}


/**
 * Создание экземпляра класса приложения
 * @param argc Количество параметров командной строки
 * @param argv Список параметров командной строки
 * @return Ссылка на экземпляр приложения
 */
std::shared_ptr<Application> Application::create(int argc, char **argv)
{
    auto application = std::make_shared<Application>(argc, argv);
    return application;
}


/**
 * Конструктор создания экземпляра приложения
 * @param argc Количество параметров командной строки
 * @param argv Список параметров командной строки
 */
Application::Application(int argc, char **argv) :
    p_configuration{nullptr},
    p_logger{nullptr},
    p_stop_loop{0}, p_app_parameters{}
{
    this->p_configuration = std::make_shared<Configuration>();
    this->p_logger = std::make_shared<Logger>("Application");

    if (argc > 1)
        for (int i = 0; i < argc; ++i)
        {
            p_app_parameters.emplace_back(argv[i]);
        }
}


/**
 * Выполнение основного цикла обработки событий и выход из приложения
 * @return Код завершения
 */
void Application::do_work()
{
    int result = 0;

    this->p_stop_loop = result;
}

