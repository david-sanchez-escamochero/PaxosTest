#include "Client.h"
#include <iostream>
#include <string>
#include <fstream>


void Client::start(std::string file_name, Proposer* proposer)
{
	this->file_name = file_name;	
    if (proposer != NULL) {

        if (file_name != "") {
            read_file();
        }
        else
            printf("Client::start - FAILED!!! file_name  == '' \r\n");
    }
    else 
        printf("Client::start - FAILED!!! proposer == NULL\r\n");
}


void Client::read_file() {

    if (file_name != "") {
        std::string line;
        //std::ifstream infile(file_name + ".txt");
        std::ifstream infile("C:\\Users\\ASUS_PORTATIL\\source\\repos\\PaxosTest\\Debug\\" + file_name + ".txt");
        
    
        while (std::getline(infile, line))
        {
            printf("Name: %s\r\n", line.c_str());
            proposer->client_request(line);            
        }
    }
    else
        printf("Client::read_file - FAILED!!! to read file\r\n");
}

void Client::send_request()
{
}
