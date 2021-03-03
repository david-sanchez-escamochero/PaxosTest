#include "Client.h"
#include <iostream>
#include <string>
#include <fstream>


void Client::start(std::string file_name, Proposer* proposer, Log *log)
{
	file_name_ = file_name;	
    proposer_ = proposer;
    log_ = log;
    if (proposer_ != NULL) {

        if (file_name_ != "") {
            read_file();
        }
        else
            log_->trace("Client::start - FAILED!!! file_name  == '' \r\n");
    }
    else 
        log_->trace("Client::start - FAILED!!! proposer == NULL\r\n");
}


void Client::read_file() {

    if (file_name_ != "") {
        std::string value;
        //std::ifstream infile(file_name + ".txt");
        std::ifstream infile(".\\" + file_name_ + ".txt");
        
    
        while (std::getline(infile, value))
        {            
            if (!proposer_->client_request(value)) {
                log_->trace("Client::read_file - FAILED!!! to client_request\r\n");
            }
        }
    }
    else
        log_->trace("Client::read_file - FAILED!!! to read file\r\n");
}

void Client::send_request()
{
}
