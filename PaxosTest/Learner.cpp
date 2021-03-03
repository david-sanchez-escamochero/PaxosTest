#include "Learner.h"

#include "Message.h"
#include "PaxosDefs.h"
#include <thread>



void Learner::start(uint32_t id, Log *log)
{
	port_send_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_SENDER_SUFIX + id;
	port_receive_ = PORT_BASE + PORT_LEARNER_SUFIX + PORT_RECEIVER1_SUFIX + id;

	std::thread thread_receive_decision(&Learner::receive_decision, this);
	thread_receive_decision.detach();
	log_ = log;
}



void Learner::receive_decision()
{
	Message message(log_);
	while (true) {
		Proposal proposal;
		std::string str_trace;
		int32_t result = message.receiveMessage(&proposal, port_receive_, "[" + std::string(ACTION_DECISION) + "]" + std::string(LEARNER) + "." + std::to_string(id_));
		if (result != MSG_SUCCESS) {
			
			str_trace = "Learner::receive_decision - FAILED!!! receive message " + std::to_string(result) + "\r\n";
			log_->trace(str_trace);
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
			str_trace = "Propuesta ACEPTADA!!!! [" + std::to_string(proposal.get_proposal_number()) + ", " + proposal.get_value() + "]\r\n";
			log_->trace(str_trace);
		}
	}
}
