
#include "Proposal.h"


void Proposal::set_value(std::string value)
{
	value_ = value;
}

void Proposal::set_proposal_number(uint32_t proposal_number)
{
	proposal_number_ = proposal_number;
}

void Proposal::set_id(uint32_t id) {
	id_ = id;
}


std::string Proposal::get_value()
{
	return value_;
}

uint32_t Proposal::get_proposal_number()
{
	return proposal_number_;
}

uint32_t Proposal::get_id() {
	return id_;
}