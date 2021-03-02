#pragma once

#define PORT_BASE							6000
#define PORT_PROPOSER_SUFIX					100
#define PORT_ACCEPTOR_SUFIX					200
#define PORT_LEARNER_SUFIX					300
#define PORT_SENDER_SUFIX					10
#define PORT_RECEIVER1_SUFIX				20
#define PORT_RECEIVER2_SUFIX				30
#define NUM_NODES							3
#define MAJORITY							( ( NUM_NODES % 2 ) + 1 )
#define TO_RETRY							5000 // 5seg


#define ACCEPTOR							"Acceptor"
#define LEARNER								"Learner"
#define PROPOSER							"Proposer"

#define ACTION_PREPARE_REQUEST				"PrepareRequest"
#define ACTION_RESPONSE_TO_PREPARE_REQUEST	"ResponseToPrepareRequest"
#define ACTION_ACCEPT_REQUEST				"AcceptRequest"
#define ACTION_DECISION						"Decision"
#define ACTION_NACK_TO_PREPARE_REQUEST		"NackToPrepareRequest"