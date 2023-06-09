#include "StaffMethod.h"
#include <iomanip>
#include <conio.h>

void StaffMethod::StaffDetial(Staff* staff){
	StaffController staffController;

//	staff = staffController.getStaffDetail_S_ID(staff->Staff_ID);
	system("cls");
	std::cout << "\n=================================================" << std::endl;
	std::cout
		<< "Staff_ID: " << staff->Staff_ID << std::endl
		<< "Manager_ID: " << staff->Manager_ID << std::endl
		<< "Staff Name: " << staff->S_Name << std::endl
		<< "Staff Gender: " << staff->S_Gender << std::endl
		<< "Staff HpNo: " << staff->S_HpNo << std::endl
		<< "Staff Email: " << staff->S_Email << std::endl
		<< "Status: " << staff->status << std::endl;
	std::cout << "=================================================" << std::endl;
}

void StaffMethod::StaffSelfUpdate(Staff* staff) {
	std::string ID_OR_loop, select;
	StaffController staffController;
	ManagerMethod MgMethod;

	do {
	update1:
		system("cls");
		std::cout << "Staff ID : " << staff->Staff_ID << std::endl;
		std::cout << "which one you want to update?" << std::endl;
		std::cout << "1.Staff Name" << std::endl;
		std::cout << "2.Staff Password" << std::endl;
		std::cout << "3.Staff Gender" << std::endl;
		std::cout << "4.Staff HpNo" << std::endl;
		std::cout << "5.Staff Email" << std::endl;
		std::cout << "0.Exit" << std::endl;
		std::cout << "Select(0-5) :";
		std::getline(std::cin, select);

		std::string input;
		if (select == "1")
		{
			//############## Staff name ##################
			system("cls");
			std::cout << "Staff Name(0 to exit): ";
			std::getline(std::cin, input);

			if (input != "0") {
				staff->S_Name = input;
			}
			else {
				goto update1;
			}
		}
		else if (select == "2") {
			//############## Staff password ##################
			
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
				staff->password = temp2;
			}
			else
			{
				std::cout << "password not match!! please try again!\n\n";
				system("pause");
				goto password;
			}
		}
		else if (select == "3") {
			//############## staff Gender ##################

			std::string selectG;
		Select:
			system("cls");
			std::cout << "Select Gender (1=Male, 2=Female, 3=Other)(0 to exit): ";
			std::getline(std::cin, select);

			if (select == "1") {
				staff->S_Gender = "Male";
			}
			else if (select == "2") {
				staff->S_Gender = "Famale";
			}
			else if (select == "3") {
				staff->S_Gender = "Other";
			}
			else if (select == "0") {
				goto update1;
			}
			else {
				std::cout << "invalid input!! please try again!\n\n";
				system("pause");
				goto Select;
			}
		}
		else if (select == "4") {
			//############## staff HpNo ##################
			do {
				system("cls");

				std::string input;
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
					staff->S_HpNo = input;
					break;
				}
				else {
					std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
					system("pause");
				}
			} while (true);
		}
		else if (select == "5") {

		//############## staff Email ##################
		do {
			system("cls");

			std::string input;
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
				staff->S_Email = input;
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

		if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" )
		{
			int status = staffController.updateStaff(staff);

			if (status != 0) {
				std::cout << "Successfully updated an existing staff" << std::endl;
			}
			else {
				std::cout << "Unable to update an existing staff" << std::endl;
			}
			system("pause");
		}

	} while (select != "0");
}

void StaffMethod::UpComingTask(Staff* staff) {
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBookings = courtBookingController.getCourtBookingDetail_S_UpComingForStaff(staff->Staff_ID);

	if (courtBookings != NULL)
	{
		PrintOutBookingInfo(courtBookings);
	}

	else
	{
		std::cout << "Not Upcoming Reservations" << std::endl;
	}
}

void StaffMethod::AllHistoryTask(Staff* staff) {
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBookings = courtBookingController.getCourtBookingDetail_S_StaffID(staff->Staff_ID);

	if (courtBookings != NULL)
	{
		PrintOutBookingInfo(courtBookings);
	}

	else
	{
		std::cout << "Not History Task" << std::endl;
	}
}

void StaffMethod::PrintOutBookingInfo(CourtBooking* courtBookings) {

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


//reuse Manager Method
//########################## Customer Method For Admin ################
//########################## Staff Search #############################
//########################## Manager Search ###########################