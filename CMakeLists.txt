# Required for Apple Silicon support.
cmake_minimum_required(VERSION 3.19)

project(
        ld-sample-app-cpp
        VERSION 0.1
        DESCRIPTION "LaunchDarkly Sample CXX App"
        LANGUAGES CXX
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(ld-sample-app-cpp main.cpp)
target_link_libraries(Threads::Threads)
