#pragma once
#include "Staff.h"
#include "DatabaseConnection.h"

#ifndef StaffController_H
#define StaffController_H

class StaffController
{
public:
	//login
	Staff* StaffLogin(std::string Name, std::string password);

	//{Manager
	//insert,update,delete
	Staff* getStaffIDForInsert();
	int insertStaff(Staff* Staff);
	int updateStaff(Staff* Staff);		//ID to update
	int deleteStaff(Staff* Staff);		//ID to Delete

	//SEARCH
	Staff* getStaffDetail_S_ID(std::string Staff_ID);			//search by Staff ID (unique)
	Staff* getStaffDetail_S_MID(std::string Manager_ID);		//search by Manager ID (multi)
	Staff* getStaffDetail_S_Name(std::string S_Name);			//search by Name (unique)
	Staff* getStaffDetail_S_Gender(std::string S_Gender);		//search by Gender (multi)
	Staff* getStaffDetail_S_HpNo(std::string S_HpNo);			//search by HpNo(multi)
	Staff* getStaffDetail_S_Email(std::string S_Email);			//search by Email(multi)
	Staff* getStaffDetail_S_Status(std::string status);			//search by Status (multi)
	Staff* getAllStaffDetails();								//display all Staff detial
	//}Manager
};
#endif // !Staff_H