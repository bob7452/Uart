# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(Uart)

#C++ 11
set(CMAKE_CXX_STANDARD 11)

#set source 
set(SRC_DIR ../../src)

#set includes
set(INCLUDE_DIR ../../includes)

#add include path
include_directories(${INCLUDE_DIR})

find_package(Boost COMPONENTS coroutine REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(test_file_io test_file_io.cpp ${SRC_DIR}/io.cpp)
    target_link_libraries(test_file_io ${Boost_LIBRARIES})
endif()

