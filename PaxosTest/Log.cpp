#include "Log.h"
#include <thread>
#include <chrono>
#include <ctime> 


unsigned long long GetTickCount()
{
	long long tick; 

	try {
		using namespace std::chrono;
		tick = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
	}
	catch (...)
	{
		tick = 0;
	}


	return tick; 
}


Log::Log() 
{
	count_line_ = 0;
}

void Log::trace(std::string str_log)
{		
		//std::lock_guard<std::mutex> guard(mu_); // RAII
		//str_log = std::to_string(count_line_++) + ".-" + "[" + std::to_string(GetTickCount()) + "]" + str_log;
		printf(str_log.c_str());
}
