//============================================================================
// Name        : my_Server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

#include "serversocket.h"
using namespace std;

void readm(serversocket &server){
	while(1)
		server.readMessage();
}

void writem(serversocket &server){
	while(1)
		server.writeMessage("");
}

int main(void) {
	cout << "Server Programs starts...." << endl;
	serversocket servSoc;
	if(servSoc.connectToServer("", 8888))
	{
		if(servSoc.acceptClient()){
			thread t1(readm,ref(servSoc));
			thread t2(writem,ref(servSoc));
			t1.join();t2.join();
		}else
		{
			cout << "Info : Accepting failed" << endl;
		}
	}
	cout << "Server Programs ends...." << endl;
}
