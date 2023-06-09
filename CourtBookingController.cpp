#include "CourtBookingController.h"


//Booking controller

void transform(sql::ResultSet* rs, CourtBooking* courtBooking)
{
	courtBooking->CourtBooking_ID = rs->getString("CourtBooking_ID");
	courtBooking->Customers_ID = rs->getString("Customers_ID");
	courtBooking->SportCourt_ID = rs->getString("SportCourt_ID");
	courtBooking->Staff_ID = rs->getString("Staff_ID");
	courtBooking->DateIN = rs->getString("DateIN");
	courtBooking->DateOUT = rs->getString("DateOUT");
	courtBooking->TotalDay = rs->getInt("TotalDay");
	courtBooking->TotalCharge = rs->getDouble("TotalCharge");
	courtBooking->PaymentType = rs->getString("PaymentType");

	//for extra info(join table)
	try {
		courtBooking->C_Name = rs->getString("C_Name");
		courtBooking->SC_Name = rs->getString("SC_Name");
		courtBooking->S_Name = rs->getString("S_Name");
	}
	catch (sql::SQLException) {		
		//accept for the Booking controller which don't use Join table
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
		system("pause");
	}
}

//insert
CourtBooking* CourtBookingController::getCourtBookingIDForInsert() {

	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Court_Booking ORDER BY CourtBooking_ID DESC LIMIT 1");

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;

	if (rs->next())
	{
		courtBooking = new CourtBooking();
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return courtBooking;

}

std::string CourtBookingController::DateInValidCheck(CourtBooking* courtBooking)
{
	//check DateIN and DateOUT Valid or not (avoid invalid date key in and DateIN >= DateOUT)
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DATEDIFF(?,?) AS DateValid");

	ps->setString(1, courtBooking->DateOUT);
	ps->setString(2, courtBooking->DateIN);

	sql::ResultSet* rs = ps->executeQuery();
	int DateValid=NULL;
	std::string Valid = "invalid input";				
	
	if (rs->next())
	{
		DateValid = rs->getInt("DateValid");

		if (DateValid != NULL && DateValid > 0) 
		{
			//check DateIN are previous Date? Valid or not (avoid DateIN is previos date)
			sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DATEDIFF(?,NOW()) AS DateValid");

			ps->setString(1, courtBooking->DateIN);

			sql::ResultSet* rs = ps->executeQuery();

			Valid = "Can't Booking Current date or Previous date";

			if (rs->next())
			{
				DateValid = rs->getInt("DateValid");

				if (DateValid > 0)
				{
					Valid = "true";
				}
			}
		}
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return Valid;
}

std::pair<int, int> CourtBookingController::DuplicateBookingCheck(CourtBooking* &courtBooking)	//Pass By Reference
{
	//check DateIN are within other booking's DateIN and DateOUT (startTime >= booking.startTime && startTime <= booking.endTime)
	
	std::string SCID = courtBooking->SportCourt_ID;
	std::string StartTime = courtBooking->DateIN;
	std::string EndTime = courtBooking->DateOUT;
	courtBooking->Match = true;

	//DB_DateIN <= YourDateIN <= DB_DateOUT
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps1 = dbConn.prepareStatement("SELECT * FROM court_booking WHERE SportCourt_ID = '" + SCID + "' AND (DateIN <= '" + StartTime + "' AND DateOUT >= '" + StartTime + "')");

	sql::ResultSet* rs1 = ps1->executeQuery();
	int StartClash = 0;
	int EndClash = 0;

	while (rs1->next()) {
		StartClash++;
		courtBooking->Match = false;
	}

	//check DateOUT are within other booking's DateIN and DateOUT (ENDTime >= booking.startTime && ENDTime <= booking.endTime)
	//DB_DateOUT <= YourDateOUT <= DB_DateOUT
	sql::PreparedStatement* ps2 = dbConn.prepareStatement("SELECT * FROM court_booking WHERE SportCourt_ID = '" + SCID + "' AND (DateIN <= '" + EndTime + "' AND DateOUT >= '" + EndTime + "')");

	sql::ResultSet* rs2 = ps2->executeQuery();

	while (rs2->next()) {
		EndClash++;
		courtBooking->Match = false;
	}

	//check all
	//(YourDateIN <= DB_DateIN <= YourDateOUT) && (YourDateIN <= DB_DateOUT <= YourDateOUT)
	sql::PreparedStatement* ps3 = dbConn.prepareStatement("SELECT * FROM court_booking WHERE SportCourt_ID = '" + SCID + "' AND ((DateIN >= '" + StartTime + "' AND DateIN <= '" + EndTime + "') OR (DateOUT >= '" + StartTime + "' AND DateOUT <= '" + EndTime + "'))");

	sql::ResultSet* rs3 = ps3->executeQuery();

	while (rs3->next()) {
		courtBooking->Match = false;
	}

	return std::make_pair(StartClash, EndClash);
}

int CourtBookingController::CountDay(CourtBooking* courtBooking)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DATEDIFF(?,?) AS Day");

	ps->setString(1, courtBooking->DateOUT);
	ps->setString(2, courtBooking->DateIN);

	sql::ResultSet* rs = ps->executeQuery();
	int Day = NULL;

	if (rs->next())
	{
		Day = rs->getInt("Day");
	}
	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return Day;
}

int CourtBookingController::insertCourtBooking(CourtBooking* courtBooking)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Court_Booking (CourtBooking_ID, Customers_ID, SportCourt_ID, Staff_ID, DateIN, DateOUT, TotalDay, TotalCharge, PaymentType) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

	//ID auto incresing
	ps->setString(1, courtBooking->CourtBooking_ID);
	ps->setString(2, courtBooking->Customers_ID);
	ps->setString(3, courtBooking->SportCourt_ID);
	ps->setString(4, courtBooking->Staff_ID);
	ps->setString(5, courtBooking->DateIN);
	ps->setString(6, courtBooking->DateOUT);
	ps->setInt(7, courtBooking->TotalDay);
	ps->setDouble(8, courtBooking->TotalCharge);
	ps->setString(9, courtBooking->PaymentType);


	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "Sorry, something went wrong! SQL Problem for insert\n";
		system("pause");
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
		system("pause");
	}
	ps->close();

	delete ps;

	return numRowsAffected;
}


