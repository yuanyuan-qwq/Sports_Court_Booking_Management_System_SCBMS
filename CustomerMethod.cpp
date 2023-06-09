#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<cstdlib>  
#include<time.h>
#include <conio.h>
#include <fstream>

#include "ManagerMethod.h" // for reuse some function from manager
#include "CustomerMethod.h"

//Register
std::string CustomerMethod::CustomerRegister() {
	Customer* customer = new Customer();
	std::string again;

	CustomerController customerController;

	system("cls");
	//############## customer ID ##################

	//Auto genarate ID Algorithm (Format VXXXXXXXX) V=IDType(C=Customer,S=staff,M=Manager,SC=Sport Court), X = variable(0-9)
	Customer* getNewestCustomerID = customerController.getCustomerIDForInsert();

	if (getNewestCustomerID != NULL) {
		std::string ID, NumAfter, d, e;	//d=covert to string after+1 , e= compose CustomerID
		ID = getNewestCustomerID->Customers_ID;

		NumAfter = ID.substr(1, 8);		//Starting position = 1, length = 8 (get num after the position)
		int b = stoi(NumAfter) + 1;		//convert String(c) to int type +1

		if (b >= 0 && b <= 9)
		{
			d = std::to_string(b);
			e = "C0000000" + d;
		}
		else if (b >= 10 && b <= 99)
		{
			d = std::to_string(b);
			e = "C000000" + d;
		}
		else if (b >= 100 && b <= 999)
		{
			d = std::to_string(b);
			e = "C00000" + d;
		}
		else if (b >= 1000 && b <= 9999)
		{
			d = std::to_string(b);
			e = "C0000" + d;
		}
		else if (b >= 10000 && b <= 99999)
		{
			d = std::to_string(b);
			e = "C000" + d;
		}
		else if (b >= 100000 && b <= 999999)
		{
			d = std::to_string(b);
			e = "C00" + d;
		}
		else if (b >= 1000000 && b <= 9999999)
		{
			d = std::to_string(b);
			e = "C0" + d;
		}
		else if (b >= 10000000 && b <= 99999999)
		{
			d = std::to_string(b);
			e = "C" + d;
		}
		customer->Customers_ID = e;
	}
	else {				//if no data in database, start at default
		customer->Customers_ID = "C00000001";
	}

	std::string input;
	//############## customer name ##################
name:
	system("cls");
	std::cout << "Customer Name(0 to exit): ";
	std::getline(std::cin, input);

	Customer* Duplication = customerController.getCustomerDetail_S_Name(input);

	if (input == "0") {
	end:
		return "0";
		
	}
	else if(Duplication != NULL) {
		std::cout << "\nUsername registered!! \n";
		system("pause");
		goto name;
	}
	else {
		customer->C_Name = input;
	}

	//############## customer password ##################

	std::string temp1, temp2;
password:
	system("cls");
	//################### hide password ##################
	do {
		char c;
		std::string password;		//for temp use, after loop(while) clear data in password
		std::cout << "Password(0 to exit): ";
		c = _getch();
		while (c != '\r') {
			if (c == '\b') {  // handle backspace
				if (!password.empty()) {
					password.pop_back();
					std::cout << "\b \b";
				}
			}
			else {
				password.push_back(c);
				std::cout << '*';
			}
			c = _getch();
		}
		temp1 = password;
		std::cout << std::endl;
	} while (false);

	if (temp1 == "0") {
		goto end;
	}

	//################### hide password ##################
	do {
		char c;
		std::string password;		//for temp use, after loop(while) clear data in password
		std::cout << "Comfirm Password: ";
		c = _getch();
		while (c != '\r') {
			if (c == '\b') {  // handle backspace
				if (!password.empty()) {
					password.pop_back();
					std::cout << "\b \b";
				}
			}
			else {
				password.push_back(c);
				std::cout << '*';
			}
			c = _getch();
		}
		temp2 = password;
		std::cout << std::endl;
	} while (false);

	if (temp1 == temp2) {
		customer->password = temp2;
	}
	else
	{
		std::cout << "password not match!! please try again!\n\n";
		system("pause");
		goto password;
	}

	//############## customer type ##################

	std::string select;
SelectType:
	system("cls");
	std::cout << "Select Type (1=Individual, 2=Organization)(0 to exit): ";
	std::getline(std::cin, select);

	if (select == "1") {
		customer->C_Type = "Individual";
	}
	else if (select == "2") {
		customer->C_Type = "Organization";
	}
	else if (select == "0") {
		goto end;
	}
	else {
		std::cout << "invalid input!! please try again!\n\n";
		system("pause");
		goto SelectType;
	}

	//############## customer Address ##################
	system("cls");
	std::cout << "Customer Address(0 to exit): ";
	std::getline(std::cin, input);

	if (input != "0") {
		customer->C_Address = input;
	}
	else {
		goto end;
	}

	//############## customer HpNo ##################
	do {
		system("cls");

		bool valid = true;

		std::cout << "Enter phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
		std::getline(std::cin, input);

		if (input == "0") {
			goto end;
		}

		if (input.length() == 0 || input[0] == '-' || input[input.length() - 1] == '-') {
			valid = false;
		}
		else {
			for (char c : input) {
				if (!isdigit(c) && c != '-') {
					valid = false;
					break;
				}
			}
		}

		if (valid) {
			customer->C_HpNo = input;
			break;
		}
		else {
			std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
			system("pause");
		}
	} while (true);

	//############## customer Email ##################
	do {
		system("cls");

		bool isValid = true;

		std::cout << "Enter an Email(0 to exit)[exp:FTMK@utem.com]: ";
		std::getline(std::cin, input);

		if (input == "0") {
			goto end;
		}

		// Check if "@" and "." are present in the string
		size_t atPos = input.find('@');
		size_t dotPos = input.find('.');
		if (atPos == std::string::npos || dotPos == std::string::npos) {
			isValid = false;
		}
		// Check if "@" is not at the beginning or end
		else if (atPos == 0 || atPos == input.length() - 1) {
			isValid = false;
		}
		// Check if "." is not at the beginning or end
		else if (dotPos == 0 || dotPos == input.length() - 1) {
			isValid = false;
		}
		// Check if "." is after "@"
		else if (dotPos < atPos) {
			isValid = false;
		}

		if (isValid) {
			customer->C_Email = input;
			break;
		}
		else {
			std::cout << "Invalid email format\n";
			system("pause");
		}
	} while (true);

	customer->status = "Active";

	//=================== Insert customer ===================
	int status = 0;
	std::string sure;
	system("cls");
	std::cout << "======================= Confirmation information =======================" << std::endl;
	std::cout << "Customers_ID: " << customer->Customers_ID << std::endl
		<< "Customer Name: " << customer->C_Name << std::endl
		<< "Customer Type: " << customer->C_Type << std::endl
		<< "Customer Address: " << customer->C_Address << std::endl
		<< "Customer HpNo: " << customer->C_HpNo << std::endl
		<< "Customer Email: " << customer->C_Email << std::endl;
	std::cout << "==========================================================================" << std::endl;
	std::cout << "Please confirm that the information is true? (Press any Key to continue)(0 to cancel Registration) :";
	std::getline(std::cin, sure);

	if (sure != "0") {
		status = customerController.insertCustomer(customer);
	}

	if (status != 0)
		std::cout << "Successfully register a new customer" << std::endl;
	else
		std::cout << "Unable to register a new customer" << std::endl;
	system("pause");
	return "1";

}

