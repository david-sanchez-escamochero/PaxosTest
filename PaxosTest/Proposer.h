#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"

class Proposer
{
public:
	void start(uint32_t id);
	uint32_t  prepare_request(std::string value);
	void accept_resquest(Proposal *proposal);
	bool client_request(std::string value);
	uint32_t get_proposal_number();
	void response_to_prepare_request();

private:
	Message message_;
	uint32_t id_;
	uint32_t proposal_number_;	
	uint32_t port_send_;
	uint32_t  port_receive_;
};

