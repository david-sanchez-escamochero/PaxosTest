
#include "Proposal.h"


Proposal::Proposal() {
	value_  = "";
	proposal_number_ = 0;
	id_ = 0;
	none_ = false;
	nack_ = false;
}

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

uint32_t Proposal::get_current_proposal_number()
{
	return current_proposal_number_;
}

void Proposal::set_current_proposal_number(uint32_t current_proposal_number)
{
	current_proposal_number_ = current_proposal_number;
}

uint32_t Proposal::get_id() {
	return id_;
}

void Proposal::set_none(bool none) {
	none_ = none;
}

bool Proposal::get_none() {
	return none_;
}

void Proposal::set_nack(bool nack) {
	nack_ = nack;
}

bool Proposal::get_nack() {
	return nack_;
}


