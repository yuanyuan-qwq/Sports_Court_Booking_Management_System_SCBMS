#pragma once
#include <string>
#ifndef customer_H
#define customer_H

class Customer
{

public:
	std::string Customers_ID, C_HpNo;
	std::string C_Name, C_Type, C_Address, C_Email, password,status;
	Customer* next;

};
#endif 