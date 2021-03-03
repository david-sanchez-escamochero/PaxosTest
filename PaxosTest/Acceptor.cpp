#include "Acceptor.h"


#include "PaxosDefs.h"
#include <thread>



void Acceptor::start(uint32_t id, Log* log)
{
	port_send_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive1_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id;
	port_receive2_ = PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id;

	std::thread thread_receive_prepare_request(&Acceptor::receive_prepare_request, this);
	thread_receive_prepare_request.detach();

	std::thread thread_accept_request(&Acceptor::receive_accept_request, this);
	thread_accept_request.detach();

	count_accepted_request_ = 0;
	there_is_an_accepted_request_ = false;
	log_ = log;
}




void Acceptor::send_response_to_prepare_request(Proposal *proposal)
{
	Message message(log_);
	// Si no hay nada procesandose...
	if (!there_is_an_accepted_request_)
		proposal->set_none(true);
	else {
		proposal->set_value(value_);
		proposal->set_proposal_number(proposal_number_);
		proposal->set_none(false);
	}

	if (message.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), std::string(ACCEPTOR) + "." + std::to_string(id_), ACTION_RESPONSE_TO_PREPARE_REQUEST, std::string(PROPOSER) + "." + std::to_string(proposal->get_id())) != MSG_SUCCESS) {
		std::string str_trace = "Acceptor::response_to_prepare_request - FAILED send message to port " + std::to_string(PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id()) + " id " + std::to_string(proposal->get_id()) + "\r\n";
		log_->trace(str_trace);
	}

}



// La propuesta es menor que las anteriores.
void Acceptor::send_nack_prepare_request(Proposal* proposal) {

	Message message(log_);
	proposal->set_nack(true);
	if (message.sendMessage(proposal, PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id(), std::string(ACCEPTOR) + "." + std::to_string(id_), ACTION_NACK_TO_PREPARE_REQUEST, std::string(PROPOSER) + "." + std::to_string(proposal->get_id())) != MSG_SUCCESS) {
		std::string str_trace = "Acceptor::nack_prepare_request - FAILED send message to port " + std::to_string(PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + proposal->get_id()) + " id " + std::to_string(proposal->get_id()) + "\r\n";

	}
}

void Acceptor::receive_prepare_request()
{
	Message message(log_);
	while (true) {
		Proposal proposal;
		int32_t result = message.receiveMessage(&proposal, port_receive1_, "[" + std::string(ACTION_PREPARE_REQUEST) + "]" + std::string(ACCEPTOR) + "." + std::to_string(id_));
		if (result != MSG_SUCCESS) {
			std::string str_trace = "Acceptor::receive_prepare_request - FAILED!!! receive message " + std::to_string(result) + "\r\n";
			log_->trace(str_trace);
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
	Message message(log_);
	while (true) {
		Proposal proposal;
		int32_t result = message.receiveMessage(&proposal, port_receive2_, "[" + std::string(ACTION_ACCEPT_REQUEST) + "]" + std::string(ACCEPTOR) + "." + std::to_string(id_));

		count_accepted_request_++;
		if (count_accepted_request_ >= MAJORITY) {
			there_is_an_accepted_request_ = true;
			int send_decision_sent_without_error = send_decision(&proposal);			
			std::string str_trace = "[SENT Decision] - OK " + std::to_string(send_decision_sent_without_error) + "/" + std::to_string(NUM_NODES) + "\r\n";
			log_->trace(str_trace);
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
	Message message(log_);
	int send_decision_sent_without_error = 0;
	// El send_decision tiene que ser enviado a todos los Learners. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		if (message.sendMessage(proposal, PORT_BASE + PORT_LEARNER_SUFIX + PORT_RECEIVER1_SUFIX + id_node, std::string(ACCEPTOR) + "." + std::to_string(id_), ACTION_RESPONSE_TO_PREPARE_REQUEST, std::string(LEARNER) + "." + std::to_string(id_node)) != MSG_SUCCESS) {
			std::string str_trace = "Acceptor::send_decision - FAILED!!! to send_decision id:" + std::to_string(id_) + ", port: " + std::to_string(PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node) + "\r\n";
			log_->trace(str_trace);
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