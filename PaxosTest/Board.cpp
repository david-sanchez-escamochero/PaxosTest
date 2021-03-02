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
	printf("***************************************\r\n");
	printf("  Starting board\r\n");
	printf("  ID: %d\r\n", id_);
	printf("  Name: %s\r\n", name_.c_str());
	printf("  File name: %s\r\n", file_name_.c_str());
	printf("***************************************\r\n");
	
	proposer_.start(id_);
	acceptor_.start(id_);
	learner_.start(id_);
	client_.start(file_name_, &proposer_);	
}


