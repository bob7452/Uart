# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(Uart)

#C++ 11
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# 設置 Debug 版本的編譯選項
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
endif()

#set source 
set(SRC_DIR ../../src)

#set includes
set(INCLUDE_DIR ../../includes)

#add include path
include_directories(${INCLUDE_DIR})

find_package(Boost COMPONENTS coroutine REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(test_grammer test_grammer.cpp ${SRC_DIR}/grammer.cpp ${SRC_DIR}/io.cpp)
    target_link_libraries(test_grammer ${Boost_LIBRARIES})
endif()

