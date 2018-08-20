
MUDUO_DIRECTORY ?= .
#MUDUO_DIRECTORY ?= $(HOME)/build/install
MUDUO_INCLUDE = $(MUDUO_DIRECTORY)/include
MUDUO_LIBRARY = $(MUDUO_DIRECTORY)/lib

SRC = .
CC = gcc
CXX = g++

CXXFLAGS = -g -O0 -Wall -I$(MUDUO_INCLUDE)

#CXXFLAGS += -O2 -Wall -ggdb -m64 -D_GNU_SOURCE=1 -D_REENTRANT -D__GUNC__    
	
LDFLAGS = -L$(MUDUO_LIBRARY)  -lpthread -lrt -lm -lmysqlclient

TARGET = echo

all: $(TARGET)


LDFLAGS := $(LDFLAGS) -D_LINUX_OS_ 
INC := $(INC) 

C_SRCS = $(foreach dir, $(SRC), $(wildcard $(dir)/*.c))
CC_SRCS = $(foreach dir, $(SRC), $(wildcard $(dir)/*.cc))
CPP_SRCS = $(foreach dir, $(SRC), $(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,%.o,$(CPP_SRCS)) $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.cc,%.o,$(CC_SRCS))


$(TARGET):$(OBJS)
	$(CXX) -g -o $@ $^ $(LDFLAGS)

%.o:%.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)
%.o:%.cc
	$(CXX) $(INC) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)
%.o:%.c
	$(CC) $(INC) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)
	
#echo: $(SRC)/echo_server.cc $(SRC)/message_handle.cpp  #$(SRC)/websocket.c
#	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f echo $(SRC)/*.o
	
.PHONY: all clean
