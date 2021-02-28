#pragma once

#include <string>
#include <stdint.h>
#include "Learner.h"
#include "Proposer.h"
#include "Acceptor.h"
#include "Client.h"
#include "Message.h"

class Board
{
	public:
		Board(uint32_t id, std::string name,  /*uint32_t port_send_proposer, uint32_t port_receive_proposer, 
											  uint32_t port_send_acceptor, uint32_t port_receive_acceptor, 
											  uint32_t port_send_learner, uint32_t port_receive_learner, 
											  uint16_t number_of_nodes,*/ std::string file_name);
		void start();
	private:
		uint32_t id_;
		std::string name_;
		//uint32_t port_send_proposer_;
		//uint32_t port_receive_proposer_;
		//uint32_t port_send_acceptor_;
		//uint32_t port_receive_acceptor_;
		//uint32_t port_send_learner_;				
		//uint32_t port_receive_learner_;

		uint16_t number_of_nodes_;
		std::string file_name_;

		Client	 client_;
		Proposer proposer_;
		Acceptor acceptor_;
		Learner	 learner_;
		Message  message_;

};

