cmake_minimum_required(VERSION 3.30)
project(StackAndQueue)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")

add_subdirectory(googletest)

add_executable(StackAndQueue main.cpp
        include/Stack.h
        include/Node.h
        include/Queue.h
        include/Collection.h
        )

include_directories(include)

add_executable(tests
        include/Stack.h
        include/Node.h
        include/Queue.h
        include/Collection.h
        src/Collection.tpp
        src/stack/Stack.tpp
        src/queue/Queue.tpp
        test/test.cpp
)

target_link_libraries(tests gtest)
