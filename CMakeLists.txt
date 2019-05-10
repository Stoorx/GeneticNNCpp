cmake_minimum_required(VERSION 3.12)
project(GeneticNNCpp)

set(CMAKE_CXX_STANDARD 17)


include_directories(include)
include(include/CMakeLists.txt)
include(src/CMakeLists.txt)

add_executable(GeneticNNCpp main.cpp include/FourierElement.h include/FourierSeries.h include/Random.h include/FourierHypersurface.h include/IncorrectArgsException.h src/Random.cpp)