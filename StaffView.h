#pragma once
#include "StaffMethod.h"

#ifndef StaffView_H
#define StaffView_H

class StaffView
{
public:
	void StaffLoginMenu();
	void StaffMainMenu(Staff* Staff);//n

	void StaffSearch();
	void ManagerSearch();

	void SportCourtMethodStaff();
	void CourtBookingMethodStaff();
	//reuse Manager Method
	//########################## Customer Method For Admin ################
	//########################## SportCourt Method ########################
	//########################## Booking Method ###########################
	//########################## Staff Search #############################
	//########################## Manager Search ###########################


};

#endif