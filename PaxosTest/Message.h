#pragma once

#include <string>

class Message
{
public: 
	int sendMessage(std::string message);
	int receiveMessage(std::string message);
	void start();
private: 
	char SendBuff[512], RecvBuff[512];
};

