cmake_minimum_required(VERSION 3.11)

project(ComputerClubManagement CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CPP_COMPILER g++)

add_executable(${PROJECT_NAME}
    src/utils.h
    src/utils.cpp
    src/ComputerClubManager.h
    src/ComputerClubManager.cpp
    src/main.cpp
)