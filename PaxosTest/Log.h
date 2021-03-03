#pragma once

#include <string>
#include <mutex>

class Log
{
public:
	Log();
	void trace(std::string str_log);
private:
	uint32_t count_line_;
	std::mutex mu_;

};

