#pragma once

#include <string>
#include <stdint.h>
#include "Learner.h"
#include "Proposer.h"
#include "Acceptor.h"
#include "Client.h"
#include "Log.h"

class Board
{
	public:
		Board(uint32_t id, std::string name,  std::string file_name, Log *log);
		void start();
	private:
		uint32_t id_;
		std::string name_;
		uint16_t number_of_nodes_;
		std::string file_name_;

		Client	 client_;
		Proposer proposer_;
		Acceptor acceptor_;
		Learner	 learner_;		
		Log		*log_;		

};

