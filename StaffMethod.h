#pragma once
#include "ManagerMethod.h"


#ifndef StaffMethod_H
#define StaffMethod_H

class StaffMethod
{
public:
	//########################## Staff Method #############################/
	void StaffDetial(Staff* staff);
	void StaffSelfUpdate(Staff* staff);

	void UpComingTask(Staff* staff);		//task(Booking) for staff
	void AllHistoryTask(Staff* staff);		//task(Booking) for staff order by DateIN

	void PrintOutBookingInfo(CourtBooking* courtBookings);
	//reuse Manager Method
	//########################## Customer Method For Admin ################
	//########################## SportCourt Method ########################
	//########################## Booking Method ###########################
	//########################## Staff Search #############################
	//########################## Manager Search ###########################




};

#endif