//Customer method
void CustomerMethod::CustomerDetial(Customer* customer) {

	CustomerController customerController;

	customer=customerController.getCustomerDetail_S_ID(customer->Customers_ID);

	system("cls");
	std::cout << "\n=================================================" << std::endl;
	std::cout << "Customers_ID: " << customer->Customers_ID << std::endl
		<< "Customer Name: " << customer->C_Name << std::endl
		<< "Customer Type: " << customer->C_Type << std::endl
		<< "Customer Address: " << customer->C_Address << std::endl
		<< "Customer HpNo: " << customer->C_HpNo << std::endl
		<< "Customer Email: " << customer->C_Email << std::endl
		<< "Status: " << customer->status << std::endl;
	std::cout << "=================================================" << std::endl;

}

void CustomerMethod::CustomerSelfUpdate(Customer* customer){
	std::string ID_OR_loop, select;
	CustomerController customerController;

	do {
	update1:
		system("cls");
		std::cout << "Customer ID : " << customer->Customers_ID << std::endl;
		std::cout << "which one you want to update?" << std::endl;
		std::cout << "1.Customer Name" << std::endl;
		std::cout << "2.Customer Password" << std::endl;
		std::cout << "3.Customer Type" << std::endl;
		std::cout << "4.Customer Address" << std::endl;
		std::cout << "5.Customer HpNo" << std::endl;
		std::cout << "6.Customer Email" << std::endl;
		std::cout << "0.Exit" << std::endl;
		std::cout << "Select(0-6) :";
		std::getline(std::cin, select);

		std::string input;
		if (select == "1") {
			//############## customer name ##################
			system("cls");
			std::cout << "Customer Name(0 to exit): ";
			std::getline(std::cin, input);

			if (input != "0") {
				customer->C_Name = input;
			}
			else {
				goto update1;
			}
		}
		else if (select == "2") {
			//############## customer password ##################

			std::string temp1, temp2;
		password:
			system("cls");
			
			//################### hide password ##################
			do {
				char c;
				std::string password;		//for temp use, after loop(while) clear data in password
				std::cout << "Password(0 to exit): ";
				c = _getch();
				while (c != '\r') {
					if (c == '\b') {  // handle backspace
						if (!password.empty()) {
							password.pop_back();
							std::cout << "\b \b";
						}
					}
					else {
						password.push_back(c);
						std::cout << '*';
					}
					c = _getch();
				}
				temp1 = password;
				std::cout << std::endl;
			} while (false);

			if (temp1 == "0") {
				goto update1;
			}

			//################### hide password ##################
			do {
				char c;
				std::string password;		//for temp use, after loop(while) clear data in password
				std::cout << "Comfirm Password: ";
				c = _getch();
				while (c != '\r') {
					if (c == '\b') {  // handle backspace
						if (!password.empty()) {
							password.pop_back();
							std::cout << "\b \b";
						}
					}
					else {
						password.push_back(c);
						std::cout << '*';
					}
					c = _getch();
				}
				temp2 = password;
				std::cout << std::endl;
			} while (false);

			if (temp1 == temp2) {
				customer->password = temp2;
			}
			else
			{
				std::cout << "password not match!! please try again!\n\n";
				system("pause");
				goto password;
			}
		}
		else if (select == "3") {
			//############## customer type ##################

			std::string select;
		SelectType:
			system("cls");
			std::cout << "Select Type (1=Individual, 2=Organization, 3=Other)(0 to exit): ";
			std::getline(std::cin, select);

			if (select == "1") {
				customer->C_Type = "Individual";
			}
			else if (select == "2") {
				customer->C_Type = "Organization";
			}
			else if (select == "3") {
				customer->C_Type = "Other";
			}
			else if (select == "0") {
				goto update1;
			}
			else {
				std::cout << "invalid input!! please try again!\n\n";
				system("pause");
				goto SelectType;
			}
		}
		else if (select == "4") {
			//############## customer Address ##################
			system("cls");
			std::cout << "Customer Address(0 to exit): ";
			std::getline(std::cin, input);

			if (input != "0") {
				customer->C_Address = input;
			}
			else {
				goto update1;
			}
		}
		else if (select == "5") {
			//############## customer HpNo ##################
			do {
				system("cls");

				bool valid = true;

				std::cout << "Enter phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
				std::getline(std::cin, input);

				if (input == "0") {
					goto update1;
				}

				if (input.length() == 0 || input[0] == '-' || input[input.length() - 1] == '-') {
					valid = false;
				}
				else {
					for (char c : input) {
						if (!isdigit(c) && c != '-') {
							valid = false;
							break;
						}
					}
				}

				if (valid) {
					customer->C_HpNo = input;
					break;
				}
				else {
					std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
					system("pause");
				}
			} while (true);
		}
		else if (select == "6") {
		//############## customer Email ##################
		do {
			system("cls");

			bool isValid = true;

			std::cout << "Enter an Email(0 to exit)[exp:FTMK@utem.com]: ";
			std::getline(std::cin, input);

			if (input == "0") {
				goto update1;
			}

			// Check if "@" and "." are present in the string
			size_t atPos = input.find('@');
			size_t dotPos = input.find('.');
			if (atPos == std::string::npos || dotPos == std::string::npos) {
				isValid = false;
			}
			// Check if "@" is not at the beginning or end
			else if (atPos == 0 || atPos == input.length() - 1) {
				isValid = false;
			}
			// Check if "." is not at the beginning or end
			else if (dotPos == 0 || dotPos == input.length() - 1) {
				isValid = false;
			}
			// Check if "." is after "@"
			else if (dotPos < atPos) {
				isValid = false;
			}

			if (isValid) {
				customer->C_Email = input;
				break;
			}
			else {
				std::cout << "Invalid email format\n";
				system("pause");
			}
		} while (true);
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!!\n";
			system("pause");
		}

		if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6")
		{
			int status = customerController.updateCustomer(customer);

			if (status != 0) {
				std::cout << "Successfully updated an existing customer" << std::endl;
			}
			else {
				std::cout << "Unable to update an existing customer" << std::endl;
			}
			system("pause");
		}

	} while (select != "0");

}

