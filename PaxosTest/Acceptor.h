#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"

class Acceptor
{
public:
	void start(uint32_t id);
	void response_to_prepare_request(Proposal* proposal);
	void decision(Proposal* proposal);
	void receive_prepare_request();
	void nack_prepare_request(Proposal* proposal);
	void accept_request();

private:
	uint32_t id_;
	uint32_t proposal_number_;
	uint32_t port_send_;
	uint32_t port_receive1_;
	uint32_t port_receive2_;
	Message message_;
	Proposal proposal_;
	std::string value_;
	bool accepted_request;
	uint32_t count_accepted_request; 

};

