// PaxosTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"
#include <stdint.h>
#include <string>
#include "Log.h"

void usage(Log *log) {
    
    log->trace("Help:\r\n");
    log->trace("Param (1) Board ID:\r\n");
    log->trace("Param (2) Board name\r\n");
    log->trace("Param (3) Name of file\r\n");
}

int main(int argc, char** argv)
{
    Log log;
    if (argc < 3)
        usage(&log);
    else {        
        Board board(std::stoi(argv[1]), argv[2], argv[3], &log);
        board.start();
    }
}