void CustomerMethod::ViewAllSportCourt(){	

	ManagerMethod MGMethod;
	MGMethod.AllSportCourtDetails();

}

void CustomerMethod::MakeBooking(Customer* customer) {
	SportCourtController SportCourtCTRL;
	CourtBookingController CourtBookingCTRL;
	ManagerMethod MgMethod;

	CourtBooking* courtBooking = new CourtBooking();
	SportCourt* sportCourt = new SportCourt();
	std::string ID_OR_loop;
	std::string VoucherCode="1";				//workshopA 1 for voucher available
	float discount=0,tax=0,subTotal;

	Select:
		//Select Sport Court to make booking
		system("cls");
		ViewAllSportCourt();	//print out SportCourt

		std::cout << "\n\nPlese enter Sport Court ID to make Reservation (0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
		sportCourt = SportCourtCTRL.getSportCourtDetail_S_ID(ID_OR_loop);
	exit:
	if (sportCourt == NULL && ID_OR_loop !="0")
	{
		std::cout << "invalid input!! please try again!\n\n";
		system("pause");
		goto Select;
	}
	else if (sportCourt != NULL && sportCourt->SC_Status == "MAINTENANCE")
	{
		std::cout << "Sport Court Temporary Unavailable (Maintenance)\n\n";
		system("pause");
		goto Select;
	}
	else if (sportCourt != NULL && sportCourt->SC_Status == "UNAVAILABLE")
	{
		std::cout << "Sport Court Unavailable\n\n";
		system("pause");
		goto Select;
	}
	else if (ID_OR_loop == "0")
	{


	}
	else
	{
		//Data IN Customer_ID, SportCourt_ID, SportCourt_ID, Staff_ID, DateIN, DateOUT 

		courtBooking->Customers_ID = customer->Customers_ID;
		courtBooking->SportCourt_ID = sportCourt->SportCourt_ID;
		courtBooking->Staff_ID = sportCourt->Staff_ID;

		std::string select,input1,input2;
		int year, month;
	calendar:
		while (true) {
			system("cls");
			std::cout << "Do you want to View Calendar ? (Press any key to View / 0 to skip):";
			std::getline(std::cin, select);

			if (select == "0") {
				ExitCalender:
				break;	//skip calendar
			}
			else {
			InputYear:
				system("cls");
				std::cout << "####################======================================================<<<<   Calendar   >>>>======================================================####################\n\n";
				std::cout << "                                                                      Enter Year(0 to skip)[exp:2023] : ";
				std::getline(std::cin, input1);

				// to handling user invalid input (avoid string & space)
				try {
					year = std::stoi(input1);
				}
				catch (const std::invalid_argument& e) {
					std::cout << "Invalid input. Please enter a valid Year." << std::endl;
					system("pause");
					goto InputYear;
				}
				if (input1 == "0") {
					goto ExitCalender;					
				}
				else if (year <= 0 || year >= 9999) {
					std::cout << "Invalid input. Please enter a valid Year." << std::endl;
					system("pause");
					goto InputYear;
				}

				std::cout << "                                                                      Enter Month[exp:5 or 05] : ";
				std::getline(std::cin, input2);

				// to handling user invalid input (avoid string & space)
				try {
					month = std::stoi(input2);
				}
				catch (const std::invalid_argument& e) {
					std::cout << "Invalid input. Please enter a valid Month." << std::endl;
					system("pause");
					goto InputYear;
				}
				if (input1 == "0") {
					goto ExitCalender;
				}
				else if (month < 1 || month > 12) {
					std::cout << "Invalid input. Please enter a valid Month." << std::endl;
					system("pause");
					goto InputYear;
				}
				std::cout << "\n\n";
				MgMethod.CalendarView(year, month, courtBooking);
				std::cout << "\n\n";
				system("pause");

			}
		}//skip calendar

	InputDate:
		system("cls");
		std::cout << "DateIN (YYYY/MM/DD)(Press 1 to view Calendar /0 to exit): ";
		std::getline(std::cin, courtBooking->DateIN);
		if (courtBooking->DateIN == "0") {
			ID_OR_loop = "0";
			goto exit;
		}else if(courtBooking->DateIN == "1") {
			goto InputYear;
		}

		std::cout << "DateOut (YYYY/MM/DD): ";
		std::getline(std::cin, courtBooking->DateOUT);

		//Date Valid Check
		std::string Valid = CourtBookingCTRL.DateInValidCheck(courtBooking);

		if (Valid == "invalid input")
		{
			std::cout << "\nInvalid Date Input! (Format:YYYY/MM/DD Example: 2023/11/10 and DateOut must greater than DateIN)\n";
			system("pause");
			goto InputDate;
		}
		else if (Valid == "Can't Booking Current date or Previous date")
		{
			std::cout << "\nInvalid Date Input! (" + Valid + ")\n";
			system("pause");
			goto InputDate;
		}
		else if (Valid == "true")	//Date is Valid
		{
			//to check which one clash the booking time
			std::pair<int, int> values = CourtBookingCTRL.DuplicateBookingCheck(courtBooking);//Pass By Reference
			int StartClash = values.first;
			int EndClash = values.second;

			if (StartClash == 1 && EndClash == 1)			//RHS & LHS clash
			{
				std::cout << "Sorry,Already Booked By Other\n";
				system("pause");
				goto InputDate;
			}
			else if (StartClash == 1 && EndClash == 0)		//RHS clash
			{
				std::cout << "Sorry,Already Booked By Other (DateIN clash)\n";
				system("pause");
				goto InputDate;
			}
			else if (StartClash == 0 && EndClash == 1)		//LHS clash
			{
				std::cout << "Sorry,Already Booked By Other (DateOUT clash)\n";
				system("pause");
				goto InputDate;
			}
			else if (StartClash == 0 && EndClash == 0)
			{
				if (!courtBooking->Match)
				{	//clash other booking date 
					std::cout << "Sorry,Already Booked By Other (Someone Booked Between DateIN and DateOut)";
					system("pause");
					goto InputDate;
				}
				else
				{	//no clashing other booking date
					//############## CourtBooking ID ##################

					//Auto genarate ID Algorithm (Format VXXXXXXXX) V=IDType(C=Customer,S=staff,M=Manager,SC=Sport Court,B=Booking), X = variable(0-9)
					CourtBooking* getNewestSportCourtID = CourtBookingCTRL.getCourtBookingIDForInsert();

					if (getNewestSportCourtID != NULL) {
						std::string ID, NumAfter, d, e;	//d=covert to string after+1 , e= compose ID
						ID = getNewestSportCourtID->CourtBooking_ID;

						NumAfter = ID.substr(2, 8);		//Starting position = 2, length = 8 (get num after the position)
						int b = stoi(NumAfter) + 1;		//convert String(c) to int type +1

						if (b >= 0 && b <= 9)
						{
							d = std::to_string(b);
							e = "B0000000" + d;
						}
						else if (b >= 10 && b <= 99)
						{
							d = std::to_string(b);
							e = "B000000" + d;
						}
						else if (b >= 100 && b <= 999)
						{
							d = std::to_string(b);
							e = "B00000" + d;
						}
						else if (b >= 1000 && b <= 9999)
						{
							d = std::to_string(b);
							e = "B0000" + d;
						}
						else if (b >= 10000 && b <= 99999)
						{
							d = std::to_string(b);
							e = "B000" + d;
						}
						else if (b >= 100000 && b <= 999999)
						{
							d = std::to_string(b);
							e = "B00" + d;
						}
						else if (b >= 1000000 && b <= 9999999)
						{
							d = std::to_string(b);
							e = "B0" + d;
						}
						else if (b >= 10000000 && b <= 99999999)
						{
							d = std::to_string(b);
							e = "B" + d;
						}
						courtBooking->CourtBooking_ID = e;
					}
					else {				//if no data in database, start at default
						courtBooking->CourtBooking_ID = "B00000001";
					}

					//Customer_ID, SportCourt_ID, SportCourt_ID, Staff_ID, DateIN, DateOUT done by previous method

					if (CourtBookingCTRL.CountDay(courtBooking) != NULL && CourtBookingCTRL.CountDay(courtBooking) != 0)
					{	//Total Day
						courtBooking->TotalDay = CourtBookingCTRL.CountDay(courtBooking);

						//SubTotal (TotalDay * PricePerDay)
						subTotal = float(courtBooking->TotalDay * sportCourt->PricePerDay);

						//Select Payment Type
						std::string select;
					SelectType:
						system("cls");

						// vouchar   discount
						while (VoucherCode == "1") {
							system("cls");
							std::cout << "Do you have Voucher Code? (0 to skip):\n";
							std::getline(std::cin, VoucherCode);

							if (VoucherCode == "workshopA") {			
								VoucherCode = "0";
								std::cout << "Voucher Applied (get 10% discount)\n";

								discount = subTotal * 0.10;
								//SubTotal=(TotalDay * PricePerDay)-discount
								subTotal= float(courtBooking->TotalDay * sportCourt->PricePerDay) - discount;
								
								
								system("pause");
							}
							else if (VoucherCode == "0") {
								VoucherCode = "0";						
							}
							else {
								std::cout << "Invalid Voucher Code, Please try Again\n";
								system("pause");
								VoucherCode = "1";
							}
							system("cls");
						}
						//tax calculation
						tax = float(subTotal * 0.06);
						courtBooking->TotalCharge = subTotal + tax;

						std::cout << std::fixed << std::setprecision(2);
						std::cout << "==================================================================================\n";
						std::cout << "======================== Confirmation Booking information ========================\n";
						std::cout << "==================================================================================\n\n";

						std::cout << "                    <<<<<<<<<< Customer Infomation >>>>>>>>>> \n";
						std::cout << "                         Customer ID      : " << courtBooking->Customers_ID << std::endl;
						std::cout << "                         Customer Name    : " << customer->C_Name << std::endl << std::endl;

						std::cout << "                    <<<<<<<<<< Booking Infomation >>>>>>>>>> \n";
						std::cout << "                         Sport Court ID   :  " << courtBooking->SportCourt_ID << std::endl;
						std::cout << "                         Sport Court Name :  " << sportCourt->SC_Name << std::endl;
						std::cout << "                         Date Check In    :  " << courtBooking->DateIN << std::endl;
						std::cout << "                         Date Check Out   :  " << courtBooking->DateOUT << std::endl;
						std::cout << "                         Total Day        :  " << courtBooking->TotalDay << std::endl;
						std::cout << "                         Price Per Day    :  " << sportCourt->PricePerDay << std::endl;
						std::cout << "                         Staff ID         :  " << courtBooking->Staff_ID << std::endl << std::endl;

						std::cout << "==================================================================================\n\n";

						std::cout << "                         Discount         :  " << discount << std::endl;
						std::cout << "                         SubTotal         :  " << subTotal << std::endl;
						std::cout << "                         Service Tax (6%) :  " << tax << std::endl << std::endl;

						std::cout << "==================================================================================\n";
						std::cout << "                         Total Charge     :RM" << courtBooking->TotalCharge << std::endl;
						std::cout << "==================================================================================\n";
						std::cout << "#### Please confirm that the information is true before payment (no refund) ####\n";
						std::cout << "==================================================================================\n\n";

						

						std::cout << "                         ++++++++++ Payment Type ++++++++++\n";
						std::cout << "                               1.Online Banking\n";
						std::cout << "                               2.Touch and Go (TNG eWallet)\n";
						std::cout << "                               3.Credit/Debit Card (Visa)\n";
						std::cout << "                               4.Cash\n";
						std::cout << "                               0.Cancel Booking\n";
						std::cout << "                               Select Payment Type(0-3): ";
						std::getline(std::cin, select);

						if (select == "1") {
							courtBooking->PaymentType = "Online Banking";
						}
						else if (select == "2") {
							courtBooking->PaymentType = "Touch and Go";
						}
						else if (select == "3") {
							courtBooking->PaymentType = "Credit/Debit Card";
						}
						else if (select == "4") {
							courtBooking->PaymentType = "Cash";
						}
						else if (select == "0") {
							//cancel Booking
						}
						else {
							std::cout << "invalid input!! please try again!\n\n";
							system("pause");
							goto SelectType;
						}

						int status = 0;

						if (select == "1" || select == "2" || select == "3" || select == "4")
						{
							//Insert Booking
							status = CourtBookingCTRL.insertCourtBooking(courtBooking);
						}

						if (status != 0)
						{
							std::cout << "Successfully Booking" << std::endl;
							system("pause");
							system("cls");
							//============================ Receipt =====================================
							std::cout << "                                         <<<<<<        R E C E I P T         >>>>>>\n";
							std::cout << "=============================================================================================================================\n";
							std::cout << "================================================ Colby College sports Centre ================================================\n";
							std::cout << "=============================================================================================================================\n\n";

							std::cout << "\t   Customer Name   : "  <<customer->C_Name << std::endl;
							std::cout << "\t   Booking ID      : "  <<courtBooking->CourtBooking_ID << std::endl;
							std::cout << "\t   Check In Date   : "  << courtBooking->DateIN << std::endl;
							std::cout << "\t   Check Out Date  : "  << courtBooking->DateOUT << std::endl << std::endl;

							std::cout << "=============================================================================================================================\n";
							std::cout << " Sport Court ID          Sport Court Name         Price Per Day         Total Day          Total Charge        Payment Method\n";
							std::cout << "=============================================================================================================================\n";
							std::cout 
								<< std::setw(14)<<courtBooking->SportCourt_ID
								<< std::setw(26) << sportCourt->SC_Name
								<< std::setw(20) << sportCourt->PricePerDay
								<< std::setw(20) << courtBooking->TotalDay
								<< std::setw(20) << subTotal+discount
								<< std::setw(25) << courtBooking->PaymentType << std::endl;
							std::cout << "=============================================================================================================================\n\n";

							std::cout << "                                                                                        Total Discount   :  " << std::setw(10) << discount << std::endl;
							std::cout << "                                                                                        SubTotal         :  " << std::setw(10) << subTotal << std::endl;
							std::cout << "                                                                                        Sevice Tax (6%)  :  " << std::setw(10) << tax << std::endl;
							std::cout << "                                                                                        Total Price      :RM" << std::setw(10) << courtBooking->TotalCharge << std::endl << std::endl << std::endl;



							std::cout << "\n\n";
							std::cout << "\t   Office Phone No.      :  010-3352070 \n";
							std::cout << "\t   Office Email          :  Colby@CCSC.edu.my \n";
							std::cout << "\t   Sport Court Location  :  Pahang, Raub District, Sungai Ruan 27500 \n\n";

							//============== file =========================
							//export file
							std::ofstream outfile;
							outfile.open("Receipt.txt");

							if (outfile.is_open()) {
								outfile << "                                         <<<<<<        R E C E I P T         >>>>>>\n";
								outfile << "=============================================================================================================================\n";
								outfile << "================================================ Colby College sports Centre ================================================\n";
								outfile << "=============================================================================================================================\n\n";

								outfile << "\t   Customer Name   : " << customer->C_Name << std::endl;
								outfile << "\t   Booking ID      : " << courtBooking->CourtBooking_ID << std::endl;
								outfile << "\t   Check In Date   : " << courtBooking->DateIN << std::endl;
								outfile << "\t   Check Out Date  : " << courtBooking->DateOUT << std::endl << std::endl;

								outfile << "=============================================================================================================================\n";
								outfile << " Sport Court ID          Sport Court Name         Price Per Day         Total Day          Total Charge        Payment Method\n";
								outfile << "=============================================================================================================================\n";
								outfile
									<< std::setw(14) << courtBooking->SportCourt_ID
									<< std::setw(26) << sportCourt->SC_Name
									<< std::setw(20) << sportCourt->PricePerDay
									<< std::setw(20) << courtBooking->TotalDay
									<< std::setw(20) << subTotal + discount
									<< std::setw(25) << courtBooking->PaymentType << std::endl;
								outfile << "=============================================================================================================================\n\n";

								outfile << "                                                                                        Total Discount   :  " << std::setw(10) << discount << std::endl;
								outfile << "                                                                                        SubTotal         :  " << std::setw(10) << subTotal << std::endl;
								outfile << "                                                                                        Sevice Tax (6%)  :  " << std::setw(10) << tax << std::endl;
								outfile << "                                                                                        Total Price      :RM" << std::setw(10) << courtBooking->TotalCharge << std::endl << std::endl << std::endl;



								outfile << "\n\n";
								outfile << "\t   Office Phone No.      :  010-3352070 \n";
								outfile << "\t   Office Email          :  Colby@CCSC.edu.my \n";
								outfile << "\t   Sport Court Location  :  Pahang, Raub District, Sungai Ruan 27500 \n\n";

								outfile.close();
								
								std::cout << "\nSuccessfully export Receipt.txt" << std::endl;
							}


						}
						else
						{
							std::cout << "Unable to Booking" << std::endl;
							
						}
					}
					else
					{
						std::cout << "Something went Wrong in CountDay";
						system("pause");
					}
				}
			}
			else
			{
				std::cout << "Something went Wrong in Clash Booking";
				system("pause");
			}
			
		}
		else
		{
			std::cout << "Something went Wrong in valid Date";
			system("pause");
		}
	}

}

