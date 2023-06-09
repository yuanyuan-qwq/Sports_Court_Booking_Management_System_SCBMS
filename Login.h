#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include <cstdlib>  
#include<time.h>
#include <mysql/jdbc.h>

using namespace std;

#ifndef Login_H
#define Login_H

class Login
{
private:
	string userName, password;

public:
	void LoginMenu();
	void CustomerLoginMenu();
	void StaffLoginMenu();
	void ManagerLoginMenu();

	void CustomerRegisterMenu();

};

#endif