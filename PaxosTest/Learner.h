#pragma once

#include <stdint.h>
#include "Message.h"
#include "Log.h"

class Learner
{
public:
	void start(uint32_t id, Log* log);
private:
	uint32_t id_;
	uint32_t proposal_number_;
	uint32_t port_send_;
	uint32_t port_receive_;	
	void receive_decision();
	Proposal current_decision_proposal_;
	int count_decision_received_;
	Log *log_;

};

