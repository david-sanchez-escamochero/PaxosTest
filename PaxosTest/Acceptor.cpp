#include "Acceptor.h"


#include "PaxosDefs.h"
#include <thread>

void Acceptor::start(uint32_t id)
{
	port_send_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive1_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id;
	port_receive2_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id;

	std::thread thread_receive_prepare_request(&Acceptor::receive_prepare_request, this);
	thread_receive_prepare_request.detach();

	std::thread thread_accept_request(&Acceptor::accept_request, this);
	thread_accept_request.detach();

}



void Acceptor::response_to_prepare_request(Proposal *proposal)
{
	// Si no hay nada procesandose...
	if (!accepted_request)
		proposal->set_none(true);
	else {
		proposal->set_value(value_);
		proposal->set_proposal_number(proposal_number_);
	}

	if (message_.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id()) != MSG_SUCCESS)
		printf("Acceptor::response_to_prepare_request - FAILED send message to port %d id %d\r\n", PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), proposal->get_id());

}

void Acceptor::decision(Proposal* proposal)
{

}

// La propuesta es menor que las anteriores.
void Acceptor::nack_prepare_request(Proposal* proposal) {

	proposal->set_nack(true);
	if (message_.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id()) != MSG_SUCCESS)
		printf("Acceptor::nack_prepare_request - FAILED send message to port %d id %d\r\n", PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), proposal->get_id());
}

void Acceptor::receive_prepare_request()
{
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive1_);
		if (result != MSG_SUCCESS) {
			printf("Acceptor::receive_prepare_request - FAILED!!! receive message %d\r\n", result);
		}
		if (proposal.get_proposal_number() > proposal_number_) {
			proposal_number_ = proposal.get_proposal_number();
			response_to_prepare_request(&proposal);
		}
		else {
			nack_prepare_request(&proposal);
		}
	}
}

void Acceptor::accept_request()
{
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive2_);

		count_accepted_request++;
		if (count_accepted_request >= MAJORITY)
			accepted_request = true;
	}
}

