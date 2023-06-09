#pragma once
#include "CustomerController.h"
#include "CourtBookingController.h"
#include "SportCourtController.h"


#ifndef CustomerMethod_H
#define CustomerMethod_H

class CustomerMethod
{
public:
	//register
	std::string CustomerRegister();
	//########################## Customer Method #############################/
	void CustomerDetial(Customer* customer);
	void CustomerSelfUpdate(Customer* customer);
	void ViewAllSportCourt();
	void MakeBooking(Customer* customer);
	void UpComing(Customer* customer);
	void CheckMyBookingHistory(Customer* customer);
	
	//##################################################################################
	void PrintOutBookingInfo(CourtBooking* courtBooking);

};

#endif