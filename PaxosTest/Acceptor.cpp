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

	std::thread thread_accept_request(&Acceptor::receive_accept_request, this);
	thread_accept_request.detach();

	count_accepted_request_ = 0;
}




void Acceptor::send_response_to_prepare_request(Proposal *proposal)
{
	// Si no hay nada procesandose...
	if (!there_is_an_accepted_request_)
		proposal->set_none(true);
	else {
		proposal->set_value(value_);
		proposal->set_proposal_number(proposal_number_);
	}

	if (message_.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), std::string(ACCEPTOR) + "." + std::to_string(id_), ACTION_RESPONSE_TO_PREPARE_REQUEST, std::string(PROPOSER) + "." + std::to_string(proposal->get_id())) != MSG_SUCCESS)
		printf("Acceptor::response_to_prepare_request - FAILED send message to port %d id %d\r\n", PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), proposal->get_id());

}



// La propuesta es menor que las anteriores.
void Acceptor::send_nack_prepare_request(Proposal* proposal) {

	proposal->set_nack(true);
	if (message_.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), std::string(ACCEPTOR) + "." + std::to_string(id_), ACTION_NACK_TO_PREPARE_REQUEST, std::string(PROPOSER) + "." + std::to_string(proposal->get_id())) != MSG_SUCCESS)
		printf("Acceptor::nack_prepare_request - FAILED send message to port %d id %d\r\n", PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), proposal->get_id());
}

void Acceptor::receive_prepare_request()
{
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive1_, std::string(ACCEPTOR) + "." + std::to_string(id_));
		if (result != MSG_SUCCESS) {
			printf("Acceptor::receive_prepare_request - FAILED!!! receive message %d\r\n", result);
		}
		else if (proposal.get_proposal_number() > proposal_number_) {
			proposal_number_ = proposal.get_proposal_number();
			send_response_to_prepare_request(&proposal);
		}
		else if (proposal.get_proposal_number() <=  proposal_number_) {
			send_nack_prepare_request(&proposal);
		}
	}
}

void Acceptor::receive_accept_request()
{	
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive2_, std::string(ACCEPTOR) + "." + std::to_string(id_));

		count_accepted_request_++;
		if (count_accepted_request_ >= MAJORITY) {
			there_is_an_accepted_request_ = true;
			int send_decision_sent_without_error = send_decision(&proposal);
			printf("[SENT Decision] - OK %d/%d", send_decision_sent_without_error, NUM_NODES);
			if (send_decision_sent_without_error >= MAJORITY) {
				// Ya podemos pasar a otra cosa. 
				send_decision(&proposal);
				count_accepted_request_ = 0;
			}
		}
	}
}

int Acceptor::send_decision(Proposal* proposal) 
{		
	int send_decision_sent_without_error = 0;
	// El send_decision tiene que ser enviado a todos los Learners. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		if (message_.receiveMessage(proposal, PORT_BASE + PORT_LEARNER_SUFIX + PORT_RECEIVER1_SUFIX + id_node, std::string(ACCEPTOR) + "." + std::to_string(id_)) != MSG_SUCCESS) {
			printf("Acceptor::send_decision - FAILED!!! to send_decision id:%d, port:%d\n", id_, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node);
		}
		else {
			send_decision_sent_without_error++;
		}
	}
	return send_decision_sent_without_error;
}



bool Acceptor::get_there_is_an_accepted_request()
{	
	return there_is_an_accepted_request_;
}

void Acceptor::set_there_is_an_accepted_request(bool there_is_an_accepted_request)
{
	std::lock_guard<std::mutex> guard(mu_); // RAII
		there_is_an_accepted_request_ = there_is_an_accepted_request;
}