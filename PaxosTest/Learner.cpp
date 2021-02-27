#include "Learner.h"

#include "Message.h"

void Learner::start(uint32_t port_send, uint32_t  port_receive, uint32_t id)
{
	port_send_ = port_send;
	port_receive_ = port_receive;

}
