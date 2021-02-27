#pragma once

#include "Proposal.h"
#include <stdint.h>

class Acceptor
{
public:
	void start(uint32_t port);
	void responseToPrepareRequest(void* response);
	void decision(Proposal* proposal);

};

