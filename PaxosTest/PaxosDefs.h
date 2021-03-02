#pragma once

#define PORT_BASE				6000
#define PORT_PROPOSER_SUFIX		100
#define PORT_ACCEPTOR_SUFIX		200
#define PORT_LEARNER_SUFIX		300
#define PORT_SENDER_SUFIX		10
#define PORT_RECEIVER1_SUFIX	20
#define PORT_RECEIVER2_SUFIX	30
#define NUM_NODES				3
#define MAJORITY				( ( NUM_NODES % 2 ) + 1 )
#define TO_RETRY				5000 // 5seg


