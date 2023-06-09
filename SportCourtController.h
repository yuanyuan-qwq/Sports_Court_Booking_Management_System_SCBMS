#pragma once
#include "SportCourt.h"
#include "DatabaseConnection.h"


#ifndef SportCourtController_H
#define SportCourtController_H

class SportCourtController
{
public:

	//Manager{

	//insert,update,delete
	SportCourt* getSportCourtIDForInsert();
	int insertSportCourt(SportCourt* sportCourt);
	int updateSportCourt(SportCourt* sportCourt);		//ID to update
	int deleteSportCourt(SportCourt* sportCourt);		//ID to Delete

	//SEARCH
	SportCourt* getSportCourtDetail_S_ID(std::string SportCourts_ID);				//search by ID (unique)
	SportCourt* getSportCourtDetail_S_Name(std::string SC_Name);				//search by Name (unique)
	SportCourt* getSportCourtDetail_S_Status(std::string SC_Status);			//search by Status (multi)
	SportCourt* getSportCourtDetail_S_PricePerDay(double PricePerDay);		//search by Price (multi)
	SportCourt* getAllSportCourtDetails();								//display all SportCourt detial

	//}Manager

};

#endif