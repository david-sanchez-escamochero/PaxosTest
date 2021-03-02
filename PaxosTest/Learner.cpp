#include "Learner.h"

#include "Message.h"
#include "PaxosDefs.h"

void Learner::start(uint32_t id)
{
	port_send_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_RECEIVER1_SUFIX + id;
}



void Learner::receive_decision()
{
	while (true) {
		Proposal proposal;
		int32_t result = message_.receiveMessage(&proposal, port_receive_);
		if (result != MSG_SUCCESS) {
			printf("Learner::receive_decision - FAILED!!! receive message %d\r\n", result);
		}
		else if (current_decision_proposal_.get_proposal_number() == proposal.get_proposal_number()) {
			count_decision_received_++;
		}
		else if (current_decision_proposal_.get_proposal_number() == proposal.get_proposal_number()) {
			current_decision_proposal_.set_proposal_number(proposal.get_proposal_number());
			current_decision_proposal_.set_value(proposal.get_value());
			count_decision_received_ = 1;
		}

		if (count_decision_received_ >= MAJORITY) {
			// Guardar propuesta. 
			printf("Propesta ACEPTADA!!!! [%d, %s]", proposal.get_proposal_number(), proposal.get_value().c_str());
		}
	}
}
