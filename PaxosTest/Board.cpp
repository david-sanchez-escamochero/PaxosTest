#include "Board.h"
#include <stdint.h>
#include <string>




Board::Board(uint32_t id, std::string name, uint32_t port_send_proposer, uint32_t port_receive_proposer,
				uint32_t port_send_acceptor, uint32_t port_receive_acceptor,
				uint32_t port_send_learner, uint32_t port_receive_learner,
				uint16_t number_of_nodes, std::string file_name)
{
	id_ = id;
	name_ = name;
	port_send_proposer_ = port_send_proposer;
	port_send_acceptor_ = port_send_acceptor;
	port_send_learner_ = port_send_learner;
	port_receive_proposer_ = port_receive_proposer;
	port_receive_acceptor_ = port_receive_acceptor;
	port_receive_learner_ = port_receive_learner;

	number_of_nodes_ = number_of_nodes;
	file_name_ = file_name;
}

void Board::start()
{
	printf("Starting board\n");
	printf("ID: %d\n", id_);
	printf("Name: %s\n", name_.c_str());
	printf("Port send proposer: %d\n", port_send_proposer_);
	printf("Port receive proposer: %d\n", port_receive_proposer_);	
	printf("Port send acceptor: %d\n", port_send_acceptor_);
	printf("Port receive acceptor: %d\n", port_receive_acceptor_);
	printf("Port send learner: %d\n", port_send_learner_);			
	printf("Port receive learner: %d\n", port_receive_learner_);
	printf("Number of nodes: %d\n", number_of_nodes_);
	printf("File name: %s\n", file_name_.c_str());

	Proposal proposal;
	proposal.set_id(id_);
	proposal.set_proposal_number(21);
	proposal.set_value("hello");
	message_.sendMessage(&proposal, port_receive_proposer_);
	
	//message_.receiveMessage(&proposal, port_receive_proposer_);

	
	proposer_.start(port_send_proposer_, port_receive_proposer_, id_);
	acceptor_.start(port_send_acceptor_, port_receive_acceptor_, id_);
	learner_.start(port_send_learner_, port_receive_learner_, id_);
	client_.start(file_name_, &proposer_);
	
}


