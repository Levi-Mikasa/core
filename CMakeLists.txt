cmake_minimum_required(VERSION 3.15)

project(TEST C CXX)

find_package(Threads REQUIRED)

add_subdirectory(service)
message(STATUS "SERVICES ROOT = ${SERVICES}")

add_subdirectory(core)

add_executable(test main.c)

target_include_directories(test
    PRIVATE
    core
)

target_link_libraries(test
    PRIVATE
    core
)