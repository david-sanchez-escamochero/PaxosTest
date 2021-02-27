#pragma once

#include <stdint.h>


class Learner
{
public:
	void start(uint32_t port_send, uint32_t  port_receive, uint32_t id);
private:
	uint32_t id_;
	uint32_t proposal_number_;
	uint32_t port_send_;
	uint32_t port_receive_;

};

