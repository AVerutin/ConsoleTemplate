cmake_minimum_required(VERSION 3.22)
project(ApplicationTemplate
        VERSION 1.0.0
        DESCRIPTION "Console application template"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++2a")
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources.rc")
set(SKIP_BUILD_TEST on)

include_directories(src/models)
include_directories(src/modules)
include_directories(src/images)

set(SOURCE main.cpp
        src/modules/application.cpp
        src/modules/application.h
        src/modules/definitions.h
        src/modules/logger.cpp
        src/modules/logger.h
        src/modules/configuration.cpp
        src/modules/configuration.h
        src/modules/connectionparams.cpp
        src/modules/connectionparams.h)

# Copy config file files in binary folder
configure_file(config.ini config.ini COPYONLY)


add_executable(${PROJECT_NAME} ${SOURCE} ${APP_ICON_RESOURCE_WINDOWS})
# target_link_libraries(${PROJECT_NAME} LINK_PUBLIC wsock32 ws2_32)
