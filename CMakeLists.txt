cmake_minimum_required(VERSION 3.10)
project(GuardGallivant)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/Main.cpp
    src/ArgumentParser.cpp
    src/FileReader.cpp
)

set(HEADERS
    src/ArgumentParser.hpp
    src/FileReader.hpp
    src/PositionCounter.hpp
)

add_executable(GuardGallivant ${SOURCES} ${HEADERS})
