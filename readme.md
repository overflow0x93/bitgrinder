# Bitgrinder
Bitgrinder is a cryptocurrency trading bot written in C++ designed to perform a number of different types of trades at high speed.




# Prerequisites

Bitgrinder
libcurl4-openssl-dev

Prometheus
1. Protocol Buffers>= 3.0 (prometheus-cpp)

Akumuli
1. Boost
2. log4cxx
3. jemalloc
4. microhttpd
5. APR
6. SQLite
7. Cmake

#TODO:
1. Implement Akumuli and Prometheus and benchmark performance
2. Refactor current CBOR functionality to push to TSDB
3. Generate time series for each currency and time series
4. Perform analysis on each time series
5. Display trade data in real-time via monitoring application refactoring monitor as needed
6. Finish config file parsing and setup
7. Benchmark standard operations and optimize
8. Improve error handling for json fetching