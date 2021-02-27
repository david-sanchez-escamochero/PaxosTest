#include "Acceptor.h"

#include "Message.h"

void Acceptor::start(uint32_t port_send, uint32_t  port_receive, uint32_t id)
{
	port_send_ = port_send;
	port_receive_ = port_receive;
}

void Acceptor::responseToPrepareRequest(void* response)
{
}

void Acceptor::decision(Proposal* proposal)
{
}
