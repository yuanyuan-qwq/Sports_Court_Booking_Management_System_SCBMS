#pragma once

#include<string>


#ifndef Staff_H
#define Staff_H

class Staff
{
public:
	std::string Staff_ID, Manager_ID, S_HpNo;
	std::string S_Name, S_Gender, S_Email,password,status;
	Staff* next;

	void StaffMenu();
};
#endif // !Staff_H