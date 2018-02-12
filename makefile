CXX = g++ -std=c++11
#CXXFLAGS=
LIBS = -lcurl -lstdc++ -lcrypto -l pthread
all: clean bitgrinder statmon

bitgrinder: bitgrinder.o gateio.o tradedata.o
	$(CXX) -o ./bin/bitgrinder ./bin/bitgrinder.o ./bin/exchange/gateio.o ./bin/system/sysdata.o ./bin/system/tradedata.o $(LIBS)

bitgrinder.o: sysdata.o ./src/bitgrinder.cpp ./src/include/bitgrinder.h ./src/include/system/json.hpp ./src/include/system/data.h
	$(CXX) -c -o ./bin/bitgrinder.o ./src/bitgrinder.cpp $(LIBS)

gateio.o: exchange.o sysdata.o ./src/exchange/gateio.cpp ./src/include/exchange/gateio.h ./src/include/exchange/exchange.h ./src/include/system/json.hpp ./src/include/system/data.h
	$(CXX) -c -o ./bin/exchange/gateio.o ./src/exchange/gateio.cpp $(LIBS)

exchange.o: ./src/exchange/exchange.cpp ./src/include/exchange/exchange.h
	$(CXX) -c -o ./bin/exchange/exchange.o ./src/exchange/exchange.cpp $(LIBS)

statmon: statmon.o
	$(CXX) -o ./bin/statmon ./bin/statmon.o $(LIBS)

statmon.o: ./src/statmon.cpp ./src/include/statmon.h
	$(CXX) -c -o ./bin/statmon.o ./src/statmon.cpp $(LIBS)

sysdata.o: ./src/system/data.cpp ./src/include/system/data.h ./src/include/system/json.hpp
	$(CXX) -c -o ./bin/system/sysdata.o ./src/system/data.cpp $(LIBS)

tradedata.o: ./src/system/tradedata.cpp ./src/include/system/tradedata.h
	$(CXX) -c -o ./bin/system/tradedata.o ./src/system/tradedata.cpp $(LIBS)

clean:
	rm -f ./bin/bitgrinder ./bin/statmon ./bin/*.o ./bin/web/*.o ./bin/system/*.o ./bin/exchange/*.o
