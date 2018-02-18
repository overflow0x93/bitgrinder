cmake_minimum_required(VERSION 3.9)
project(bitgrinder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread")

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
    message(WARNING "Could not find libcURL.")
endif ()
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
endif ()

add_executable(bitgrinder
        src/exchange/apiscrape.cpp
        src/exchange/exchange.cpp
        src/exchange/gateio.cpp
        src/exchange/position.cpp
        src/include/exchange/apiscrape.h
        src/include/exchange/exchange.h
        src/include/exchange/gateio.h
        src/include/exchange/position.h
        src/include/math/analysis.h
        src/include/system/config.h
        src/include/system/conparse.h
        src/include/system/data.h
        src/include/system/json.hpp
        src/include/system/systatus.h
        src/include/system/tinyfsm.hpp
        src/include/system/tradedata.h
        src/include/bitgrinder.h
        src/math/analysis.cpp
        src/system/config.cpp
        src/system/conparse.cpp
        src/system/data.cpp
        src/system/systatus.c
        src/system/tradedata.cpp
        src/bitgrinder.cpp
        makefile
        readme.md)

add_executable(monitor
        src/exchange/apiscrape.cpp
        src/exchange/exchange.cpp
        src/exchange/gateio.cpp
        src/exchange/position.cpp
        src/include/exchange/apiscrape.h
        src/include/exchange/exchange.h
        src/include/exchange/gateio.h
        src/include/exchange/position.h
        src/include/math/analysis.h
        src/include/system/config.h
        src/include/system/conparse.h
        src/include/system/data.h
        src/include/system/json.hpp
        src/include/system/systatus.h
        src/include/system/tinyfsm.hpp
        src/include/system/tradedata.h
        src/include/btgmonitor.h
        src/include/console.h
        src/math/analysis.cpp
        src/system/config.cpp
        src/system/conparse.cpp
        src/system/data.cpp
        src/system/systatus.c
        src/system/tradedata.cpp
        src/btgmonitor.cpp
        makefile
        readme.md)

add_executable(console
        src/exchange/apiscrape.cpp
        src/exchange/exchange.cpp
        src/exchange/gateio.cpp
        src/exchange/position.cpp
        src/include/exchange/apiscrape.h
        src/include/exchange/exchange.h
        src/include/exchange/gateio.h
        src/include/exchange/position.h
        src/include/math/analysis.h
        src/include/system/config.h
        src/include/system/conparse.h
        src/include/system/data.h
        src/include/system/json.hpp
        src/include/system/systatus.h
        src/include/system/tinyfsm.hpp
        src/include/system/tradedata.h
        src/include/console.h
        src/math/analysis.cpp
        src/system/config.cpp
        src/system/conparse.cpp
        src/system/data.cpp
        src/system/systatus.c
        src/system/tradedata.cpp
        src/console.cpp
        makefile
        readme.md)

add_custom_target(bitgrinder_make COMMAND make -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_custom_target(console_make COMMAND make console -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_custom_target(monitor_make COMMAND make monitor -C ${bitgrinder_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})
target_Link_Libraries(bitgrinder "-lcrypto -lcurl -lstdc++ -lpthread -lboost_program_options -lboost_filesystem -lboost_system -stdlib=libc++")