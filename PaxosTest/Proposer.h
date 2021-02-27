#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"

class Proposer
{
public:
	void start(uint32_t port);
	void prepare_request(uint32_t proposal_number);
	void accept_resquest(Proposal *proposal);
	void client_request(std::string);

private:
	Message message;
};

