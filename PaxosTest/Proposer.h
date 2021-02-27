#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"

class Proposer
{
public:
	void start(uint32_t port);
	void prepareRequest(uint32_t proposal_number);
	void acceptResquest(Proposal *proposal);

private:
	Message message;
};

