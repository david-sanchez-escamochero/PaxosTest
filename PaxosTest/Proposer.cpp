#include "Proposer.h"


#include "Message.h"
#include "PaxosDefs.h"
#include <chrono>
#include <thread>




void Proposer::start(uint32_t id)
{
	std::string str_message = "hola";	
	id_ = id;
	proposal_number_ = 1;
	port_send_ = PORT_BASE + PORT_PROPOSER_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive_ = PORT_BASE + PORT_PROPOSER_SUFIX + PORT_RECEIVER1_SUFIX + id;
}

uint32_t Proposer::prepare_request(std::string value)
{	
	int prepare_request_sent_without_error = 0; 
	Proposal proposal; 
	proposal.set_id(id_);
	proposal.set_value(value);
	proposal.set_proposal_number(proposal_number_);

	// El prepare_request tiene que ser enviado a todos los Acceptors. 
	for (int count = 0; count < NUM_NODES; count++) {
		if(message_.sendMessage(&proposal, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + count)) {
			printf("Proposer::prepare_request - FAILED!!! to prepare_request id:%d, port:%d\n", id_, PORT_BASE + PORT_ACCEPTOR_SUFIX + PORT_RECEIVER1_SUFIX + count);
		}
		else {
			prepare_request_sent_without_error++;
		}
	}
	return prepare_request_sent_without_error;
}

void Proposer::response_to_prepare_request() 
{
	//message.receiveMessage();
}

void Proposer::accept_resquest(Proposal* proposal)
{
}

bool  Proposer::client_request(std::string value) 
{
	int result = 0;
	while (result < MAJORITY){
		 result = prepare_request(value);
		 
		 if (result < MAJORITY) {
			 // Esperamos un tiempo antes de volver a enviar. 
			 std::this_thread::sleep_for(std::chrono::milliseconds(TO_RETRY));
		 }
	}

	// Se ha enviado con éxito todos los mensajes. 
	return true;
}

uint32_t Proposer::get_proposal_number() {
	return proposal_number_;
}


