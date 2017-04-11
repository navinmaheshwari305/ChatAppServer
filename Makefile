CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS = $(SRC:.cpp=.o)

SRC = my_server.cpp serversocket.cpp

INC = serversocket.h
  
FLAGS =  -std=c++11  -Wall -pedantic -g  -pthread

LIBS =

TARGET = server

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(FLAGS)

all:	$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)

.cpp.o :
	$(CXX) -c $< -o $@  $(LIBS) $(INCS) $(FLAGS)