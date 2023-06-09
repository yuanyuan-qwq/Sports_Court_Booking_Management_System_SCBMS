#pragma once
#include "CustomerController.h"
#include "StaffController.h"
#include "ManagerController.h"
#include "SportCourtController.h"
#include "CourtBookingController.h"

#ifndef ManagerMethod_H
#define ManagerMethod_H

class ManagerMethod
{
public:

	//########################## Customer Method #############################/
	void InsertCustomer();
	void UpdateCustomer();
	void DeleteCustomer();

	void IDSearchCustomer();
	void NameSearchCustomer();
	void TypeSearchCustomer();
	void AddressSearchCustomer();
	void HpNoSearchCustomer();
	void EmailSearchCustomer();
	void StatusSearchCustomer();

	void AllCustomerDetails();
	void PrintOutCustomerInfo(Customer* customer);


	//########################## Staff Method #############################/
	void InsertStaff();
	void UpdateStaff();
	void DeleteStaff();

	void IDSearchStaff();
	void MIDSearchStaff();
	void NameSearchStaff();
	void GenderSearchStaff();
	void HpNoSearchStaff();
	void EmailSearchStaff();
	void StatusSearchStaff();

	void AllStaffDetails();
	void PrintOutStaffInfo(Staff* staffs);


	//########################## Manager Method #############################/
	void InsertManager();
	void UpdateManager();
	void DeleteManager();

	void IDSearchManager();
	void NameSearchManager();
	void GenderSearchManager();
	void HpNoSearchManager();
	void EmailSearchManager();
	void StatusSearchManager();

	void AllManagerDetails();
	void PrintOutManagerInfo(Manager* managers);


	//########################## SportCourt Method #############################
	void InsertSportCourt();
	void UpdateSportCourt();
	void DeleteSportCourt();

	void IDSearchSportCourt();
	void NameSearchSportCourt();
	void StatusSearchSportCourt();
	void PriceSearchSportCourt();

	void AllSportCourtDetails();
	void PrintOutSportCourtInfo(SportCourt* sportCourts);

	
	//########################## Booking Method #############################
	void InsertCourtBooking();		//reuse customer booking
	void UpdateCourtBooking();		//not bulid yet
	void DeleteCourtBooking();		

	void BookingIDSearchCourtBooking();
	void CustomerIDSearchCourtBooking();
	void SportCourtIDSearchCourtBooking();
	void StaffIDSearchCourtBooking();
	void DateINSearchCourtBooking();
	void DateOUTSearchCourtBooking();
	void YearSearchCourtBooking();
	void TotalDaySearchCourtBooking();
	void TotalChargeSearchCourtBooking();
	void PaymentTypeSearchCourtBooking();

	void AllCourtBookingDetails();
	void AllUpComingCourtBookingDetails();
	void PrintOutBookingInfo(CourtBooking* courtBooking);

	//calender
	void CalendarView(int year, int month, CourtBooking* courtBooking);

	//########################## Report Method #############################
	void AnnualIncome();
	void MonthlyIncome();
	void HighDemandSportCourt();
	void SummaryReport();

	void StatisticReport();

	//###################### Test fuc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// /*
	void TotalManager();

	// */
};

#endif