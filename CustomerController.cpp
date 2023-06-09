#include "CustomerController.h"

//Customer controller

void transform(sql::ResultSet* rs, Customer* customer)
{
	customer->Customers_ID = rs->getString("Customers_ID");
	customer->password = rs->getString("password");
	customer->C_Name = rs->getString("C_Name");
	customer->C_Type = rs->getString("C_Type");
	customer->C_Address = rs->getString("C_Address");
	customer->C_HpNo = rs->getString("C_HpNo");
	customer->C_Email = rs->getString("C_Email");
	customer->status = rs->getString("status");

}

//Customer login
Customer* CustomerController::CustomerLogin(std::string C_Name, std::string password) {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM customers WHERE C_Name = ? AND password = ?");

	ps->setString(1, C_Name);
	ps->setString(2, password);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;

	if (rs->next())
	{
		customer = new Customer();
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}


//insert,update,delete for Customer
Customer* CustomerController::getCustomerIDForInsert() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers ORDER BY Customers_ID DESC LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;

	if (rs->next())
	{
		customer = new Customer();
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;

}

int CustomerController::insertCustomer(Customer* customer)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO customers (Customers_ID, C_Name, C_Type, C_Address, C_HpNo, C_Email, password, status) VALUES (?,?, ?, ?, ?, ?, ?, ?)");

	//ID auto incresing
	ps->setString(1, customer->Customers_ID);
	ps->setString(2, customer->C_Name);
	ps->setString(3, customer->C_Type);
	ps->setString(4, customer->C_Address);
	ps->setString(5, customer->C_HpNo);
	ps->setString(6, customer->C_Email);
	ps->setString(7, customer->password);
	ps->setString(8, customer->status);

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

int CustomerController::updateCustomer(Customer* customer)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE customers SET C_Name = ?, C_Type = ?, C_Address = ?, C_HpNo = ?, C_Email = ?,password = ?, status = ? WHERE Customers_ID = ?");

	ps->setString(1, customer->C_Name);
	ps->setString(2, customer->C_Type);
	ps->setString(3, customer->C_Address);
	ps->setString(4, customer->C_HpNo);
	ps->setString(5, customer->C_Email);
	ps->setString(6, customer->password);
	ps->setString(7, customer->status);
	ps->setString(8, customer->Customers_ID);

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

int CustomerController::deleteCustomer(Customer* customer)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM customers WHERE Customers_ID = ?");

	ps->setString(1, customer->Customers_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "can't delete this account, because recorded data in other table\n";
		std::cout << "System will automaticly help you to Frozen this account\n";
		customer->status = "Frozen";
		numRowsAffected = updateCustomer(customer);
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}
	ps->close();

	delete ps;

	return numRowsAffected;
}

//SEARCH
Customer* CustomerController::getCustomerDetail_S_ID(std::string Customers_ID)	//search by ID (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE Customers_ID = ?");

	ps->setString(1, Customers_ID);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;

	if (rs->next())
	{
		customer = new Customer();
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;


	return customer;
}

Customer* CustomerController::getCustomerDetail_S_Name(std::string C_Name)	//search by Name (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE C_Name = ?");

	ps->setString(1, C_Name);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;

	if (rs->next())
	{
		customer = new Customer();
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return customer;
}

Customer* CustomerController::getCustomerDetail_S_Type(std::string C_Type)	//search by Type (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE C_Type = ?");

	ps->setString(1, C_Type);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustomerController::getCustomerDetail_S_Address(std::string C_Address)	//search by Address (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE C_Address = ?");

	ps->setString(1, C_Address);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustomerController::getCustomerDetail_S_HpNo(std::string C_HpNo)	//search by HpNo (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE C_HpNo = ?");

	ps->setString(1, C_HpNo);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustomerController::getCustomerDetail_S_Email(std::string C_Email)	//search by Email (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE C_Email = ?");

	ps->setString(1, C_Email);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustomerController::getCustomerDetail_S_Status(std::string status)	//search by Status (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers WHERE status = ?");

	ps->setString(1, status);

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL) {
			customer = new Customer();
			head = customer;
		}
		else {
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

Customer* CustomerController::getAllCustomerDetails()	//display all customer detial
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Customers");

	sql::ResultSet* rs = ps->executeQuery();
	Customer* customer = NULL;
	Customer* head = NULL;

	while (rs->next())		//for multi output
	{
		if (customer == NULL)
		{
			customer = new Customer();
			head = customer;
		}
		else
		{
			customer->next = new Customer();
			customer = customer->next;
		}
		transform(rs, customer);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

