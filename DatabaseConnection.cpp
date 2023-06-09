#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection()
{
	sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
	connection = driver->connect("tcp://127.0.0.1:3306", "root", "");

	connection->setSchema("workshop1");
}

DatabaseConnection::~DatabaseConnection()
{
	connection->close();

	delete connection;
}

sql::PreparedStatement* DatabaseConnection::prepareStatement(std::string query)
{
	return connection->prepareStatement(query);
}