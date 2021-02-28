#include "Learner.h"

#include "Message.h"
#include "PaxosDefs.h"

void Learner::start(uint32_t id)
{
	port_send_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_RECEIVER1_SUFIX + id;
}
