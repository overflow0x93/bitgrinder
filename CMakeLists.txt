cmake_minimum_required(VERSION 3.9)
project(bitgrinder)

set(CMAKE_CXX_STANDARD 11)

add_custom_target(bitgrinder COMMAND make -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_custom_target(console COMMAND make console -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_custom_target(monitor COMMAND make monitor -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})