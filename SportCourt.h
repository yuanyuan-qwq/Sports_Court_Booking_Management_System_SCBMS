#pragma once

#include<string>


#ifndef SportCourt_H
#define SportCourt_H

class SportCourt
{
public:
	std::string SportCourt_ID,SC_Name, SC_Status;
	float PricePerDay;
	std::string Staff_ID;
	SportCourt* next;
};
#endif // !SportCourt_H