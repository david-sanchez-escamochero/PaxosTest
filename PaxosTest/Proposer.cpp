#include "Proposer.h"


#include "Message.h"

void Proposer::start(uint32_t port_send, uint32_t  port_receiver, uint32_t id)
{
	std::string str_message = "hola";	
	id_ = id;
	proposal_number_ = 0;
	port_send_ = port_send;
	port_receive_ = port_receiver;
}

uint32_t Proposer::prepare_request(std::string value)
{
	// Envía a todos los acceptors su propuest. 
	Proposal proposal; 
	proposal.set_value(value);
	proposal.set_proposal_number(get_proposal_number());
	return message_.sendMessage(proposal, 6202);
}

void Proposer::response_to_prepare_request() 
{
	//message.receiveMessage();
}

void Proposer::accept_resquest(Proposal* proposal)
{
}

void Proposer::client_request(std::string value) 
{
	prepare_request(value);
}

uint32_t Proposer::get_proposal_number() {
	return proposal_number_;
}