void CustomerMethod::UpComing(Customer* customer) {
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBookings = courtBookingController.getCourtBookingDetail_S_UpComingForCustomer(customer->Customers_ID);

	if (courtBookings != NULL)
	{
		PrintOutBookingInfo(courtBookings);
	}

	else
	{
		std::cout << "Not Upcoming Reservations" << std::endl;
	}
}

void CustomerMethod::CheckMyBookingHistory(Customer* customer){
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBookings = courtBookingController.getCourtBookingDetail_S_CustomerID(customer->Customers_ID);

	if (courtBookings != NULL)
	{
		PrintOutBookingInfo(courtBookings);
	}

	else
	{
		std::cout << "Not record" << std::endl;
	}
}

void CustomerMethod::PrintOutBookingInfo(CourtBooking* courtBookings) {

	CourtBooking* courtBooking = courtBookings;

	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(16) << " CourtBooking_ID "
		<< std::setw(14) << " Customer_ID "
		<< std::setw(16) << " SportCourt_ID "
		<< std::setw(19) << " SportCourt    "
		<< std::setw(14) << " Staff_ID "
		<< std::setw(14) << " DateIN "
		<< std::setw(16) << " DateOUT "
		<< std::setw(16) << " TotalDay "
		<< std::setw(17) << " TotalCharge "
		<< std::setw(20) << " PaymentType " << std::endl;
	std::cout << "=====================================================================================================================================================================" << std::endl << std::endl;
	do
	{

		std::cout << std::setw(14) << courtBooking->CourtBooking_ID
			<< std::setw(15) << courtBooking->Customers_ID
			<< std::setw(15) << courtBooking->SportCourt_ID
			<< std::setw(20) << courtBooking->SC_Name
			<< std::setw(15) << courtBooking->Staff_ID
			<< std::setw(16) << courtBooking->DateIN
			<< std::setw(16) << courtBooking->DateOUT
			<< std::setw(12) << courtBooking->TotalDay
			<< std::setw(15) << courtBooking->TotalCharge
			<< std::setw(25) << courtBooking->PaymentType << std::endl;

		courtBooking = courtBooking->next;

	} while (courtBooking != NULL);
}