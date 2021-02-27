#pragma once

#include <string>
#include "Proposer.h"

class Client
{
public:
	void start(std::string file_name, Proposer *proposer);
	void read_file();
	void send_request();
private:
	std::string file_name;
	Proposer* proposer;
};

