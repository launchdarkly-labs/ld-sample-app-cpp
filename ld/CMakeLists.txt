cmake_minimum_required(VERSION 3.19)

project(
        LDClient
        VERSION 0.1
        DESCRIPTION "Client-side SDK"
        LANGUAGES CXX
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(ld-client LDClient.cc)
target_link_libraries(ld-client PRIVATE launchdarkly::client Threads::Threads)
