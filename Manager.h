#pragma once

#include<string>


#ifndef Manager_H
#define Manager_H

class Manager
{
public:
	std::string Manager_ID, M_HpNo;
	std::string M_Name, M_Gender, M_Email, password,status;
	Manager* next;

};
#endif // !Manager_H