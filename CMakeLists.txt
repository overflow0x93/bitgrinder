cmake_minimum_required(VERSION 3.9)
project(bitgrinder)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99")

include_directories(${bitgrinder_SOURCE_DIR}/src)
include_directories(${bitgrinder_SOURCE_DIR}/src/include)
include_directories(${bitgrinder_SOURCE_DIR}/src/include/system)
include_directories(${bitgrinder_SOURCE_DIR}/src/include/exchange)
include_directories(${bitgrinder_SOURCE_DIR}/src/include/math)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif ()
IF (NOT Boost_FOUND)
    message(WARNING "Boost not found.")
endif ()

find_package(CURL)
if (NOT ${CURL_FOUND})
    message(WARNING "libcURL not found.")
endif ()
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
endif ()

add_executable(bitgrinder
        src/exchange/apiscrape.cpp
        src/exchange/exchange.cpp
        src/exchange/gateio.cpp
        src/exchange/position.cpp
        src/include/exchange/apiscrape.hpp
        src/include/exchange/exchange.hpp
        src/include/exchange/gateio.hpp
        src/include/exchange/position.hpp
        src/include/math/analysis.hpp
        src/include/system/config.hpp
        src/include/system/conparse.hpp
        src/include/system/data.hpp
        src/include/system/json.hpp
        src/include/system/logging.hpp
        src/include/system/systatus.hpp
        src/include/system/tinyfsm.hpp
        src/include/system/tradedata.hpp
        src/include/bitgrinder.hpp
        src/system/config.cpp
        src/system/conparse.cpp
        src/system/data.cpp
        src/system/logging.cpp
        src/system/systatus.cpp
        src/system/tradedata.cpp
        src/bitgrinder.cpp)

add_executable(monitor
        src/include/btgmonitor.hpp
        src/btgmonitor.cpp)

add_executable(console
        src/include/system/config.hpp
        src/include/system/data.hpp
        src/include/system/json.hpp
        src/include/system/systatus.hpp
        src/include/console.hpp
        src/system/config.cpp
        src/system/data.cpp
        src/system/systatus.cpp
        src/console.cpp)

#add_custom_target(_make_bitgrinder COMMAND make -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

#add_custom_target(_make_console COMMAND make console -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

#add_custom_target(_make_monitor COMMAND make monitor -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

target_Link_Libraries(bitgrinder "-lcrypto -lcurl -lstdc++ -lpthread -lboost_program_options -lboost_filesystem -lboost_system")
target_Link_Libraries(console "-lcrypto -lcurl -lstdc++ -lpthread -lboost_program_options -lboost_filesystem -lboost_system")