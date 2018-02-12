CXX = g++ -std=c++11
CC=g++
#CXXFLAGS=
LIBS = -lcurl -lstdc++ -lcrypto -l pthread
all: clean bitgrinder monitor console

bitgrinder: bitgrinder.o gateio.o tradedata.o
	$(CXX) -o ./bin/bitgrinder ./bin/bitgrinder.o ./bin/exchange/gateio.o ./bin/system/sysdata.o ./bin/system/tradedata.o $(LIBS)

bitgrinder.o: sysdata.o ./src/bitgrinder.cpp ./src/include/bitgrinder.h ./src/include/system/json.hpp ./src/include/system/data.h
	$(CXX) -c -o ./bin/bitgrinder.o ./src/bitgrinder.cpp $(LIBS)

gateio.o: exchange.o sysdata.o ./src/exchange/gateio.cpp ./src/include/exchange/gateio.h ./src/include/exchange/exchange.h ./src/include/system/json.hpp ./src/include/system/data.h
	$(CXX) -c -o ./bin/exchange/gateio.o ./src/exchange/gateio.cpp $(LIBS)

exchange.o: ./src/exchange/exchange.cpp ./src/include/exchange/exchange.h
	$(CXX) -c -o ./bin/exchange/exchange.o ./src/exchange/exchange.cpp $(LIBS)

monitor: monitor.o
	$(CXX) -o ./bin/monitor ./bin/monitor.o $(LIBS)

monitor.o: ./src/btgmonitor.cpp ./src/include/btgmonitor.h
	$(CXX) -c -o ./bin/monitor.o ./src/btgmonitor.cpp $(LIBS)

console: console.o
	$(CXX) -o ./bin/console ./bin/console.o ./bin/system/systatus.o -L/usr/lib64 -lboost_program_options -lboost_filesystem -lboost_system $(LIBS)

console.o: systatus.o ./src/console.cpp ./src/include/console.h ./src/include/system/systatus.h
	$(CXX) -c -o ./bin/console.o ./src/console.cpp -L/usr/lib64 -lboost_program_options -lboost_filesystem -lboost_system $(LIBS)

sysdata.o: ./src/system/data.cpp ./src/include/system/data.h ./src/include/system/json.hpp
	$(CXX) -c -o ./bin/system/sysdata.o ./src/system/data.cpp $(LIBS)

tradedata.o: ./src/system/tradedata.cpp ./src/include/system/tradedata.h
	$(CXX) -c -o ./bin/system/tradedata.o ./src/system/tradedata.cpp $(LIBS)

systatus.o: ./src/system/systatus.c ./src/include/system/systatus.h
	$(CC) -c ./src/system/systatus.c -o ./bin/system/systatus.o

clean:
	rm -f ./bin/bitgrinder ./bin/monitor ./bin/console ./bin/*.o ./bin/web/*.o ./bin/system/*.o ./bin/exchange/*.o

install:
	cp ./bin/bitgrinder ./bin/console ./bin/monitor /opt/bitgrinder