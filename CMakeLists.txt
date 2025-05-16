cmake_minimum_required(VERSION 3.16)
project(FileCommander VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

qt_standard_project_setup()

qt_add_executable(FileCommander
    src/main.cpp
    src/MainWindow.cpp
    src/FileManager.cpp
    src/TcpServer.cpp
    src/TcpClient.cpp
)

target_link_libraries(FileCommander PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

target_include_directories(FileCommander PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_compile_features(FileCommander PRIVATE cxx_std_11)
