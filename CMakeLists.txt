cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-fexec-charset=CP949")

add_executable(untitled main.cpp)
if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    file(WRITE ${PROJECT_BINARY_DIR}\\crun.bat start\ /wait\ ccore.bat)
    file(WRITE ${PROJECT_BINARY_DIR}\\ccore.bat @echo\ off\ntitle\ ${CMAKE_PROJECT_NAME}\ncls\n${CMAKE_PROJECT_NAME}\npause\nexit)
endif()