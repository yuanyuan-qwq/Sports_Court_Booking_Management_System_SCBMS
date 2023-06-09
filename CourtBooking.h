#pragma once
#include <string>

#ifndef CourtBooking_H
#define CourtBooking_H

class CourtBooking
{
public:
	std::string CourtBooking_ID, Customers_ID, SportCourt_ID, Staff_ID;
	std::string DateIN,DateOUT;
	int TotalDay;
	double TotalCharge;
	std::string PaymentType;
	CourtBooking* next;
	
	//temp var  	//for extra info(join table)
	bool Match;		//to check date booking valid or not
	std::string C_Name, SC_Name, S_Name,C_type;
	int Month,frequency;
	float MonthlyIncome=0, AnualIncome=0,TypeIncome=0,MeanProfit=0,MeanDay=0;

};
#endif // !CourtBooking