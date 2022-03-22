#ifndef THREADPOOL_APPLICATION_H
#define THREADPOOL_APPLICATION_H

#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <windows.h>

#include "configuration.h"
#include "logger.h"

class Application
{
public:
    Application() = delete;
    explicit Application(int argc, char** argv);
    static std::shared_ptr<Application> create(int argc, char** argv);
    [[nodiscard]] int run();

protected:
    void do_work();

    std::shared_ptr<Configuration> p_configuration;
    std::shared_ptr<Logger> p_logger;
    int p_stop_loop;
    std::vector<std::string> p_app_parameters;
};


#endif //THREADPOOL_APPLICATION_H
