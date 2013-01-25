CXX =g++
C=gcc
FLAGS= -Wall -ggdb
CFLAGS= $(FLAGS) -std=c99 -D_GNU_SOURCE
CXXFLAGS =$(FLAGS)

SERVER_SRC = \
    server.cc

SERVER_SRC_OBJS = ${SERVER_SRC:.cc=.o}


CLIENT_SRC = \
    client.c

CLIENT_SRC_OBJS = ${CLIENT_SRC:.c=.o}


.SUFFIXES:
.SUFFIXES: .o .cc .c
.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $*.o

.c.o:
	$(C) $(CFLAGS) -c $< -o $*.o

all: server client

server: $(SERVER_SRC_OBJS)
	$(CXX) $(CXXFLAGS) -o server $(SERVER_SRC_OBJS) -lACE

client: $(CLIENT_SRC_OBJS)
	$(C) $(CFLAGS) -o client $(CLIENT_SRC_OBJS)

clean:
	$(RM) $(SERVER_SRC_OBJS) $(CLIENT_SRC_OBJS) client server

