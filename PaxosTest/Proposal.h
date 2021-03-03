#pragma once

#include <stdint.h>
#include <string>

class Proposal
{

public:
	Proposal();
	void set_value(std::string value);
	void set_proposal_number(uint32_t proposal_number);
	void set_id(uint32_t id);
	std::string get_value();
	uint32_t get_proposal_number();
	uint32_t get_current_proposal_number();
	void	 set_current_proposal_number(uint32_t current_proposal_number);
	uint32_t get_id();
	void set_none(bool none);
	bool get_none();
	void set_nack(bool nack);
	bool get_nack();

private:
	std::string value_;
	uint32_t proposal_number_;
	uint32_t id_;	
	bool none_; 
	bool nack_;
	uint32_t current_proposal_number_;
};

