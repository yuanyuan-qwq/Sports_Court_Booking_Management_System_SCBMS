#pragma once
#include "Manager.h"
#include "DatabaseConnection.h"

#ifndef ManagerController_H
#define ManagerController_H

class ManagerController
{
public:
	//login
	Manager* ManagerLogin(std::string Name, std::string password);

	//insert,update,delete
	Manager* getManagerIDForInsert();
	int insertManager(Manager* Manager);
	int updateManager(Manager* Manager);		//ID to update
	int deleteManager(Manager* Manager);		//ID to Delete

	//SEARCH
	Manager* getManagerDetail_S_ID(std::string Manager_ID);		//search by ID (unique)
	Manager* getManagerDetail_S_Name(std::string M_Name);			//search by Name (unique)
	Manager* getManagerDetail_S_Gender(std::string M_Gender);		//search by Gender (multi)
	Manager* getManagerDetail_S_HpNo(std::string M_HpNo);			//search by HpNo(multi)
	Manager* getManagerDetail_S_Email(std::string M_Email);			//search by Email(multi)
	Manager* getManagerDetail_S_Status(std::string Status);		//search by Gender (multi)
	Manager* getAllManagerDetails();								//display all Manager detial

	//SQL Algorithm
	int getCountManagerForSelect();
};
#endif // !manager_H