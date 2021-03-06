#include "Proposer.h"


#include "Message.h"
#include "PaxosDefs.h"
#include <chrono>
#include <thread>




void Proposer::start(uint32_t id, Log *log)
{
	std::string str_message = "hola";	
	id_ = id;
	current_proposal_number_ = 0;
	port_send_ = PORT_BASE + PORT_PROPOSER_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive1_ = PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + id;
	port_receive2_ = PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER2_SUFIX + id;
	count_response_to_prepare_request_ = 0;

	std::thread thread_receive_response_to_prepare_request(&Proposer::receive_response_to_prepare_request, this);
	thread_receive_response_to_prepare_request.detach();
	log_ = log;
}

uint32_t Proposer::send_prepare_request(std::string value)
{	
	int prepare_request_sent_without_error = 0; 
	Message message(log_);

	Proposal proposal;
	current_proposal_number_++;
	proposal.set_id(id_);
	proposal.set_nack(false);
	proposal.set_none(false);
	proposal.set_proposal_number(current_proposal_number_);
	proposal.set_current_proposal_number(current_proposal_number_);
	proposal.set_value(value);


	// El prepare_request tiene que ser enviado a todos los Acceptors. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		
		if(message.sendMessage(&proposal, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node, std::string(PROPOSER) + "." + std::to_string(id_), ACTION_PREPARE_REQUEST, std::string(ACCEPTOR) + "." + std::to_string(id_node))) {
			std::string str_strace = "Proposer::prepare_request - FAILED!!! to prepare_request id:" + std::to_string(id_) + ", port:" + std::to_string(PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node) + "\r\n";
			log_->trace(str_strace);
		}
		else {
			prepare_request_sent_without_error++;
		}
	}
	return prepare_request_sent_without_error;
}

void Proposer::receive_response_to_prepare_request() 
{
	Message message(log_);
	while (true) {
		Proposal proposal;
		std::string str_trace;
		int32_t result = message.receiveMessage(&proposal, port_receive1_, "[" + std::string(ACTION_RESPONSE_TO_PREPARE_REQUEST) + "]" + std::string(PROPOSER) + "." + std::to_string(id_));
		if (result != MSG_SUCCESS) {
			str_trace = "Proposer::receive_response_to_prepare_request - FAILED!!! receive message " + std::to_string(result) + "\r\n";
			log_->trace(str_trace);
		}
		// Si es NACK
		if (proposal.get_nack() == true) {
			// No continuamos con la propuesta...
			str_trace = "Proposal[" + std::to_string(proposal.get_proposal_number()) + "." + std::to_string(proposal.get_id()) + ", " + proposal.get_value() + "] --> NACK\r\n";
			log_->trace(str_trace);
		}
		else {
			count_response_to_prepare_request_++;
			// Si hemos alcanzado la mayor�a...
			if (count_response_to_prepare_request_ >= MAJORITY) {
				// Hay una propuesta procensandose...
				if (proposal.get_none() == false) {
					// Marcamos el n�mero de la propuesta...
					proposal.set_proposal_number(proposal.get_current_proposal_number());
					// Enviamos el mensaje. 
					send_accept_resquest(&proposal);
				}
				// Si todav�a no hay ninguna propuesta 
				else if (proposal.get_none() == true) {
					// Mandamos nuestra propuesta...					
					send_accept_resquest(&proposal);
				}
			}
		}		
	}
}

uint32_t  Proposer::send_accept_resquest(Proposal* proposal)
{
	std::string str_trace;
	Message message(log_);
	// Enviamos la propuesta a todos los acceptor... 
	send_accept_sent_without_error_ = 0;
		// El prepare_request tiene que ser enviado a todos los Acceptors. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		if (message.sendMessage(proposal, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id_node, std::string(PROPOSER) + "." + std::to_string(id_), ACTION_ACCEPT_REQUEST, std::string(ACCEPTOR) + "." + std::to_string(id_node))) {
			str_trace = "Proposer::send_accept_resquest - FAILED!!! to prepare_request id:" +std::to_string(id_)+ ", port:" + std::to_string(PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id_node) + "\r\n";
			log_->trace(str_trace);
		}
		else {
			send_accept_sent_without_error_++;
		}
	}
	return send_accept_sent_without_error_;
}


bool  Proposer::client_request(std::string value) 
{
	int result = 0;

	
	result = send_prepare_request(value);
		 
	if (result != NUM_NODES) {
		log_->trace("Proposer::client_request - FAILED!!! to send proposal all proposer\r\n");
	}

	// Se ha enviado con �xito todos los mensajes. 
	return (result == NUM_NODES);
}



