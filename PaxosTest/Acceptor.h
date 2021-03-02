#pragma once

#include "Proposal.h"
#include <stdint.h>
#include "Message.h"
#include <mutex>

class Acceptor
{
public:
	void start(uint32_t id);
	void send_response_to_prepare_request(Proposal* proposal);	
	void receive_prepare_request();
	void send_nack_prepare_request(Proposal* proposal);
	void receive_accept_request();
	int send_decision(Proposal* proposal);

private:
	uint32_t id_;
	uint32_t proposal_number_;
	uint32_t port_send_;
	uint32_t port_receive1_;
	uint32_t port_receive2_;
	Message message_;
	Proposal proposal_;
	std::string value_;
	bool there_is_an_accepted_request_;
	uint32_t count_accepted_request_; 


	std::mutex mu_;
	bool get_there_is_an_accepted_request();
	void set_there_is_an_accepted_request(bool there_is_an_accepted_request);
};

