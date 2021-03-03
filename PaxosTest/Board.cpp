#include "Board.h"
#include <stdint.h>
#include <string>




Board::Board(uint32_t id, std::string name, std::string file_name, Log* log)
{
	id_ = id;
	name_ = name;	
	file_name_ = file_name;
	log_ = log;
}

void Board::start()
{
	std::string str_trace;
	log_->trace("***************************************\r\n");
	log_->trace("  Starting board\r\n");
	str_trace = "  ID: " + std::to_string(id_) + "\r\n";
	log_->trace(str_trace);
	str_trace = "  Name: " + name_ + "\r\n";
	log_->trace(str_trace);
	str_trace = "  File name: " + file_name_ + "\r\n";
	log_->trace(str_trace);
	log_->trace("***************************************\r\n");
	


	proposer_.start(id_, log_);
	acceptor_.start(id_, log_);
	learner_.start(id_, log_);
	client_.start(file_name_, &proposer_, log_);
}


