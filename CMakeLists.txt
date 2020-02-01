cmake_minimum_required(VERSION 3.15)

include(cmake/HunterGate.cmake)

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.240.tar.gz"
        SHA1 "ca19f3769e6c80cfdd19d8b12ba5102c27b074e0"
)

project(Issue1830)

hunter_add_package(Boost COMPONENTS system)

find_package(Boost CONFIG COMPONENTS system)
find_package(Threads)

link_libraries(Boost::system Threads::Threads)

add_executable(wrong wrong/main.cpp)
add_executable(correct correct/main.cpp)


