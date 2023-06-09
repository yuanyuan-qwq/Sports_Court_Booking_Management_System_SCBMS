#include "SportCourtController.h"

//SportCourt controller

void transform(sql::ResultSet* rs, SportCourt* SportCourt)
{
	SportCourt->SportCourt_ID = rs->getString("SportCourt_ID");
	SportCourt->SC_Name = rs->getString("SC_Name");
	SportCourt->SC_Status = rs->getString("SC_Status");
	SportCourt->PricePerDay = rs->getDouble("PricePerDay");
	SportCourt->Staff_ID = rs->getString("Staff_ID");

}

//insert,update,delete for SportCourt
SportCourt* SportCourtController::getSportCourtIDForInsert() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court ORDER BY SportCourt_ID DESC LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;

	if (rs->next())
	{
		sportCourt = new SportCourt();
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return sportCourt;

}

int SportCourtController::insertSportCourt(SportCourt* sportCourt)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Sport_Court (SportCourt_ID, SC_Name, SC_Status, PricePerDay, Staff_ID) VALUES ( ?, ?, ?, ?, ?)");

	//ID auto incresing
	ps->setString(1, sportCourt->SportCourt_ID);
	ps->setString(2, sportCourt->SC_Name);
	ps->setString(3, sportCourt->SC_Status);
	ps->setDouble(4, sportCourt->PricePerDay);
	ps->setString(5, sportCourt->Staff_ID);


	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "duplecate Sport Court Name!!\n";
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}
	ps->close();

	delete ps;

	return numRowsAffected;
}

int SportCourtController::updateSportCourt(SportCourt* sportCourt)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Sport_Court SET SC_Name = ?, SC_Status = ?, PricePerDay = ?, Staff_ID = ? WHERE SportCourt_ID = ?");

	ps->setString(1, sportCourt->SC_Name);
	ps->setString(2, sportCourt->SC_Status);
	ps->setDouble(3, sportCourt->PricePerDay);
	ps->setString(4, sportCourt->Staff_ID);
	ps->setString(5, sportCourt->SportCourt_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "duplecate Sport Court Name!!\n";
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}

int SportCourtController::deleteSportCourt(SportCourt* SportCourt)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Sport_Court WHERE SportCourt_ID = ?");

	ps->setString(1, SportCourt->SportCourt_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "can't delete, because recorded data in other table\n";
		std::cout << "System will automaticly help you to Frozen this\n";
		SportCourt->SC_Status = "UNAVAILABLE";
		numRowsAffected = updateSportCourt(SportCourt);
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}


//SEARCH
SportCourt* SportCourtController::getSportCourtDetail_S_ID(std::string SportCourt_ID)	//search by ID (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court WHERE SportCourt_ID = ?");

	ps->setString(1, SportCourt_ID);

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;

	if (rs->next())
	{
		sportCourt = new SportCourt();
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;


	return sportCourt;
}

SportCourt* SportCourtController::getSportCourtDetail_S_Name(std::string SC_Name)	//search by Name (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court WHERE SC_Name = ?");

	ps->setString(1, SC_Name);

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;

	if (rs->next())
	{
		sportCourt = new SportCourt();
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return sportCourt;
}

SportCourt* SportCourtController::getSportCourtDetail_S_Status(std::string SC_Status)	//search by Status (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court WHERE SC_Status = ?");

	ps->setString(1, SC_Status);

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;
	SportCourt* head = NULL;

	while (rs->next())		//for multi output
	{
		if (sportCourt == NULL) {
			sportCourt = new SportCourt();
			head = sportCourt;
		}
		else {
			sportCourt->next = new SportCourt();
			sportCourt = sportCourt->next;
		}
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

SportCourt* SportCourtController::getSportCourtDetail_S_PricePerDay(double PricePerDay)	//search by Address (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court WHERE PricePerDay = ?");

	ps->setDouble(1, PricePerDay);

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;
	SportCourt* head = NULL;

	while (rs->next())		//for multi output
	{
		if (sportCourt == NULL) {
			sportCourt = new SportCourt();
			head = sportCourt;
		}
		else {
			sportCourt->next = new SportCourt();
			sportCourt = sportCourt->next;
		}
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

SportCourt* SportCourtController::getAllSportCourtDetails()	//display all SportCourt detial
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Sport_Court");

	sql::ResultSet* rs = ps->executeQuery();
	SportCourt* sportCourt = NULL;
	SportCourt* head = NULL;

	while (rs->next())		//for multi output
	{
		if (sportCourt == NULL)
		{
			sportCourt = new SportCourt();
			head = sportCourt;
		}
		else
		{
			sportCourt->next = new SportCourt();
			sportCourt = sportCourt->next;
		}
		transform(rs, sportCourt);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}