#pragma once
#include "ManagerMethod.h"

#ifndef ManagerView_H
#define ManagerView_H

class ManagerView
{
public:
	void ManagerLoginMenu();
	void ManagerMainMenu(Manager* manager);//n

	void CustomerMethodForAdmin();
	void StaffMethodForAdmin();
	void ManagerSelfMethod();
	void SportCourtMethod();
	void CourtBookingMethod();// now
	void GenerateReportMethod();//

};

#endif