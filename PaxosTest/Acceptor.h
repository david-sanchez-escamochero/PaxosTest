#pragma once

#include "Proposal.h"
#include <stdint.h>

class Acceptor
{
public:
	void start(uint32_t port_send, uint32_t  port_receive, uint32_t id);
	void responseToPrepareRequest(void* response);
	void decision(Proposal* proposal);

private:
	uint32_t id_;
	uint32_t proposal_number_;
	uint32_t port_send_;
	uint32_t port_receive_;

};

