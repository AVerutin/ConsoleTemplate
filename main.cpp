#include <windows.h>
#include <memory>
#include <iostream>
#include "logger.h"
#include "application.h"


BOOL WINAPI CtrlHandler(DWORD fdwCtrlType)
{
    auto logger = std::make_shared<Logger>("Main");
    std::string msg = "Application stopped ";

    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
        case CTRL_C_EVENT:
            msg.append("by [Ctrl-C] event");
            break;

            // CTRL-CLOSE: confirm that the user wants to exit.
        case CTRL_CLOSE_EVENT:
            msg.append("by [Close] event");
            break;

            // Pass other signals to the next handler.
        case CTRL_BREAK_EVENT:
            msg.append("by [Ctrl-Break] event");
            break;

        case CTRL_LOGOFF_EVENT:
            msg.append("by [Logoff] event");
            break;

        case CTRL_SHUTDOWN_EVENT:
            msg.append("by [Shutdown] event");
            break;

        default:
            msg.append("by [unknown] reason");
            break;
    }

    logger->info(msg);
    return FALSE;
}


int main(int argc, char** argv)
{
    if (!SetConsoleCtrlHandler(CtrlHandler, TRUE))
    {
        std::cerr <<"Error registering exit handler" <<std::endl;
    }

    std::shared_ptr<Logger> logger = std::make_shared<Logger>("Main");
    logger->info("Application started");

    auto app = Application::create(argc, argv);
    return app->run();
}