//Update & Delete for staff & Manager
int CourtBookingController::updateCourtBooking(CourtBooking* courtBooking) {		//not bulid yet
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE Court_Booking SET CourtBooking_ID = ?, Customers_ID = ?, SportCourt_ID = ?, Staff_ID = ?, DateIN = ?,DateOUT = ?, TotalDay = ?, TotalCharge = ? WHERE CourtBooking_ID = ?");

	ps->setString(1, courtBooking->CourtBooking_ID);
	ps->setString(2, courtBooking->Customers_ID);
	ps->setString(3, courtBooking->SportCourt_ID);
	ps->setString(4, courtBooking->Staff_ID);
	ps->setString(5, courtBooking->DateIN);
	ps->setString(6, courtBooking->DateOUT);
	ps->setInt(7, courtBooking->TotalDay);
	ps->setDouble(8, courtBooking->TotalCharge);
	ps->setString(9, courtBooking->CourtBooking_ID);

	int numRowsAffected = 0;
	try {
		numRowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException) {
		std::cout << "duplecate!!\n";
	}
	catch (...) {
		std::cout << "something went wrong! please restart! \n";
	}

	ps->close();

	delete ps;

	return numRowsAffected;
}


int CourtBookingController::deleteCourtBooking(CourtBooking* courtBooking) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Court_Booking WHERE CourtBooking_ID = ?");

	ps->setString(1, courtBooking->CourtBooking_ID);

	int numRowsAffected = ps->executeUpdate();

	ps->close();

	delete ps;

	return numRowsAffected;
}

