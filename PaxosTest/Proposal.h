#pragma once

#include <stdint.h>
#include <string>

class Proposal
{

public:
	void set_value(std::string value);
	void set_proposal_number(uint32_t proposal_number);
	void set_id(uint32_t id);
	std::string get_value();
	uint32_t get_proposal_number();
	uint32_t get_id();


private:
	std::string value_;
	uint32_t proposal_number_;
	uint32_t id_;	
};

