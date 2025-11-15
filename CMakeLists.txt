cmake_minimum_required(VERSION 3.30)
project(StackAndQueue)

set(CMAKE_CXX_STANDARD 20)

add_executable(StackAndQueue main.cpp
        src/stack/Stack.h
        src/Node.h
        src/queue/Queue.h
        src/Collection.h)
