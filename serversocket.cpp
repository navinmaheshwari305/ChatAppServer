/*
 * serversocket.cpp
 *
 *  Created on: 01-Apr-2017
 *      Author: navin
 */

#include "serversocket.h"

#include <arpa/inet.h>

serversocket::serversocket() {
	bind_addr = new sockaddr_in();
	bind_addr->sin_family = AF_INET;
	std::cout << "Info :bind_adrr "<< bind_addr->sin_family  << std::endl;
	bind_addr->sin_addr.s_addr = INADDR_ANY;
	sockFd = -1;
	client_socket = -1;
}

serversocket::~serversocket() {
	close(client_socket);
	close(sockFd);
	std::cout << "Info : In destructor " << std::endl;
	if(bind_addr != NULL){
		delete bind_addr;
	}
}

bool serversocket::connectToServer(std::string serv_ip,int port)
{
	sockFd = socket(AF_INET,SOCK_STREAM,0);
	if(sockFd == -1)
	{
		std::cout << "Error : Creating socket failed ["<< strerror(errno) <<"]"  << std::endl;
		return false;
	}

	bind_addr->sin_port = htons(port);
	if(!serv_ip.empty() &&  inet_pton(AF_INET, serv_ip.c_str(), &bind_addr->sin_addr)<=0)
	{
		std::cout << "Error : Invalid address/ Address not supported \n";
		return false;
	}
	if(bind(sockFd,(struct sockaddr*)bind_addr,sizeof(*bind_addr)) == -1)
	{
		std::cout << "Error : Binding failed ["<< strerror(errno) <<"]" << std::endl;
		return false;
	}
	std::cout << "Info : Binding done "<< std::endl;

	if(listen(sockFd,2) == -1 )
	{
		std::cout << "Error : Listening failed" << std::endl;
		return false;
	}
	std::cout << "Info : Listening done ["<< strerror(errno) <<"]" << std::endl;
	std::cout << "Info : Server started at port : " << port << std::endl;
	return true;
}
bool serversocket::acceptClient(){
	unsigned int addrLen = sizeof(cli_addr);
		client_socket = accept(sockFd,(struct sockaddr *)&cli_addr,&addrLen);
		if(!client_socket)
		{
			std::cout << "Error : Accepting failed ["<< strerror(errno) <<"]" << std::endl;
			return false;
		}
		std::string str;
		std::cout << "Info : Client connected [" << inet_ntoa(cli_addr.sin_addr) <<"]" << std::endl;
		return true;
}

void serversocket::readMessage()
{
	if(client_socket == -1)
	{
		std::cout << "Error : Socket not defined"<< std::endl;
		exit(1);
	}

	std::string message;
	char buffer[1025];int readLen=1024;
	while(readLen == 1024)
	{
		readLen = read(client_socket,buffer,1024);
		if(readLen == 0) exit(1);
		buffer[readLen]= '\0';
		message += std::string(buffer);
	}
	std::cout <<"Client says : " << message << std::endl;
}
void serversocket::writeMessage(std::string str)
{
	if(client_socket == -1)
	{
		std::cout << "Error : Socket not defined"<< std::endl;
		exit(1);
	}
	std::cout << "You : ";std::cin>>str;std::cout<<std::endl;
	if(send(client_socket,str.c_str(),str.length(),0) == -1)
	{
		std::cout << "Error : Message ["<<str<<"] writing failed"<< std::endl;
	}
}
