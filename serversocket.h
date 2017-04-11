/*
 * serversocket.h
 *
 *  Created on: 01-Apr-2017
 *      Author: navin
 */

#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_
#include <string>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <errno.h>
#include <string.h>

class serversocket {
public:
	serversocket();
	virtual ~serversocket();

	bool connectToServer(std::string serv_ip,int port);
	bool acceptClient();
	void readMessage();
	void writeMessage(std::string str = "");

private:
	struct sockaddr_in *bind_addr = NULL;
	struct sockaddr_in cli_addr;
	int client_socket;
	int sockFd;
};

#endif /* SERVERSOCKET_H_ */

