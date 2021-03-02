#include "Client.h"
#include <iostream>
#include <string>
#include <fstream>


void Client::start(std::string file_name, Proposer* proposer)
{
	file_name_ = file_name;	
    proposer_ = proposer;
    if (proposer_ != NULL) {

        if (file_name_ != "") {
            read_file();
        }
        else
            printf("Client::start - FAILED!!! file_name  == '' \r\n");
    }
    else 
        printf("Client::start - FAILED!!! proposer == NULL\r\n");
}


void Client::read_file() {

    if (file_name_ != "") {
        std::string value;
        //std::ifstream infile(file_name + ".txt");
        std::ifstream infile(".\\" + file_name_ + ".txt");
        
    
        while (std::getline(infile, value))
        {            
            proposer_->client_request(value);            
        }
    }
    else
        printf("Client::read_file - FAILED!!! to read file\r\n");
}

void Client::send_request()
{
}
