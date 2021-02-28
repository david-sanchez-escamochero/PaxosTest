#pragma once

#include <string>
#include "Proposal.h"

#define MSG_SUCCESS                                 0
#define MSG_ERROR_INITIALIZATION_SOCKET             1
#define MSG_ERROR_UNKNOWN_SERVER                    2
#define MSG_ERROR_CREATE_SOCKET                     3
#define MSG_ERROR_FAILED_TO_CONNECT_SERVER          4
#define MSG_ERROR_TO_ASSOCIATE_PORT_AND_IP_SOCKET   5
#define MSG_ERROR_TO_ENABLE_INGOING_CONNECTIONS     6
#define MSG_ERROR_TO_ACCEPT_INGOING_CONNECTIONS     7



class Message
{
public: 
	int sendMessage(Proposal *proposal, unsigned short port);
	int receiveMessage(Proposal *proposal, unsigned short port);
	void start();
private: 
	char SendBuff[512], RecvBuff[512];
};

