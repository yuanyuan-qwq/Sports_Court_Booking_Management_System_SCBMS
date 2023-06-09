#pragma once
#include "CourtBooking.h"
#include "DatabaseConnection.h"
#include <utility> // for std::pair
#include <vector>


#ifndef CourtBookingController_H
#define CourtBookingController_H

class CourtBookingController
{
public:

	//insert	{
	CourtBooking* getCourtBookingIDForInsert();
	std::string DateInValidCheck(CourtBooking* courtBooking);
	std::pair<int, int> DuplicateBookingCheck(CourtBooking* &courtBooking);
	int CountDay(CourtBooking* courtBooking);
	int insertCourtBooking(CourtBooking* courtBooking);
	//insert	}

	//Update & Delete for staff & Manager
	int updateCourtBooking(CourtBooking* courtBooking);		//ID to update		//not bulid yet
	int deleteCourtBooking(CourtBooking* courtBooking);		//ID to Delete		
		
	//SEARCH
	CourtBooking* getCourtBookingDetail_S_BookingID(std::string CourtBookings_ID);		//search by BookingID (unique)
	CourtBooking* getCourtBookingDetail_S_CustomerID(std::string Customer_ID);			//search by CustomerID (multi)/
	CourtBooking* getCourtBookingDetail_S_SportCourtID(std::string SportCourt_ID);		//search by CustomerID (multi)
	CourtBooking* getCourtBookingDetail_S_StaffID(std::string Staff_ID);				//search by StaffID (multi)
	CourtBooking* getCourtBookingDetail_S_DateIN(std::string DateIN);					//search by DateIN (multi)
	CourtBooking* getCourtBookingDetail_S_DateOUT(std::string DateOUT);					//search by DateOUT (multi)
	CourtBooking* getCourtBookingDetail_S_Year(int year);								//search by Extract Year (multi)
	CourtBooking* getCourtBookingDetail_S_TotalDay(int TotalDay);						//search by TotalDay (multi)
	CourtBooking* getCourtBookingDetail_S_TotalCharge(double TotalCharge);				//search by TotalCharge (multi)
	CourtBooking* getCourtBookingDetail_S_PaymentType(std::string PaymentType);			//search by PaymentType(multi)

	CourtBooking* getCourtBookingDetail_S_UpComingForCustomer(std::string Customer_ID);		//search by UpComing(customer (multi)
	CourtBooking* getCourtBookingDetail_S_UpComingForStaff(std::string Staff_ID);			//search by UpComing(Staff (multi)
	CourtBooking* getCourtBookingDetail_S_UpComing(	);										//search by UpComing(All (multi)

	CourtBooking* getAllCourtBookingDetails();											//display all CourtBooking detial

	//Generate report
	CourtBooking* AnnualIncome(int year);
	CourtBooking* MonthlyIncome(int year,int month);
	CourtBooking* HighDemandSportCourt();
	CourtBooking* SummaryReport(int year);

	CourtBooking* StatisticReport(int year);











};

#endif