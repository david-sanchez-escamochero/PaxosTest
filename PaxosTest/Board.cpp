#include "Board.h"
#include "Learner.h"
#include "Proposer.h"
#include "Acceptor.h"
#include "Client.h"
#include <stdint.h>
#include <string>
#include "Message.h"


Board::Board(uint32_t id, std::string name, uint32_t port_proposer, uint32_t port_acceptor, uint32_t port_learner, uint16_t number_of_nodes) {
	this->id = id;
	this->name = name;
	this->port_proposer = port_proposer;
	this->port_acceptor = port_acceptor;
	this->port_learner = port_learner;
	this->number_of_nodes = number_of_nodes;
}

void Board::start()
{
	printf("Starting board\n");
	printf("ID: %d\n", id);
	printf("Name: %s\n", name.c_str());
	printf("Port proposer: %d\n", port_proposer);
	printf("Port acceptor: %d\n", port_acceptor);
	printf("Port learner: %d\n", port_learner);	
	printf("Number of nodes: %d\n", number_of_nodes);

	Client	 client; 
	Proposer proposer; 
	Acceptor acceptor;
	Learner	 learner;
	Message  message;

	client.start();
	proposer.start(port_proposer);
	acceptor.start(port_acceptor);
	learner.start(port_learner);
	
}