//SEARCH
CourtBooking* CourtBookingController::getCourtBookingDetail_S_BookingID(std::string CourtBooking_ID)	//search by BookingID (unique)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.CourtBooking_ID = ? ;");
		
	ps->setString(1, CourtBooking_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;

	if (rs->next())
	{
		courtBooking = new CourtBooking();
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;


	return courtBooking;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_CustomerID(std::string Customer_ID)	//search by CustomerID (multi)
{
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.Customers_ID = ? ;");

	ps->setString(1, Customer_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_SportCourtID(std::string SportCourt_ID) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.SportCourt_ID = ? ;");

	ps->setString(1, SportCourt_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_StaffID(std::string Staff_ID) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.Staff_ID = ? ;");

	ps->setString(1, Staff_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_DateIN(std::string DateIN) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.DateIN = ? ;");

	ps->setString(1, DateIN);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_DateOUT(std::string DateOUT) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.DateOUT = ? ;");

	ps->setString(1, DateOUT);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_TotalDay(int TotalDay) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.TotalDay = ? ;");

	ps->setInt(1, TotalDay);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_TotalCharge(double TotalCharge) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE (court_booking.TotalCharge <= ?+100 AND court_booking.TotalCharge >= ?-100);");

	ps->setDouble(1, TotalCharge);
	ps->setDouble(2, TotalCharge);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_PaymentType(std::string PaymentType) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.PaymentType = ? ;");

	ps->setString(1, PaymentType);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_Year(int year) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE EXTRACT(YEAR FROM DateIN) = ? OR EXTRACT(YEAR FROM Dateout) = ? "
		"ORDER BY court_booking.DateIN; "
		);

	ps->setInt(1, year);
	ps->setInt(2, year);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_UpComingForCustomer(std::string Customer_ID) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.Customers_ID = ? AND (court_booking.DateIN > NOW() OR court_booking.DateOUT > NOW()) "
		"ORDER BY court_booking.DateIN;");

	ps->setString(1, Customer_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_UpComingForStaff(std::string Staff_ID) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.Staff_ID = ? AND (court_booking.DateIN > NOW() OR court_booking.DateOUT > NOW()) "
		"ORDER BY court_booking.DateIN;");

	ps->setString(1, Staff_ID);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getCourtBookingDetail_S_UpComing() {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID "
		"WHERE court_booking.DateIN > NOW() OR court_booking.DateOUT > NOW() "
		"ORDER BY court_booking.DateIN;");

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::getAllCourtBookingDetails() {			
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT "
		"court_booking.CourtBooking_ID, "
		"court_booking.Customers_ID, "
		"customers.C_Name, "
		"court_booking.SportCourt_ID, "
		"sport_court.SC_Name, "
		"court_booking.Staff_ID, "
		"staff.S_Name, "
		"court_booking.DateIN, "
		"court_booking.DateOUT, "
		"court_booking.TotalDay, "
		"court_booking.TotalCharge, "
		"court_booking.PaymentType "
		"FROM court_booking "
		"JOIN customers ON court_booking.Customers_ID = customers.Customers_ID "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"JOIN staff ON court_booking.Staff_ID = staff.Staff_ID");

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) 
		{
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		transform(rs, courtBooking);

	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


//Generate report
CourtBooking* CourtBookingController::AnnualIncome(int year) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT court_booking.SportCourt_ID,sport_court.SC_Name, COUNT(*) AS frequency,SUM(court_booking.TotalCharge)AS TotalCharge "
		"FROM court_booking "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"WHERE EXTRACT(YEAR FROM DateIN) = ? OR EXTRACT(YEAR FROM Dateout) = ? "
		"GROUP BY SportCourt_ID "
		"ORDER BY TotalCharge DESC;"
	);

	ps->setInt(1, year);
	ps->setInt(2, year);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		courtBooking->SportCourt_ID = rs->getString("SportCourt_ID");
		courtBooking->SC_Name = rs->getString("SC_Name");
		courtBooking->frequency = rs->getInt("frequency");
		courtBooking->TotalCharge = rs->getDouble("TotalCharge");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::MonthlyIncome(int year, int month) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT court_booking.SportCourt_ID,sport_court.SC_Name, COUNT(*) AS frequency,SUM(court_booking.TotalCharge)AS TotalCharge "
		"FROM court_booking "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"WHERE (EXTRACT(YEAR FROM DateIN) = ? OR EXTRACT(YEAR FROM Dateout) = ?) AND (EXTRACT(MONTH FROM DateIN) = ? OR EXTRACT(MONTH FROM Dateout) = ?)"
		"GROUP BY SportCourt_ID "
		"ORDER BY TotalCharge DESC;"
	);

	ps->setInt(1, year);
	ps->setInt(2, year);
	ps->setInt(3, month);
	ps->setInt(4, month);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		courtBooking->SportCourt_ID = rs->getString("SportCourt_ID");
		courtBooking->SC_Name = rs->getString("SC_Name");
		courtBooking->frequency = rs->getInt("frequency");
		courtBooking->TotalCharge = rs->getDouble("TotalCharge");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::HighDemandSportCourt() {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT court_booking.SportCourt_ID,sport_court.SC_Name, COUNT(*) AS frequency,SUM(court_booking.TotalCharge)AS TotalCharge "
		"FROM court_booking "
		"JOIN sport_court ON court_booking.SportCourt_ID = sport_court.SportCourt_ID "
		"GROUP BY SportCourt_ID "
		"ORDER BY frequency DESC;"
	);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		courtBooking->SportCourt_ID = rs->getString("SportCourt_ID");
		courtBooking->SC_Name = rs->getString("SC_Name");
		courtBooking->frequency = rs->getInt("frequency");
		courtBooking->TotalCharge = rs->getDouble("TotalCharge");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}

CourtBooking* CourtBookingController::SummaryReport(int year) {
	DatabaseConnection dbConn;
	std::string sql = "SELECT MONTH(DateIN) AS Month, SUM(TotalCharge) AS MonthlyIncome FROM court_booking WHERE EXTRACT(YEAR FROM DateIN) = ? OR EXTRACT(YEAR FROM Dateout) = ? GROUP BY MONTH(DateIN) ORDER BY MONTH(DateIN);";
	sql::PreparedStatement* ps = dbConn.prepareStatement(sql);

	ps->setInt(1, year);
	ps->setInt(2, year);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		courtBooking->Month = rs->getInt("Month");
		courtBooking->MonthlyIncome = rs->getDouble("MonthlyIncome");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}


CourtBooking* CourtBookingController::StatisticReport(int year) {
	DatabaseConnection dbConn;
	sql::PreparedStatement* ps = dbConn.prepareStatement(
		"SELECT customers.C_type, SUM(court_booking.TotalCharge) AS TypeIncome, AVG(court_booking.TotalCharge) AS MeanProfit, AVG(court_booking.TotalDay) AS MeanDay "
		"FROM court_booking "
		"JOIN customers ON customers.customers_ID = court_booking.customers_ID "
		"WHERE (EXTRACT(YEAR FROM DateIN) = ? OR EXTRACT(YEAR FROM Dateout) = ?) "
		"GROUP BY customers.C_type"
	);

	ps->setInt(1, year);
	ps->setInt(2, year);

	sql::ResultSet* rs = ps->executeQuery();
	CourtBooking* courtBooking = NULL;
	CourtBooking* head = NULL;

	while (rs->next())		//for multi output
	{
		if (courtBooking == NULL) {
			courtBooking = new CourtBooking();
			head = courtBooking;
		}
		else {
			courtBooking->next = new CourtBooking();
			courtBooking = courtBooking->next;
		}
		// first pointer for individual, second is for organization
		courtBooking->C_type = rs->getString("C_type");
		courtBooking->TypeIncome = rs->getDouble("TypeIncome");
		courtBooking->MeanProfit = rs->getDouble("MeanProfit");
		courtBooking->MeanDay = rs->getDouble("MeanDay");
	}

	rs->close();
	ps->close();

	delete rs;
	delete ps;

	return head;
}