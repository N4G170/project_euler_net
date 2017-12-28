#Project Euler Makefile

INCLUDE=-Isrc/include -Isrc/include/sockets -Isrc/lib/jsoncpp

CXX=g++

CXXFLAGS=-c -Wall -std=c++14 $(INCLUDE)
LDFLAGS=-lSDL2 -lSDL2_net -lgmp -pthread

SRC_PATH=src/src/
PROBLEMS_PATH=src/src/problems/
LIB_PATH=src/lib/
OBJ_PATH=objects/
BIN_PATH=bin/

#So this make file is a mess and will keep growing as I add more files, so I'll need to change it to a patern approach
all: app

app: configparser main message_writer utils clock server_socket_TCP server_socket_UDP jsoncpp problems_results eulerproblems_01_10 eulerproblems_11_20 eulerproblems_21_30 eulerproblems_31_40 eulerproblems_41_50 eulerproblems_51_60 eulerproblems_61_70 eulerproblems_71_80 eulerproblems_81_90 eulerproblems_91_100 poker_hand
	$(CXX) $(LDFLAGS) $(OBJ_PATH)configparser.o $(OBJ_PATH)main.o $(OBJ_PATH)message_writer.o $(OBJ_PATH)utils.o $(OBJ_PATH)clock.o $(OBJ_PATH)server_socket_TCP.o $(OBJ_PATH)server_socket_UDP.o $(OBJ_PATH)jsoncpp.o $(OBJ_PATH)problems_results.o $(OBJ_PATH)eulerproblems_01_10.o $(OBJ_PATH)eulerproblems_11_20.o $(OBJ_PATH)eulerproblems_21_30.o $(OBJ_PATH)eulerproblems_31_40.o $(OBJ_PATH)eulerproblems_41_50.o $(OBJ_PATH)eulerproblems_51_60.o $(OBJ_PATH)eulerproblems_61_70.o $(OBJ_PATH)eulerproblems_71_80.o $(OBJ_PATH)eulerproblems_81_90.o $(OBJ_PATH)eulerproblems_91_100.o $(OBJ_PATH)poker_hand.o -o $(BIN_PATH)euler_server


main: 
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(OBJ_PATH)main.o 

configparser:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)configparser.cpp -o $(OBJ_PATH)configparser.o

message_writer:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)message_writer.cpp -o $(OBJ_PATH)message_writer.o

jsoncpp:
	$(CXX) $(CXXFLAGS) $(LIB_PATH)/jsoncpp/jsoncpp.cpp -o $(OBJ_PATH)jsoncpp.o

utils:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)utils.cpp -o $(OBJ_PATH)utils.o

clock:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)clock.cpp -o $(OBJ_PATH)clock.o

server_socket_TCP:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)/sockets/server_socket_TCP.cpp -o $(OBJ_PATH)server_socket_TCP.o

server_socket_UDP:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)/sockets/server_socket_UDP.cpp -o $(OBJ_PATH)server_socket_UDP.o

problems_results:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)problems_results.cpp -o $(OBJ_PATH)problems_results.o

eulerproblems_01_10:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_01_10.cpp -o $(OBJ_PATH)eulerproblems_01_10.o

eulerproblems_11_20:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_11_20.cpp -o $(OBJ_PATH)eulerproblems_11_20.o

eulerproblems_21_30:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_21_30.cpp -o $(OBJ_PATH)eulerproblems_21_30.o

eulerproblems_31_40:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_31_40.cpp -o $(OBJ_PATH)eulerproblems_31_40.o

eulerproblems_41_50:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_41_50.cpp -o $(OBJ_PATH)eulerproblems_41_50.o

eulerproblems_51_60:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_51_60.cpp -o $(OBJ_PATH)eulerproblems_51_60.o

eulerproblems_61_70:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_61_70.cpp -o $(OBJ_PATH)eulerproblems_61_70.o

eulerproblems_71_80:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_71_80.cpp -o $(OBJ_PATH)eulerproblems_71_80.o

eulerproblems_81_90:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_81_90.cpp -o $(OBJ_PATH)eulerproblems_81_90.o

eulerproblems_91_100:
	$(CXX) $(CXXFLAGS) $(PROBLEMS_PATH)eulerproblems_91_100.cpp -o $(OBJ_PATH)eulerproblems_91_100.o

poker_hand:
	$(CXX) $(CXXFLAGS) $(SRC_PATH)poker_hand.cpp -o $(OBJ_PATH)poker_hand.o

clean:
	rm $(OBJ_PATH)* $(BIN_PATH)euler_server