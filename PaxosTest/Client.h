#pragma once

#include <string>
#include "Proposer.h"
#include "Log.h"

class Client
{
public:
	void start(std::string file_name, Proposer *proposer, Log* log);
	void read_file();
	void send_request();
private:
	std::string file_name_;
	Proposer* proposer_;
	Log *log_;
};

