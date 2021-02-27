#pragma once

#include <stdint.h>
#include <string>

class Proposal
{

public:
	void set_value(std::string value);
	void set_proposal_number(uint32_t proposal_number);

private:
	std::string value;
	uint32_t proposal_number;
	uint32_t id;
	uint32_t n;
};

