#include "Proposer.h"


#include "Message.h"

void Proposer::start(uint32_t port)
{
	std::string str_message = "hola";
	message.receiveMessage(str_message);	
}

void Proposer::prepareRequest(uint32_t proposal_number)
{
}

void Proposer::acceptResquest(Proposal* proposal)
{
}
