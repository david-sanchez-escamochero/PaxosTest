#pragma once

#include <string>
#include "Proposal.h"


class Message
{
public: 
	int sendMessage(Proposal *proposal, unsigned short port);
	int receiveMessage(Proposal *proposal, unsigned short port);
	void start();
private: 
	char SendBuff[512], RecvBuff[512];
};

