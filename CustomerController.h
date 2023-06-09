#pragma once
#include "customer.h"
#include "DatabaseConnection.h"


#ifndef CustomerController_H
#define CustomerController_H

class CustomerController
{
public:

	//login
	Customer* CustomerLogin(std::string C_Name, std::string password);

	//Manager{
	
	//insert,update,delete
	Customer* getCustomerIDForInsert();
	int insertCustomer(Customer* customer);
	int updateCustomer(Customer* customer);		//ID to update
	int deleteCustomer(Customer* customer);		//ID to Delete

	//SEARCH
	Customer* getCustomerDetail_S_ID(std::string Customers_ID);		//search by ID (unique)
	Customer* getCustomerDetail_S_Name(std::string C_Name);			//search by Name (unique)
	Customer* getCustomerDetail_S_Type(std::string C_Type);			//search by Type (multi)
	Customer* getCustomerDetail_S_Address(std::string C_Address);	//search by Address(multi)
	Customer* getCustomerDetail_S_HpNo(std::string C_HpNo);			//search by HpNo(multi)
	Customer* getCustomerDetail_S_Email(std::string C_Email);		//search by Email(multi)
	Customer* getCustomerDetail_S_Status(std::string status);		//search by Status (multi)
	Customer* getAllCustomerDetails();								//display all customer detial
	
	//}Manager

};

#endif