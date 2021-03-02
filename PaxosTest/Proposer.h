#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"
#include "Proposal.h"

class Proposer
{
public:
	void start(uint32_t id);
	uint32_t  send_prepare_request(std::string value);
	uint32_t  send_accept_resquest(Proposal *proposal);
	bool client_request(std::string value);
	
	void receive_response_to_prepare_request();

private:
	Message message_;
	uint32_t id_;
	uint32_t current_proposal_number_;	
	uint32_t port_send_;
	uint32_t  port_receive1_;
	uint32_t  port_receive2_;
	uint32_t  count_response_to_prepare_request_;
	uint32_t  send_accept_sent_without_error_;
	Proposal  new_proposal_;

	void	 create_new_proposal(std::string value);
};

