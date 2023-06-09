#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include <cstdlib>  
#include<time.h>

#include "Login.h"
#include "manager.h"
#include "staff.h"
#include "ManagerView.h"

ManagerView managerView;



#include<mysql/jdbc.h>
using namespace sql;

/*

void Login::StaffLoginMenu() {
CTM:
	system("cls");
	cout << "------------- Staff Login Page ------------- \n";
	cout << "User Name: ";
	cin >> userName;
	cout << "Password: ";
	cin >> password;

	mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
	Connection* connection = driver->connect("tcp://127.0.0.1:3306", "root", "");

	connection->setSchema("workshop1");
	PreparedStatement* ps = connection->prepareStatement("SELECT * FROM staff WHERE S_Name = ? AND Password = ?");

	ps->setString(1, userName);
	ps->setString(2, password);

	ResultSet* rs = ps->executeQuery();

	if (rs->next()) {
		//adddd
	}
	else {
		cout << "wrong, try again!!\n";
		system("pause");
		goto CTM;
	}

	rs->close();
	ps->close();
	connection->close();

	delete rs;
	delete ps;
	delete connection;

}

void Login::ManagerLoginMenu() {
MNG:
	system("cls");
	cout << "------------- Manager Login Page ------------- \n";
	cout << "User Name: ";
	cin >> userName;
	cout << "Password: ";
	cin >> password;

	mysql::MySQL_Driver* driver = mysql::get_mysql_driver_instance();
	Connection* connection = driver->connect("tcp://127.0.0.1:3306", "root", "");

	connection->setSchema("workshop1");
	PreparedStatement* ps = connection->prepareStatement("SELECT * FROM manager WHERE M_Name = ? AND Password = ?");

	ps->setString(1, userName);
	ps->setString(2, password);

	ResultSet* rs = ps->executeQuery();


	if (rs->next()) {
		managerView.ManagerMainMenu();
	}
	else {
		cout << "wrong, try again!!\n";
		system("pause");
		goto MNG;
	}

	rs->close();
	ps->close();
	connection->close();

	delete rs;
	delete ps;
	delete connection;

}

void Login::CustomerRegisterMenu() {

	ManagerMethod ManagerMethod;
	system("cls");

	ManagerMethod.InsertCustomer();

}
*/