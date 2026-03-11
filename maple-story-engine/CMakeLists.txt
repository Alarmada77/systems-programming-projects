cmake_minimum_required(VERSION 3.30)
project(4)

set(CMAKE_CXX_STANDARD 17)

add_executable(4 main.cpp
        Players/Job.h
        Events/Encounter.cpp
        Events/Encounter.h
        Events/Event.cpp
        Players/Job.cpp
        Players/Player.cpp
        MatamStory.cpp
        Utilities.cpp)
