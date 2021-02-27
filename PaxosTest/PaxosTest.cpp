// PaxosTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include <stdint.h>
#include <string>

void usage() {
    printf("Help:\n");
    printf("Param (1) Board ID:\n");
    printf("Param (2) Board name\n");
    printf("Param (3) Proposal port\n");
    printf("Param (4) Acceptor port\n");
    printf("Param (5) Learner  port\n");    
    printf("Param (6) Number of nodes\n");
    printf("Param (7) Name of file\n");
}

int main(int argc, char** argv)
{
    if (argc < 6)
        usage();
    else {        
        Board board(std::stoi(argv[1]), argv[2], std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]), argv[7]);
        board.start();
    }
}
