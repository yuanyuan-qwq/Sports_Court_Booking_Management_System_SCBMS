#pragma once
#include <string>
#include <mysql/jdbc.h>

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

class DatabaseConnection
{
private:
	sql::Connection* connection;

public:
	DatabaseConnection();
	~DatabaseConnection();
	sql::PreparedStatement* prepareStatement(std::string query);
};

#endif