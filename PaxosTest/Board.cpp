#include "Board.h"
#include <stdint.h>
#include <string>




Board::Board(uint32_t id, std::string name, std::string file_name)
{
	id_ = id;
	name_ = name;	
	file_name_ = file_name;
}

void Board::start()
{
	printf("Starting board\n");
	printf("ID: %d\n", id_);
	printf("Name: %s\n", name_.c_str());
	printf("File name: %s\n", file_name_.c_str());

	//Proposal proposal;
	//proposal.set_id(id_);
	//proposal.set_proposal_number(21);
	//proposal.set_value("hello");
	//message_.sendMessage(&proposal, port_receive_proposer_);
	
	//message_.receiveMessage(&proposal, port_receive_proposer_);

	
	proposer_.start(id_);
	acceptor_.start(id_);
	learner_.start(id_);
	client_.start(file_name_, &proposer_);
	
}


