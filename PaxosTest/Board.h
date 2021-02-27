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
		Board(uint32_t id, std::string name,  uint32_t port_proposer, uint32_t port_acceptor, uint32_t port_learner, uint16_t number_of_nodes, std::string file_name);
		void start();
	private:
		uint32_t id;
		std::string name;
		uint32_t port_proposer;
		uint32_t port_acceptor;
		uint32_t port_learner;
		uint16_t number_of_nodes;
		std::string file_name;

		Client	 client;
		Proposer proposer;
		Acceptor acceptor;
		Learner	 learner;
		Message  message;

};

