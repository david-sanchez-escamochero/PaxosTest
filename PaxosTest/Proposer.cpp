#include "Proposer.h"


#include "Message.h"
#include "PaxosDefs.h"
#include <chrono>
#include <thread>




void Proposer::start(uint32_t id)
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

}

uint32_t Proposer::send_prepare_request(std::string value)
{	
	int prepare_request_sent_without_error = 0; 

	// El prepare_request tiene que ser enviado a todos los Acceptors. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		if(message_.sendMessage(&new_proposal_, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node, std::string(PROPOSER) + "." + std::to_string(id_), ACTION_PREPARE_REQUEST, std::string(ACCEPTOR) + "." + std::to_string(id_node))) {
			printf("Proposer::prepare_request - FAILED!!! to prepare_request id:%d, port:%d\n", id_, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + id_node);
		}
		else {
			prepare_request_sent_without_error++;
		}
	}
	return prepare_request_sent_without_error;
}

void Proposer::receive_response_to_prepare_request() 
{
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive1_, "[" + std::string(ACTION_RESPONSE_TO_PREPARE_REQUEST) + "]" + std::string(PROPOSER) + "." + std::to_string(id_));
		if (result != MSG_SUCCESS) {
			printf("Proposer::receive_response_to_prepare_request - FAILED!!! receive message %d\r\n", result);
		}
		// Si es NACK
		if (proposal.get_nack() == true) {
			// No continuamos con la propuesta...
			printf("Proposal[%d.%d, %s] --> NACK\r\n", proposal.get_proposal_number(), proposal.get_id(), proposal.get_value().c_str());
		}
		else {
			count_response_to_prepare_request_++;
			// Si hemos alcanzado la mayoría...
			if (count_response_to_prepare_request_ >= MAJORITY) {
				// Hay una propuesta procensandose...
				if (proposal.get_none() == false) {
					// Marcamos el número de la propuesta...
					proposal.set_proposal_number(current_proposal_number_);
					// Enviamos el mensaje. 
					send_accept_resquest(&proposal);
				}
				// Si todavía no hay ninguna propuesta 
				else if (proposal.get_none() == true) {
					// Mandamos nuestra propuesta...
					new_proposal_.set_value(new_value_);
					send_accept_resquest(&new_proposal_);
				}
			}
		}		
	}
}

uint32_t  Proposer::send_accept_resquest(Proposal* proposal)
{
	// Enviamos la propuesta a todos los acceptor... 
	send_accept_sent_without_error_ = 0;
		// El prepare_request tiene que ser enviado a todos los Acceptors. 
	for (int id_node = 0; id_node < NUM_NODES; id_node++) {
		if (message_.sendMessage(proposal, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id_node, std::string(PROPOSER) + "." + std::to_string(id_), ACTION_ACCEPT_REQUEST, std::string(ACCEPTOR) + "." + std::to_string(id_node))) {
			printf("Proposer::send_accept_resquest - FAILED!!! to prepare_request id:%d, port:%d\n", id_, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER2_SUFIX + id_node);
		}
		else {
			send_accept_sent_without_error_++;
		}
	}
	return send_accept_sent_without_error_;
}

void Proposer::create_new_proposal(std::string value)
{
	current_proposal_number_++;
	new_proposal_.set_id(id_);
	new_proposal_.set_nack(false);
	new_proposal_.set_none(false);
	new_proposal_.set_proposal_number(current_proposal_number_);	
	new_proposal_.set_value("");

	new_value_ = value;
}


bool  Proposer::client_request(std::string value) 
{
	int result = 0;

	// Guardamos la propuesta...
	create_new_proposal(value); 


	while (result < MAJORITY){
		 result = send_prepare_request(value);
		 
		 if (result < MAJORITY) {
			 // Esperamos un tiempo antes de volver a enviar. 
			 std::this_thread::sleep_for(std::chrono::milliseconds(TO_RETRY));
		 }
	}

	// Se ha enviado con éxito todos los mensajes. 
	return true;
}



