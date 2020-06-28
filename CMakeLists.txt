cmake_minimum_required(VERSION 3.2.0)
project(NamelessLogger)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog")

message(STATUS, ${CMAKE_CURRENT_SOURCE_DIR})


set(SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/Log.hpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/Log.cpp")

set(VENDOR_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include/")

add_library(NamelessLogger ${SOURCES} ${VENDOR_SOURCES})

target_include_directories(NamelessLogger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                                                 "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include/" )
