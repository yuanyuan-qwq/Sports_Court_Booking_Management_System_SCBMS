#include "StaffController.h"

//StaffController

void transform(sql::ResultSet* rs, Staff* Staff)
{
	Staff->Staff_ID = rs->getString("Staff_ID");
	Staff->Manager_ID = rs->getString("Manager_ID");
	Staff->S_Name = rs->getString("S_Name");
	Staff->S_Gender = rs->getString("S_Gender");
	Staff->S_HpNo = rs->getString("S_HpNo");
	Staff->S_Email = rs->getString("S_Email");
	Staff->password = rs->getString("password");
	Staff->status = rs->getString("status");

}

//Manager login
Staff* StaffController::StaffLogin(std::string Name, std::string password) {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE S_Name = ? AND password = ?");

	ps->setString(1, Name);
	ps->setString(2, password);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;

	if (rs->next())
	{
		staff = new Staff();
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}


//insert,update,delete for Staff
Staff* StaffController::getStaffIDForInsert() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff ORDER BY Staff_ID DESC LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;

	if (rs->next())
	{
		staff = new Staff();
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;

}

int StaffController::insertStaff(Staff* staff)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Staff (Staff_ID,Manager_ID, S_Name, S_Gender, S_HpNo, S_Email, password, status) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

	//ID auto incresing
	ps->setString(1, staff->Staff_ID);
	ps->setString(2, staff->Manager_ID);
	ps->setString(3, staff->S_Name);
	ps->setString(4, staff->S_Gender);
	ps->setString(5, staff->S_HpNo);
	ps->setString(6, staff->S_Email);
	ps->setString(7, staff->password);
	ps->setString(8, staff->status);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "duplecate UserName!!\n";
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}
	ps->close();

	delete ps;

	return numRowsAffected;
}

int StaffController::updateStaff(Staff* staff)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Staff SET Manager_ID = ?, S_Name = ?, S_Gender = ?, S_HpNo = ?, S_Email = ?,password = ? ,status = ? WHERE Staff_ID = ?");

	ps->setString(1, staff->Manager_ID);
	ps->setString(2, staff->S_Name);
	ps->setString(3, staff->S_Gender);
	ps->setString(4, staff->S_HpNo);
	ps->setString(5, staff->S_Email);
	ps->setString(6, staff->password);
	ps->setString(7, staff->status);
	ps->setString(8, staff->Staff_ID);


	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "duplecate UserName!!\n";
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}

int StaffController::deleteStaff(Staff* staff)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Staff WHERE Staff_ID = ?");

	ps->setString(1, staff->Staff_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "can't delete this account, because recorded data in other table\n";
		std::cout << "System will automaticly help you to Frozen this account\n";
		staff->status = "Frozen";
		numRowsAffected = updateStaff(staff);
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}


//SEARCH
Staff* StaffController::getStaffDetail_S_ID(std::string Staff_ID)	//search by ID (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE Staff_ID = ?");

	ps->setString(1, Staff_ID);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;

	if (rs->next())
	{
		staff = new Staff();
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;


	return staff;
}

Staff* StaffController::getStaffDetail_S_MID(std::string Manager_ID) 
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE Manager_ID = ?");

	ps->setString(1, Manager_ID);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* StaffController::getStaffDetail_S_Name(std::string S_Name)	//search by Name (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE S_Name = ?");

	ps->setString(1, S_Name);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;

	if (rs->next())
	{
		staff = new Staff();
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return staff;
}

Staff* StaffController::getStaffDetail_S_Gender(std::string S_Gender)	//search by Gender (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE S_Gender = ?");

	ps->setString(1, S_Gender);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* StaffController::getStaffDetail_S_HpNo(std::string S_HpNo)	//search by HpNo (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE S_HpNo = ?");

	ps->setString(1, S_HpNo);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* StaffController::getStaffDetail_S_Email(std::string S_Email)	//search by Email (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE S_Email = ?");

	ps->setString(1, S_Email);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* StaffController::getStaffDetail_S_Status(std::string status)	//search by Status (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff WHERE status = ?");

	ps->setString(1, status);

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Staff* StaffController::getAllStaffDetails()	//display all Staff detial
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Staff");

	sql::ResultSet* rs = ps->executeQuery();
	Staff* staff = NULL;
	Staff* head = NULL;

	while (rs->next())		//for multi output
	{
		if (staff == NULL) {
			staff = new Staff();
			head = staff;
		}
		else {
			staff->next = new Staff();
			staff = staff->next;
		}
		transform(rs, staff);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}