#include "ManagerController.h"

//ManagerController

void transform(sql::ResultSet* rs, Manager* Manager)
{
	Manager->Manager_ID = rs->getString("Manager_ID");
	Manager->M_Name = rs->getString("M_Name");
	Manager->M_Gender = rs->getString("M_Gender");
	Manager->M_HpNo = rs->getString("M_HpNo");
	Manager->M_Email = rs->getString("M_Email");
	Manager->password = rs->getString("password");
	Manager->status = rs->getString("status");

}

//Manager login
Manager* ManagerController::ManagerLogin(std::string Name, std::string password) {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE M_Name = ? AND password = ?");

	ps->setString(1, Name);
	ps->setString(2, password);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;

	if (rs->next())
	{
		manager = new Manager();
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return manager;
}

//insert,update,delete for manager
Manager* ManagerController::getManagerIDForInsert() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager ORDER BY Manager_ID DESC LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;

	if (rs->next())
	{
		manager = new Manager();
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return manager;

}

int ManagerController::insertManager(Manager* manager)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Manager (Manager_ID, M_Name, M_Gender, M_HpNo, M_Email, password, status) VALUES (?, ?, ?, ?, ?, ?, ?)");

	//ID auto incresing
	ps->setString(1, manager->Manager_ID);
	ps->setString(2, manager->M_Name);
	ps->setString(3, manager->M_Gender);
	ps->setString(4, manager->M_HpNo);
	ps->setString(5, manager->M_Email);
	ps->setString(6, manager->password);
	ps->setString(7, manager->status);

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

int ManagerController::updateManager(Manager* manager)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Manager SET M_Name = ?, M_Gender = ?, M_HpNo = ?, M_Email = ?,password = ?,status = ? WHERE Manager_ID = ?");

	ps->setString(1, manager->M_Name);
	ps->setString(2, manager->M_Gender);
	ps->setString(3, manager->M_HpNo);
	ps->setString(4, manager->M_Email);
	ps->setString(5, manager->password);
	ps->setString(6, manager->status);
	ps->setString(7, manager->Manager_ID);

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

int ManagerController::deleteManager(Manager* manager)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Manager WHERE Manager_ID = ?");

	ps->setString(1, manager->Manager_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "can't delete this account, because recorded data in other table\n";
		std::cout << "System will automaticly help you to Frozen this account\n";
		manager->status = "Frozen";
		numRowsAffected = updateManager(manager);
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}


//SEARCH
Manager* ManagerController::getManagerDetail_S_ID(std::string Manager_ID)	//search by ID (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE Manager_ID = ?");

	ps->setString(1, Manager_ID);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;

	if (rs->next())
	{
		manager = new Manager();
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;


	return manager;
}

Manager* ManagerController::getManagerDetail_S_Name(std::string M_Name)	//search by Name (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE M_Name = ?");

	ps->setString(1, M_Name);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;

	if (rs->next())
	{
		manager = new Manager();
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return manager;
}

Manager* ManagerController::getManagerDetail_S_Gender(std::string M_Gender)	//search by Gender (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE M_Gender = ?");

	ps->setString(1, M_Gender);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next())		//for multi output
	{
		if (manager == NULL) {
			manager = new Manager();
			head = manager;
		}
		else {
			manager->next = new Manager();
			manager = manager->next;
		}
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Manager* ManagerController::getManagerDetail_S_HpNo(std::string M_HpNo)	//search by HpNo (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE M_HpNo = ?");

	ps->setString(1, M_HpNo);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next())		//for multi output
	{
		if (manager == NULL) {
			manager = new Manager();
			head = manager;
		}
		else {
			manager->next = new Manager();
			manager = manager->next;
		}
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Manager* ManagerController::getManagerDetail_S_Email(std::string M_Email)	//search by Email (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE M_Email = ?");

	ps->setString(1, M_Email);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next())		//for multi output
	{
		if (manager == NULL) {
			manager = new Manager();
			head = manager;
		}
		else {
			manager->next = new Manager();
			manager = manager->next;
		}
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Manager* ManagerController::getManagerDetail_S_Status(std::string Status)	//search by Status (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager WHERE status = ?");

	ps->setString(1, Status);

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next())		//for multi output
	{
		if (manager == NULL) {
			manager = new Manager();
			head = manager;
		}
		else {
			manager->next = new Manager();
			manager = manager->next;
		}
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Manager* ManagerController::getAllManagerDetails()	//display all Manager detail
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Manager");

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;
	Manager* head = NULL;

	while (rs->next())		//for multi output
	{
		if (manager == NULL)
		{
			manager = new Manager();
			head = manager;
		}
		else
		{
			manager->next = new Manager();
			manager = manager->next;
		}
		transform(rs, manager);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


//SQL Algorithm
int ManagerController::getCountManagerForSelect() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT COUNT(*) as CountManager FROM manager");

	sql::ResultSet* rs = ps->executeQuery();
	Manager* manager = NULL;

	int cout;
	if (rs->next())
	{
		cout = rs->getInt("CountManager");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return cout;

}