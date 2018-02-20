CC=g++
CXX = $(CC) -std=c++11
# Standard build
#CXXFLAGS=-c
# Debug Build
CXXFLAGS=-c -ggdb
#LIBS = -lcurl -lstdc++ -lcrypto -l pthread
LIBS = -lcurl -lstdc++ -lcrypto -pthread
all: clean bitgrinder monitor console

bitgrinder: bitgrinder.o gateio.o tradedata.o config.o position.o sysdata.o
	$(CXX) -o ./bin/bitgrinder ./bin/bitgrinder.o ./bin/exchange/gateio.o ./bin/system/sysdata.o ./bin/system/tradedata.o ./bin/system/config.o ./bin/exchange/position.o $(LIBS)

bitgrinder.o: sysdata.o gateio.o config.o position.o ./src/bitgrinder.cpp ./src/include/bitgrinder.hpp ./src/include/system/json.hpp ./src/include/system/data.hpp ./src/include/system/config.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/bitgrinder.o ./src/bitgrinder.cpp $(LIBS)

config.o: sysdata.o ./src/system/config.cpp ./src/include/system/config.hpp ./src/include/system/json.hpp ./src/include/system/data.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/system/config.o ./src/system/config.cpp $(LIBS)

gateio.o: exchange.o sysdata.o position.o tradedata.o ./src/exchange/gateio.cpp ./src/include/exchange/gateio.hpp ./src/include/exchange/exchange.hpp ./src/include/system/json.hpp ./src/include/system/data.hpp ./src/include/exchange/position.hpp ./src/include/system/tradedata.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/exchange/gateio.o ./src/exchange/gateio.cpp $(LIBS)

position.o: ./src/exchange/position.cpp ./src/include/exchange/position.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/exchange/position.o ./src/exchange/position.cpp $(LIBS)

exchange.o: ./src/exchange/exchange.cpp ./src/include/exchange/exchange.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/exchange/exchange.o ./src/exchange/exchange.cpp $(LIBS)

monitor: monitor.o 
	$(CXX) -o ./bin/monitor ./bin/monitor.o $(LIBS)

monitor.o: ./src/btgmonitor.cpp ./src/include/btgmonitor.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/monitor.o ./src/btgmonitor.cpp $(LIBS)

console: console.o config.o sysdata.o
	$(CXX) -o ./bin/console ./bin/console.o ./bin/system/systatus.o ./bin/system/config.o ./bin/system/sysdata.o -L/usr/lib64 -lboost_program_options -lboost_filesystem -lboost_system $(LIBS)

console.o: systatus.o sysdata.o ./src/console.cpp ./src/include/console.hpp ./src/include/system/systatus.h ./src/include/system/json.hpp ./src/include/system/data.hpp ./src/include/system/config.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/console.o ./src/console.cpp -L/usr/lib64 -lboost_program_options -lboost_filesystem -lboost_system $(LIBS)

sysdata.o: ./src/system/data.cpp ./src/include/system/data.hpp ./src/include/system/json.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/system/sysdata.o ./src/system/data.cpp $(LIBS)

tradedata.o: ./src/system/tradedata.cpp ./src/include/system/tradedata.hpp
	$(CXX) $(CXXFLAGS) -o ./bin/system/tradedata.o ./src/system/tradedata.cpp $(LIBS)

systatus.o: ./src/system/systatus.c ./src/include/system/systatus.h
	$(CC) $(CXXFLAGS) -o ./bin/system/systatus.o ./src/system/systatus.c

clean:
	rm -f ./bin/bitgrinder ./bin/monitor ./bin/console ./bin/*.o ./bin/web/*.o ./bin/system/*.o ./bin/exchange/*.o

install:
	cp ./bin/bitgrinder ./bin/console ./bin/monitor /opt/bitgrinder
