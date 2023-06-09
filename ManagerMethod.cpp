#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<cstdlib>  
#include<time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>

#include "ManagerMethod.h"
#include "CustomerMethod.h"	//for reuse some method  (insert customer, insert booking
#include <algorithm>

//temp
#include "CourtBookingController.h"
#include "CourtBooking.h"

//########################## Customer Method For Admin #############################/
void ManagerMethod::InsertCustomer() {
	Customer* customer = new Customer();
	std::string again;

	CustomerMethod customerMethod;

	do {
		again=customerMethod.CustomerRegister();
		if (again == "0")
			break;
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, again);
	} while (again != "0");
}

void ManagerMethod::UpdateCustomer() {
	std::string ID_OR_loop, select;
	CustomerController customerController;

	do {
	update:
		system("cls");
		std::cout << "========= Customer Update =========" << std::endl;
		std::cout << "Please input Customers_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Customer* customer = customerController.getCustomerDetail_S_ID(ID_OR_loop);

		if (customer != NULL)
		{
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
				std::cout << "7.Status" << std::endl;
				std::cout << "0.Exit" << std::endl;
				std::cout << "Select(0-7) :";
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
					std::cout << "Select Type (1=Individual, 2=Organization)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						customer->C_Type = "Individual";
					}
					else if (select == "2") {
						customer->C_Type = "Organization";
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
				else if (select == "7") {
					//############## staff status ##################
					system("cls");
					std::string select;
				SelectStatus:
					std::cout << "Select status (1=Active, 2=Frozen)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						customer->status = "Active";
					}
					else if (select == "2") {
						customer->status = "Frozen";
					}
					else if (select == "0") {
						goto update1;
					}
					else {
						std::cout << "invalid input!! please try again!\n\n";
						goto SelectStatus;
					}
				}
				else if (select == "0") {
					goto update;
					break;
				}
				else {
					std::cout << "invalid input!!\n";
					system("pause");
				}

				if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6" || select == "7")
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
		else if (ID_OR_loop == "0") {
			break;
		}
		else {
			std::cout << "customer not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DeleteCustomer() {

	CustomerController customerController;
	std::string ID_OR_loop;

	do {
		system("cls");

		std::cout << "========= Customer Delete =========" << std::endl;
		std::cout << "Please input Customers_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Customer* customer = customerController.getCustomerDetail_S_ID(ID_OR_loop);

		if (customer != NULL) {
			int status=0;

			try {
				status = customerController.deleteCustomer(customer);
			}
			catch (sql::SQLException) {
				std::cout << "Can't Delete this Customer, Recorded in Booking\n";		
			}
			catch (...) {
				std::cout << "something went wrong! please restart! \n";
				system("pause");
			}

			if (status != 0)
			{
				std::cout << "Successfully Delete an existing customer" << std::endl;
			}
			else
			{
				std::cout << "Unable to Delete an existing customer" << std::endl;
			}

		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "customer not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::IDSearchCustomer() {
	std::string ID_OR_loop;
	CustomerController customerController;

	do {
		system("cls");

		std::cout << "========= Customer Search =========" << std::endl;
		std::cout << "Please input Customers_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Customer* customer = customerController.getCustomerDetail_S_ID(ID_OR_loop);

		if (customer != NULL)
		{
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
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::NameSearchCustomer() {
	std::string Name_OR_loop;
	CustomerController customerController;

	do {
		system("cls");

		std::cout << "========= Customer Search =========" << std::endl;
		std::cout << "Please input Customer's Name(0 to exit): ";
		std::getline(std::cin, Name_OR_loop);

		Customer* customer = customerController.getCustomerDetail_S_Name(Name_OR_loop);

		if (customer != NULL)
		{
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
		else if (Name_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, Name_OR_loop);
	} while (Name_OR_loop != "0");
}

void ManagerMethod::TypeSearchCustomer() {
	std::string C_Type;
	CustomerController customerController;

	std::string select;
	do {
	SelectType:
		system("cls");
		std::cout << "========= Customer Type Search =========" << std::endl;
		std::cout << "Select Type (1=Individual, 2=Organization, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			C_Type = "Individual";
		}
		else if (select == "2") {
			C_Type = "Organization";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			system("cls");
			goto SelectType;
		}

		Customer* customers = customerController.getCustomerDetail_S_Type(C_Type);

		if (customers != NULL)
		{
			PrintOutCustomerInfo(customers);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::AddressSearchCustomer() {
	std::string C_AddressORLoop;
	CustomerController customerController;

	do {
	SelectType:
		system("cls");
		std::cout << "========= Customer Address Search =========" << std::endl;
		std::cout << "Please input Customers Address(0 to exit): ";
		std::getline(std::cin, C_AddressORLoop);

		Customer* customers = customerController.getCustomerDetail_S_Address(C_AddressORLoop);

		if (customers != NULL)
		{
			PrintOutCustomerInfo(customers);
		}
		else if (C_AddressORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, C_AddressORLoop);
	} while (C_AddressORLoop != "0");
}

void ManagerMethod::HpNoSearchCustomer() {
	std::string HpNoORLoop;
	CustomerController customerController;

	do {
	SelectType:
		system("cls");
		std::cout << "========= Customer HpNo Search =========" << std::endl;
		std::cout << "Please input Customers HpNo(0 to exit): ";
		std::getline(std::cin, HpNoORLoop);

		Customer* customers = customerController.getCustomerDetail_S_HpNo(HpNoORLoop);

		if (customers != NULL)
		{
			PrintOutCustomerInfo(customers);
		}
		else if (HpNoORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, HpNoORLoop);
	} while (HpNoORLoop != "0");
}

void ManagerMethod::EmailSearchCustomer() {
	std::string EmailORLoop;
	CustomerController customerController;

	do {
	SelectType:
		system("cls");
		std::cout << "========= Customer Email Search =========" << std::endl;
		std::cout << "Please input Customers Email(0 to exit): ";
		std::getline(std::cin, EmailORLoop);

		Customer* customers = customerController.getCustomerDetail_S_Email(EmailORLoop);

		if (customers != NULL)
		{
			PrintOutCustomerInfo(customers);
		}
		else if (EmailORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, EmailORLoop);
	} while (EmailORLoop != "0");
}

void ManagerMethod::StatusSearchCustomer() {
	std::string status;
	CustomerController customerController;

	std::string select;
	do {
	SelectStatus:
		system("cls");
		std::cout << "========= Customer Status Search =========" << std::endl;
		std::cout << "Select Status (1=Active, 2=Frozen, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			status = "Active";
		}
		else if (select == "2") {
			status = "Frozen";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			system("cls");
			goto SelectStatus;
		}

		Customer* customers = customerController.getCustomerDetail_S_Status(status);

		if (customers != NULL)
		{
			PrintOutCustomerInfo(customers);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::AllCustomerDetails() {
	system("cls");
	CustomerController customerController;

	Customer* customers = customerController.getAllCustomerDetails();

	if (customers != NULL)
	{
		PrintOutCustomerInfo(customers);
	}

	else
	{
		std::cout << "Customers not found" << std::endl;
	}
	system("pause");
}

void ManagerMethod::PrintOutCustomerInfo(Customer* customers) {
	Customer* customer = customers;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(15) << " Customers_ID "
		<< std::setw(25) << " Customer Name "
		<< std::setw(19) << " Customer Type "
		<< std::setw(30) << " Customer Address "
		<< std::setw(20) << " Customer HpNo "
		<< std::setw(30) << " Customer Email "
		<< std::setw(20) << " Status " << std::endl;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	do
	{
		std::cout << std::setw(13) << customer->Customers_ID
			<< std::setw(25) << customer->C_Name
			<< std::setw(20) << customer->C_Type
			<< std::setw(30) << customer->C_Address
			<< std::setw(20) << customer->C_HpNo
			<< std::setw(30) << customer->C_Email
			<< std::setw(20) << customer->status << std::endl;

		customer = customer->next;

	} while (customer != NULL);
}


//########################## Staff Method #############################/
void ManagerMethod::InsertStaff() {
	Staff* staff = new Staff();
	std::string again;

	StaffController staffController;

	do {
		system("cls");
		//############## Staff ID ##################

		//Auto genarate ID Algorithm (Format VXXXXXXXX) V=IDType(C=Customer,S=staff,M=Manager,SC=Sport Court), X = variable(0-9)
		Staff* getNewestStaffID = staffController.getStaffIDForInsert();

		if (getNewestStaffID != NULL) {
			std::string ID, NumAfter, d, e;	//d=covert to string after+1 , e= compose ID
			ID = getNewestStaffID->Staff_ID;

			NumAfter = ID.substr(1, 8);		//Starting position = 1, length = 8 (get num after the position)
			int b = stoi(NumAfter) + 1;		//convert String(c) to int type +1

			if (b >= 0 && b <= 9)
			{
				d = std::to_string(b);
				e = "S0000000" + d;
			}
			else if (b >= 10 && b <= 99)
			{
				d = std::to_string(b);
				e = "S000000" + d;
			}
			else if (b >= 100 && b <= 999)
			{
				d = std::to_string(b);
				e = "S00000" + d;
			}
			else if (b >= 1000 && b <= 9999)
			{
				d = std::to_string(b);
				e = "S0000" + d;
			}
			else if (b >= 10000 && b <= 99999)
			{
				d = std::to_string(b);
				e = "S000" + d;
			}
			else if (b >= 100000 && b <= 999999)
			{
				d = std::to_string(b);
				e = "S00" + d;
			}
			else if (b >= 1000000 && b <= 9999999)
			{
				d = std::to_string(b);
				e = "S0" + d;
			}
			else if (b >= 10000000 && b <= 99999999)
			{
				d = std::to_string(b);
				e = "S" + d;
			}
			staff->Staff_ID = e;
		}
		else {				//if no data in database, start at default
			staff->Staff_ID = "S00000001";
		}

		std::string input;
		//############## Staff's Manager ID select ##################11111111111111111111111111111111
		ManagerController MGCTRL;
	Again:
		AllManagerDetails();
		std::cout << "Enter manager ID(0 to exit): ";
		std::getline(std::cin, input);

		if (input == "0") {
		end:
			break;
		}

		Manager* manager = MGCTRL.getManagerDetail_S_ID(input);

		if (manager == NULL) {
			std::cout << "Manager not found please try again !!\n";
			system("pause");
			goto Again;
		}

		staff->Manager_ID = manager->Manager_ID;

		//############## Staff name ##################
	name:
		system("cls");
		std::cout << "S_Name(0 to exit): ";
		std::getline(std::cin, input);

		Staff* Duplication = staffController.getStaffDetail_S_Name(input);

		if (input == "0") {
			goto end;
		}
		else if (Duplication != NULL) {
			std::cout << "\nUsername registered!! \n";
			system("pause");
			goto name;
		}
		else {
			staff->S_Name = input;
		}

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
			staff->password = temp2;
		}
		else
		{
			std::cout << "password not match!! please try again!\n\n";
			system("pause");
			goto password;
		}

		//############## staff Gender ##################

		std::string select;
	Select:
		system("cls");
		std::cout << "Select Gender (1=Male, 2=Female, 3=Other)(0 to exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			staff->S_Gender = "Male";
		}
		else if (select == "2") {
			staff->S_Gender = "Female";
		}
		else if (select == "3") {
			staff->S_Gender = "Other";
		}
		else if (select == "0") {
			goto end;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		//############## staff HpNo ##################

		do {
			system("cls");

			std::string input;
			bool valid = true;

			std::cout << "Enter a phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
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
				staff->S_HpNo = input;
				break;
			}
			else {
				std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
				system("pause");
			}
		} while (true);

		//############## staff Email ##################
		do {
			system("cls");

			std::string input;
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
				staff->S_Email = input;
				break;
			}
			else {
				std::cout << "Invalid email format\n";
				system("pause");
			}
		} while (true);

		//account status
		staff->status = "Active";

		//=================== Insert staff ===================
		int status = 0;
		std::string sure;

		system("cls");
		std::cout << "======================= Confirmation information =======================" << std::endl;
		std::cout
			<< "staff_ID: " << staff->Staff_ID << std::endl
			<< "Manager_ID: " << staff->Manager_ID << std::endl
			<< "S_Name: " << staff->S_Name << std::endl
			<< "S_Gender: " << staff->S_Gender << std::endl
			<< "S_HpNo: " << staff->S_HpNo << std::endl
			<< "S_Email: " << staff->S_Email << std::endl;
		std::cout << "==========================================================================" << std::endl;
		std::cout << "Please confirm that the information is true? (Press any Key to continue)(0 to cancel Registration) :";
		std::getline(std::cin, sure);

		if (sure != "0") {
			status = staffController.insertStaff(staff);
		}

		if (status != 0)
			std::cout << "Successfully added a new staff" << std::endl;
		else
			std::cout << "Unable to add a new staff" << std::endl;

		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, again);
	} while (again != "0");
}

void ManagerMethod::UpdateStaff() {
	std::string ID_OR_loop, select;
	StaffController staffController;

	do {
	update:
		system("cls");
		std::cout << "========= Staff Update =========" << std::endl;
		std::cout << "Please input Staff_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Staff* staff = staffController.getStaffDetail_S_ID(ID_OR_loop);

		if (staff != NULL)
		{
			do {
			update1:
				system("cls");
				std::cout << "Staff ID : " << staff->Staff_ID << std::endl;
				std::cout << "which one you want to update?" << std::endl;
				std::cout << "1.Staff Manager ID" << std::endl;
				std::cout << "2.Staff Name" << std::endl;
				std::cout << "3.Staff Password" << std::endl;
				std::cout << "4.Staff Gender" << std::endl;
				std::cout << "5.Staff HpNo" << std::endl;
				std::cout << "6.Staff Email" << std::endl;
				std::cout << "7.Status " << std::endl;
				std::cout << "0.Exit" << std::endl;
				std::cout << "Select(0-7) :";
				std::getline(std::cin, select);

				std::string input;

				if (select == "1") {
					//############## Staff's Manager ID select ##################11111111111111111111111111111111
					ManagerController MGCTRL;
				Again:
					AllManagerDetails();
					std::cout << "Enter manager ID(0 to exit): ";
					std::getline(std::cin, input);

					if (input == "0") {
						goto update1;
					}

					Manager* manager = MGCTRL.getManagerDetail_S_ID(input);

					if (manager == NULL) {
						std::cout << "Manager not found please try again !!\n";
						system("pause");
						goto Again;
					}

					staff->Manager_ID = manager->Manager_ID;
				}
				else if (select == "2") 
				{
					//############## Staff name ##################
					system("cls");
					std::cout << "S_Name(0 to exit): ";
					std::getline(std::cin, input);

					if (input != "0") {
						staff->S_Name = input;
					}
					else {
						goto update1;
					}
				}
				else if (select == "3") {
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
				else if (select == "4") {
					//############## staff Gender ##################

					std::string select;
				Select:
					system("cls");
					std::cout << "Select Gender (1=Male, 2=Female, 3=Other)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						staff->S_Gender = "Male";
					}
					else if (select == "2") {
						staff->S_Gender = "Female";
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
				else if (select == "5") {
					//############## staff HpNo ##################
					do {
						system("cls");

						std::string input;
						bool valid = true;

						std::cout << "Enter a phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
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
				else if (select == "6") {

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
				else if (select == "7") {
					//############## staff status ##################
					system("cls");
					std::string select;
				SelectStatus:
					std::cout << "Select status (1=Active, 2=Frozen)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						staff->status = "Active";
					}
					else if (select == "2") {
						staff->status = "Frozen";
					}
					else if (select == "0") {
						goto update1;
					}
					else {
						std::cout << "invalid input!! please try again!\n\n";
						goto SelectStatus;
					}
				}
				else if (select == "0") {
					goto update;
					break;
				}
				else {
					std::cout << "invalid input!!\n";
					system("pause");
				}

				if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6" || select == "7")
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
		else if (ID_OR_loop == "0") {
			break;
		}
		else {
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DeleteStaff() {

	StaffController staffController;
	std::string ID_OR_loop;

	do {
		system("cls");

		std::cout << "========= Staff Delete =========" << std::endl;
		std::cout << "Please input Staff_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Staff* staff = staffController.getStaffDetail_S_ID(ID_OR_loop);

		if (staff != NULL) {
			int status = staffController.deleteStaff(staff);

			if (status != 0)
			{
				std::cout << "Successfully Delete or Frozen an existing staff" << std::endl;
			}
			else
			{
				std::cout << "Unable to Delete or Frozen an existing staff" << std::endl;
			}

		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::IDSearchStaff() {
	std::string ID_OR_loop;
	StaffController staffController;

	do {
		system("cls");

		std::cout << "========= Staff Search =========" << std::endl;
		std::cout << "Please input Staff_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Staff* staff = staffController.getStaffDetail_S_ID(ID_OR_loop);

		if (staff != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "staff_ID: " << staff->Staff_ID << std::endl
				<< "Manager_ID: " << staff->Manager_ID << std::endl
				<< "S_Name: " << staff->S_Name << std::endl
				<< "S_Gender: " << staff->S_Gender << std::endl
				<< "S_HpNo: " << staff->S_HpNo << std::endl
				<< "S_Email: " << staff->S_Email << std::endl
				<< "Status: " << staff->status << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::MIDSearchStaff() {
	std::string ID_OR_loop;
	StaffController staffController;

	do {
		system("cls");

		std::cout << "################## Search Staff by Manager ID ##################" << std::endl;
		std::cout << "Please input Manager_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Staff* staffs = staffController.getStaffDetail_S_MID(ID_OR_loop);

		if (staffs != NULL)
		{
			system("cls");
			PrintOutStaffInfo(staffs);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::NameSearchStaff() {
	std::string Name_OR_loop;
	StaffController staffController;

	do {
		system("cls");

		std::cout << "========= Staff Search =========" << std::endl;
		std::cout << "Please input Staff's Name(0 to exit): ";
		std::getline(std::cin, Name_OR_loop);

		Staff* staff = staffController.getStaffDetail_S_Name(Name_OR_loop);

		if (staff != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "staff_ID: " << staff->Staff_ID << std::endl
				<< "Manager_ID: " << staff->Manager_ID << std::endl
				<< "S_Name: " << staff->S_Name << std::endl
				<< "S_Gender: " << staff->S_Gender << std::endl
				<< "S_HpNo: " << staff->S_HpNo << std::endl
				<< "S_Email: " << staff->S_Email << std::endl
				<< "Status: " << staff->status << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (Name_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, Name_OR_loop);
	} while (Name_OR_loop != "0");
}

void ManagerMethod::GenderSearchStaff() {
	std::string S_Gender;
	StaffController staffController;

	std::string select;
	do {

	Select:
		system("cls");
		std::cout << "========= Staff Gender Search =========" << std::endl;
		std::cout << "Select Type (1=Male, 2=Female, 3=Other, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			S_Gender = "Male";
		}
		else if (select == "2") {
			S_Gender = "Female";
		}
		else if (select == "3") {
			S_Gender = "Other";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		Staff* staffs = staffController.getStaffDetail_S_Gender(S_Gender);

		if (staffs != NULL)
		{
			PrintOutStaffInfo(staffs);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::HpNoSearchStaff() {
	std::string HpNoORLoop;
	StaffController staffController;

	do {

		system("cls");
		std::cout << "========= Staff HpNo Search =========" << std::endl;
		std::cout << "Please input Staff HpNo(0 to exit): ";
		std::getline(std::cin, HpNoORLoop);

		Staff* staffs = staffController.getStaffDetail_S_HpNo(HpNoORLoop);

		if (staffs != NULL)
		{
			PrintOutStaffInfo(staffs);
		}
		else if (HpNoORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, HpNoORLoop);
	} while (HpNoORLoop != "0");
}

void ManagerMethod::EmailSearchStaff() {
	std::string EmailORLoop;
	StaffController staffController;

	do {

		system("cls");
		std::cout << "========= Staff Email Search =========" << std::endl;
		std::cout << "Please input Staff Email(0 to exit): ";
		std::getline(std::cin, EmailORLoop);

		Staff* staffs = staffController.getStaffDetail_S_Email(EmailORLoop);

		if (staffs != NULL)
		{
			PrintOutStaffInfo(staffs);
		}
		else if (EmailORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, EmailORLoop);
	} while (EmailORLoop != "0");
}

void ManagerMethod::StatusSearchStaff() {
	std::string status;
	StaffController staffController;

	std::string select;
	do {

	Select:
		system("cls");
		std::cout << "========= Staff Status Search =========" << std::endl;
		std::cout << "Select Status (1=Active, 2=Frozen, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			status = "Active";
		}
		else if (select == "2") {
			status = "Frozen";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		Staff* staffs = staffController.getStaffDetail_S_Status(status);

		if (staffs != NULL)
		{
			PrintOutStaffInfo(staffs);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "staff not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::AllStaffDetails() {

	StaffController staffController;

	Staff* staffs = staffController.getAllStaffDetails();

	if (staffs != NULL)
	{
		PrintOutStaffInfo(staffs);
	}

	else
	{
		std::cout << "staff not found" << std::endl;
	}

}

void ManagerMethod::PrintOutStaffInfo(Staff* staffs) {
	Staff* staff = staffs;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(15) << " Staff_ID "
		<< std::setw(15) << " Manager_ID "
		<< std::setw(20) << " Staff Name "
		<< std::setw(20) << " Staff Gender"
		<< std::setw(20) << " Staff HpNo "
		<< std::setw(30) << " Staff Email "
		<< std::setw(20) << " Status "
		 << std::endl;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	do
	{
		std::cout << std::setw(14) << staff->Staff_ID
			<< std::setw(14) << staff->Manager_ID
			<< std::setw(20) << staff->S_Name
			<< std::setw(20) << staff->S_Gender
			<< std::setw(20) << staff->S_HpNo
			<< std::setw(30) << staff->S_Email
			<< std::setw(21) << staff->status << std::endl;

		staff = staff->next;

	} while (staff != NULL);
}


//########################## Manager Method #############################/
void ManagerMethod::InsertManager() {
	Manager* manager = new Manager();
	std::string again;

	ManagerController managerController;

	do {
		system("cls");
		//############## Manager ID ##################

		//Auto genarate ID Algorithm (Format VXXXXXXXX) V=IDType(C=Customer,S=staff,M=Manager,SC=Sport Court), X = variable(0-9)
		Manager* getNewestManagerID = managerController.getManagerIDForInsert();

		if (getNewestManagerID != NULL) {
			std::string ID, NumAfter, d, e;	//d=covert to string after+1 , e= compose ID
			ID = getNewestManagerID->Manager_ID;

			NumAfter = ID.substr(1, 8);		//Starting position = 1, length = 8 (get num after the position)
			int b = stoi(NumAfter) + 1;		//convert String(c) to int type +1

			if (b >= 0 && b <= 9)
			{
				d = std::to_string(b);
				e = "M0000000" + d;
			}
			else if (b >= 10 && b <= 99)
			{
				d = std::to_string(b);
				e = "M000000" + d;
			}
			else if (b >= 100 && b <= 999)
			{
				d = std::to_string(b);
				e = "M00000" + d;
			}
			else if (b >= 1000 && b <= 9999)
			{
				d = std::to_string(b);
				e = "M0000" + d;
			}
			else if (b >= 10000 && b <= 99999)
			{
				d = std::to_string(b);
				e = "M000" + d;
			}
			else if (b >= 100000 && b <= 999999)
			{
				d = std::to_string(b);
				e = "M00" + d;
			}
			else if (b >= 1000000 && b <= 9999999)
			{
				d = std::to_string(b);
				e = "M0" + d;
			}
			else if (b >= 10000000 && b <= 99999999)
			{
				d = std::to_string(b);
				e = "M" + d;
			}
			manager->Manager_ID = e;
		}
		else {				//if no data in database, start at default
			manager->Manager_ID = "M00000001";
		}

		std::string input;
		//############## manager name ##################
	name:
		system("cls");
		std::cout << "M_Name: ";
		std::getline(std::cin, input);

		Manager* Duplication = managerController.getManagerDetail_S_Name(input);

		if (input == "0") {
		end:
			break;

		}
		else if (Duplication != NULL) {
			std::cout << "\nUsername registered!! \n";
			system("pause");
			goto name;
		}
		else {
			manager->M_Name = input;
		}

		//############## manager password ##################

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
			manager->password = temp2;
		}
		else
		{
			std::cout << "password not match!! please try again!\n\n";
			system("pause");
			goto password;
		}

		//############## manager Gender ##################

		std::string select;
	
	Select:
		system("cls");
		std::cout << "Select Gender (1=Male, 2=Female, 3=Other)(0 to exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			manager->M_Gender = "Male";
		}
		else if (select == "2") {
			manager->M_Gender = "Female";
		}
		else if (select == "3") {
			manager->M_Gender = "Other";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		//############## manager HpNo ##################
		do {
			system("cls");

			std::string input;
			bool valid = true;

			std::cout << "Enter a phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
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
				manager->M_HpNo = input;
				break;
			}
			else {
				std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
				system("pause");
			}
		} while (true);

		//############## manager Email ##################
		do {
			system("cls");

			std::string input;
			bool isValid = true;

			std::cout << "Enter a Email(0 to exit)[exp:FTMK@utem.com]: ";
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
				manager->M_Email = input;
				break;
			}
			else {
				std::cout << "Invalid email format\n";
				system("pause");
			}
		} while (true);

		//account status
		manager->status = "Active";

		//=================== Insert manager ===================
		int status = 0;
		std::string sure;

		system("cls");
		std::cout << "======================= Confirmation information =======================" << std::endl;
		std::cout
			<< "manager_ID: " << manager->Manager_ID << std::endl
			<< "M_Name: " << manager->M_Name << std::endl
			<< "M_Gender: " << manager->M_Gender << std::endl
			<< "M_HpNo: " << manager->M_HpNo << std::endl
			<< "M_Email: " << manager->M_Email << std::endl;
		std::cout << "==========================================================================" << std::endl;
		std::cout << "Please confirm that the information is true? (Press any Key to continue)(0 to cancel Registration) :";
		std::getline(std::cin, sure);

		if (sure != "0") {
			status = managerController.insertManager(manager);
		}

		if (status != 0)
			std::cout << "Successfully added a new manager" << std::endl;
		else
			std::cout << "Unable to add a new manager" << std::endl;

		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, again);
	} while (again != "0");
} 

void ManagerMethod::UpdateManager() {
	std::string ID_OR_loop, select;
	ManagerController managerController;

	do {
	update:
		system("cls");
		std::cout << "========= Manager Update =========" << std::endl;
		std::cout << "Please input Manager_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Manager* manager = managerController.getManagerDetail_S_ID(ID_OR_loop);

		if (manager != NULL)
		{
			do {
			update1:
				system("cls");
				std::cout << "Manager ID : " << manager->Manager_ID << std::endl;
				std::cout << "which one you want to update?" << std::endl;
				std::cout << "1.Manager Name" << std::endl;
				std::cout << "2.Manager Password" << std::endl;
				std::cout << "3.Manager Gender" << std::endl;
				std::cout << "4.Manager HpNo" << std::endl;
				std::cout << "5.Manager Email" << std::endl;
				std::cout << "6.Status" << std::endl;
				std::cout << "0.Exit" << std::endl;
				std::cout << "Select(0-6) :";
				std::getline(std::cin, select);

				if (select == "1") {
					//############## Manager name ##################
					std::string input;

					system("cls");
					std::cout << "M_Name(0 to exit): ";
					std::getline(std::cin, input);

					if (input != "0") {
						manager->M_Name = input;
					}
					else {
						goto update1;
					}
			

				}
				else if (select == "2") {
					//############## Manager password ##################
					
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
						manager->password = temp2;
					}
					else
					{
						std::cout << "password not match!! please try again!\n\n";
						system("pause");
						goto password;
					}
				}
				else if (select == "3") {
					//############## manager Gender ##################

					std::string select;
				Select:
					system("cls");
					std::cout << "Select Gender (1=Male, 2=Female, 3=Other)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						manager->M_Gender = "Male";
					}
					else if (select == "2") {
						manager->M_Gender = "Female";
					}
					else if (select == "3") {
						manager->M_Gender = "Other";
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
					//############## manager HpNo ##################
					do {
						system("cls");

						std::string input;
						bool valid = true;

						std::cout << "Enter a phone number (digits and hyphen only)(0 to exit)[exp:010-3306933]: ";
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
							manager->M_HpNo = input;
							break;
						}
						else {
							std::cout << "Invalid input. Phone number must contain only digits and hyphen, and cannot start or end with hyphen." << std::endl;
							system("pause");
						}
					} while (true);
				}
				else if (select == "5") {

					//############## manager Email ##################
					do {
						system("cls");

						std::string input;
						bool isValid = true;

						std::cout << "Enter a Email(0 to exit)[exp:FTMK@utem.com]: ";
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
							manager->M_Email = input;
							break;
						}
						else {
							std::cout << "Invalid email format\n";
							system("pause");
						}
					} while (true);
				}
				else if (select == "6") {
					//############## manager status ##################
					
					std::string select;
				SelectStatus:
					system("cls");
					std::cout << "Select status (1=Active, 2=Frozen)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						manager->status = "Active";
					}
					else if (select == "2") {
						manager->status = "Frozen";
					}
					else if (select == "0") {
						goto update1;
					}
					else {
						std::cout << "invalid input!! please try again!\n\n";
						goto SelectStatus;
					}
				}
				else if (select == "0") {
					goto update;
					break;
				}
				else {
					std::cout << "invalid input!!\n";
					system("pause");
				}

				if (select == "1" || select == "2" || select == "3" || select == "4" || select == "5" || select == "6")
				{
					int status = managerController.updateManager(manager);

					if (status != 0) {
						std::cout << "Successfully updated an existing manager" << std::endl;
					}
					else {
						std::cout << "Unable to update an existing manager" << std::endl;
					}
					system("pause");
				}

			} while (select != "0");
		}
		else if (ID_OR_loop == "0") {
			break;
		}
		else {
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Do you want to update other info? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DeleteManager() {

	ManagerController managerController;
	std::string ID_OR_loop;

	do {
		system("cls");

		std::cout << "========= manager Delete =========" << std::endl;
		std::cout << "Please input Manager_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Manager* manager = managerController.getManagerDetail_S_ID(ID_OR_loop);

		if (manager != NULL) {
			int status = managerController.deleteManager(manager);

			if (status != 0)
			{
				std::cout << "Successfully Delete or Frozen an existing manager" << std::endl;
			}
			else
			{
				std::cout << "Sorry Unable to Delete or Frozen an existing manager" << std::endl;
			}

		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::IDSearchManager() {
	std::string ID_OR_loop;
	ManagerController managerController;

	do {
		system("cls");

		std::cout << "========= Manager Search =========" << std::endl;
		std::cout << "Please input Manager_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Manager* manager = managerController.getManagerDetail_S_ID(ID_OR_loop);

		if (manager != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "manager_ID: " << manager->Manager_ID << std::endl
				<< "M_Name: " << manager->M_Name << std::endl
				<< "M_Gender: " << manager->M_Gender << std::endl
				<< "M_HpNo: " << manager->M_HpNo << std::endl
				<< "M_Email: " << manager->M_Email << std::endl
				<< "Status: " << manager->status << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::NameSearchManager() {
	std::string Name_OR_loop;
	ManagerController managerController;

	do {
		system("cls");

		std::cout << "========= Manager Search =========" << std::endl;
		std::cout << "Please input Manager's Name(0 to exit): ";
		std::getline(std::cin, Name_OR_loop);

		Manager* manager = managerController.getManagerDetail_S_Name(Name_OR_loop);

		if (manager != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "manager_ID: " << manager->Manager_ID << std::endl
				<< "M_Name: " << manager->M_Name << std::endl
				<< "M_Gender: " << manager->M_Gender << std::endl
				<< "M_HpNo: " << manager->M_HpNo << std::endl
				<< "M_Email: " << manager->M_Email << std::endl
				<< "Status: " << manager->status << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (Name_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, Name_OR_loop);
	} while (Name_OR_loop != "0");
}

void ManagerMethod::GenderSearchManager() {
	std::string M_Gender;
	ManagerController managerController;

	std::string select;
	do {

	Select:
		system("cls");
		std::cout << "========= Manager Gender Search =========" << std::endl;
		std::cout << "Select Type (1=Male, 2=Female, 3=Other, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			M_Gender = "Male";
		}
		else if (select == "2") {
			M_Gender = "Female";
		}
		else if (select == "3") {
			M_Gender = "Other";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		Manager* managers = managerController.getManagerDetail_S_Gender(M_Gender);

		if (managers != NULL)
		{
			PrintOutManagerInfo(managers);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::HpNoSearchManager() {
	std::string HpNoORLoop;
	ManagerController managerController;

	do {
	SelectType:
		system("cls");
		std::cout << "========= Manager HpNo Search =========" << std::endl;
		std::cout << "Please input Manager HpNo(0 to exit): ";
		std::getline(std::cin, HpNoORLoop);

		Manager* managers = managerController.getManagerDetail_S_HpNo(HpNoORLoop);

		if (managers != NULL)
		{
			PrintOutManagerInfo(managers);
		}
		else if (HpNoORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, HpNoORLoop);
	} while (HpNoORLoop != "0");
}

void ManagerMethod::EmailSearchManager() {
	std::string EmailORLoop;
	ManagerController managerController;

	do {
	SelectType:
		system("cls");
		std::cout << "========= Manager Email Search =========" << std::endl;
		std::cout << "Please input Manager Email(0 to exit): ";
		std::getline(std::cin, EmailORLoop);

		Manager* managers = managerController.getManagerDetail_S_Email(EmailORLoop);

		if (managers != NULL)
		{
			PrintOutManagerInfo(managers);
		}
		else if (EmailORLoop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, EmailORLoop);
	} while (EmailORLoop != "0");
}

void ManagerMethod::StatusSearchManager() {
	std::string status;
	ManagerController managerController;

	std::string select;
	do {

	Select:
		system("cls");
		std::cout << "========= Manager Status Search =========" << std::endl;
		std::cout << "Select Status (1=Active, 2=Frozen, 0=Exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			status = "Active";
		}
		else if (select == "2") {
			status = "Frozen";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		Manager* managers = managerController.getManagerDetail_S_Status(status);

		if (managers != NULL)
		{
			PrintOutManagerInfo(managers);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "manager not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::AllManagerDetails() {
	system("cls");
	ManagerController managerController;

	Manager* managers = managerController.getAllManagerDetails();

	if (managers != NULL)
	{
		PrintOutManagerInfo(managers);
	}

	else
	{
		std::cout << "Manager not found" << std::endl;
	}
	
}

void ManagerMethod::PrintOutManagerInfo(Manager* managers) {
	Manager* manager = managers;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(15) << " Manager_ID "
		<< std::setw(20) << " Manager Name "
		<< std::setw(20) << " Manager Gender"
		<< std::setw(20) << " Manager HpNo "
		<< std::setw(30) << " Manager Email "
		<< std::setw(20) << " Status " << std::endl;
	std::cout << "=====================================================================================================================================================================" << std::endl << std::endl;
	do
	{
		std::cout << std::setw(13) << manager->Manager_ID
			<< std::setw(20) << manager->M_Name
			<< std::setw(20) << manager->M_Gender
			<< std::setw(20) << manager->M_HpNo
			<< std::setw(30) << manager->M_Email
			<< std::setw(21) << manager->status << std::endl;

		manager = manager->next;

	} while (manager != NULL);
}


//########################## SportCourt Method #############################/
void ManagerMethod::InsertSportCourt() {
	SportCourt* sportCourt = new SportCourt();
	std::string again;

	SportCourtController sportCourtController;
	StaffController staffController;

	do {
		system("cls");
		//############## SportCourt ID ##################

		//Auto genarate ID Algorithm (Format VXXXXXXXX) V=IDType(C=Customer,S=staff,M=Manager,SC=Sport Court), X = variable(0-9)
		SportCourt* getNewestSportCourtID = sportCourtController.getSportCourtIDForInsert();

		if (getNewestSportCourtID != NULL) {
			std::string ID, NumAfter, d, e;	//d=covert to string after+1 , e= compose ID
			ID = getNewestSportCourtID->SportCourt_ID;

			NumAfter = ID.substr(2, 8);		//Starting position = 2, length = 8 (get num after the position)
			int b = stoi(NumAfter) + 1;		//convert String(c) to int type +1

			if (b >= 0 && b <= 9)
			{
				d = std::to_string(b);
				e = "SC0000000" + d;
			}
			else if (b >= 10 && b <= 99)
			{
				d = std::to_string(b);
				e = "SC000000" + d;
			}
			else if (b >= 100 && b <= 999)
			{
				d = std::to_string(b);
				e = "SC00000" + d;
			}
			else if (b >= 1000 && b <= 9999)
			{
				d = std::to_string(b);
				e = "SC0000" + d;
			}
			else if (b >= 10000 && b <= 99999)
			{
				d = std::to_string(b);
				e = "SC000" + d;
			}
			else if (b >= 100000 && b <= 999999)
			{
				d = std::to_string(b);
				e = "SC00" + d;
			}
			else if (b >= 1000000 && b <= 9999999)
			{
				d = std::to_string(b);
				e = "SC0" + d;
			}
			else if (b >= 10000000 && b <= 99999999)
			{
				d = std::to_string(b);
				e = "SC" + d;
			}
			sportCourt->SportCourt_ID = e;
		}
		else {				//if no data in database, start at default
			sportCourt->SportCourt_ID = "SC00000001";
		}

		//############## SportCourt name ##################
		std::string input;
		system("cls");
		std::cout << "Sport Court Name(0 to exit): ";
		std::getline(std::cin, input);

		if (input != "0") {
			sportCourt->SC_Name = input;
		}
		else {
		end:
			break;
		}

		//############## SportCourt Status ##################

		std::string select;
	SelectType:
		system("cls");
		std::cout << "Select Status (1=AVAILABLE, 2=MAINTENANCE, 3=UNAVAILABLE)(0 to exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			sportCourt->SC_Status = "AVAILABLE";
		}
		else if (select == "2") {
			sportCourt->SC_Status = "MAINTENANCE";
		}
		else if (select == "3") {
			sportCourt->SC_Status = "UNAVAILABLE";
		}
		else if (select == "0") {
			break;;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto SelectType;
		}

		//############## SportCourt PricePerDay ##################

		double PricePerDay;
	Price:
		system("cls");
		std::cout << "Price Per Day(0 to exit): ";
		std::getline(std::cin, input);

		if (input == "0") {
			break;
		}

		// to handling user invalid input (avoid string & space except '.')
		if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
			std::cerr << "invalid input!! please try again!\n\n";
			system("pause");
			goto Price;
		}
		else {
			try {
				PricePerDay = std::stod(input);
			}
			catch (const std::exception& e) {
				std::cerr << "invalid input!! please try again!\n\n";
				system("pause");
				goto Price;
			}
		}

		sportCourt->PricePerDay = PricePerDay;

		//############## SportCourt staff ID ##################
		std::string Staff_ID;
		do {
			system("cls");

			AllStaffDetails();

			std::cout << "========= Staff =========" << std::endl;
			std::cout << "Please Enter one Staff_ID(0 to exit): ";
			std::getline(std::cin, Staff_ID);

			if (Staff_ID == "0") {
				goto end;
			}

			Staff* staff = staffController.getStaffDetail_S_ID(Staff_ID);

			if (staff != NULL) {
				sportCourt->Staff_ID = staff->Staff_ID;
				break;
			}
			else
			{
				std::cout << "staff not found, please try again!" << std::endl;
				system("pause");
			}
		} while (true);

		//=================== Insert SportCourt ===================
		int status = 0;
		std::string sure;

		system("cls");
		std::cout << "======================= Confirmation information =======================" << std::endl;
		std::cout
			<< "SportCourt_ID: " << sportCourt->SportCourt_ID << std::endl
			<< "SC_Name: " << sportCourt->SC_Name << std::endl
			<< "SC_Status: " << sportCourt->SC_Status << std::endl
			<< "PricePerDay: " << sportCourt->PricePerDay << std::endl
			<< "Staff_ID: " << sportCourt->Staff_ID << std::endl;
		std::cout << "==========================================================================" << std::endl;
		std::cout << "Please confirm that the information is true? (Press any Key to continue)(0 to cancel Registration) :";
		std::getline(std::cin, sure);

		if (sure != "0") {
			status = sportCourtController.insertSportCourt(sportCourt);
		}

		if (status != 0)
			std::cout << "Successfully added a new SportCourt" << std::endl;
		else
			std::cout << "Unable to add a new SportCourt" << std::endl;

		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, again);
	} while (again != "0");
}

void ManagerMethod::UpdateSportCourt() {
	std::string ID_OR_loop, select;
	SportCourtController sportCourtController;
	StaffController staffController;

	do {
	update:
		system("cls");
		std::cout << "========= Sport Court Update =========" << std::endl;
		std::cout << "Please input Sport Court ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		SportCourt* sportCourt = sportCourtController.getSportCourtDetail_S_ID(ID_OR_loop);

		if (sportCourt != NULL)
		{
			do {
			update1:
				system("cls");
				std::cout << "SportCourt ID : " << sportCourt->SportCourt_ID << std::endl;
				std::cout << "which one you want to update?" << std::endl;
				std::cout << "1.SportCourt Name" << std::endl;
				std::cout << "2.SportCourt Status" << std::endl;
				std::cout << "3.SportCourt PricePerDay" << std::endl;	
				std::cout << "4.Staff ID" << std::endl;
				std::cout << "0.Exit" << std::endl;
				std::cout << "Select(0-4) :";
				std::getline(std::cin, select);

				if (select == "1") {
					//############## SportCourt name ##################
					std::string input;
					system("cls");
					std::cout << "Sport Court Name(0 to exit): ";
					std::getline(std::cin, input);

					if (input != "0") {
						sportCourt->SC_Name = input;
					}
					else {
						goto update1;
					}

				}
				else if (select == "2") {
					//############## SportCourt Status ##################
					std::string select;
				SelectType:
					system("cls");
					std::cout << "Select Status (1=AVAILABLE, 2=MAINTENANCE, 3=UNAVAILABLE)(0 to exit): ";
					std::getline(std::cin, select);

					if (select == "1") {
						sportCourt->SC_Status = "AVAILABLE";
					}
					else if (select == "2") {
						sportCourt->SC_Status = "MAINTENANCE";
					}
					else if (select == "3") {
						sportCourt->SC_Status = "UNAVAILABLE";
					}
					else if (select == "0") {
						goto update1;
					}
					else {
						std::cout << "invalid input!! please try again!\n\n";
						goto SelectType;
					}
				}
				else if (select == "3") {
					//############## SportCourt PricePerDay ##################
					double PricePerDay;
					std::string input;
				Price:
					system("cls");
					std::cout << "Price Per Day(0 to exit): ";
					std::getline(std::cin, input);

					if (input == "0") {
						goto update1;
					}

					// to handling user invalid input (avoid string & space except '.')
					if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
						std::cerr << "invalid input!! please try again!\n\n";
						system("pause");
						goto Price;
					}
					else {
						try {
							PricePerDay = std::stod(input);
						}
						catch (const std::exception& e) {
							std::cerr << "invalid input!! please try again!\n\n";
							system("pause");
							goto Price;
						}
					}

					sportCourt->PricePerDay = PricePerDay;
				}
				else if (select == "4") {
					//############## SportCourt staff ID ##################
					std::string Staff_ID;
					do {
						system("cls");

						AllStaffDetails();

						std::cout << "========= Staff =========" << std::endl;
						std::cout << "Please Enter one Staff_ID(0 to exit): ";
						std::getline(std::cin, Staff_ID);

						if (Staff_ID == "0") {
							goto update1;
						}

						Staff* staff = staffController.getStaffDetail_S_ID(Staff_ID);

						if (staff != NULL) {
							sportCourt->Staff_ID = staff->Staff_ID;
							break;
						}
						else
						{
							std::cout << "staff not found, please try again!" << std::endl;
							system("pause");
						}
					} while (true);
				}
				else if (select == "0") {
					goto update;
					break;
				}
				else {
					std::cout << "invalid input!!\n";
					system("pause");
				}

				if (select == "1" || select == "2" || select == "3" || select == "4")
				{
					int status = sportCourtController.updateSportCourt(sportCourt);

					if (status != 0) {
						std::cout << "Successfully updated an existing SportCourt" << std::endl;
					}
					else {
						std::cout << "Unable to update an existing SportCourt" << std::endl;
					}
					system("pause");
				}

			} while (select != "0");
		}
		else if (ID_OR_loop == "0") {
			break;
		}
		else {
			std::cout << "Sport Court not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DeleteSportCourt() {

	SportCourtController sportCourtController;
	std::string ID_OR_loop;

	do {
		system("cls");

		std::cout << "========= Sport Court Delete =========" << std::endl;
		std::cout << "Please input Sport Court ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		SportCourt* sportCourt = sportCourtController.getSportCourtDetail_S_ID(ID_OR_loop);

		if (sportCourt != NULL) {
			int status = sportCourtController.deleteSportCourt(sportCourt);

			if (status != 0)
			{
				std::cout << "Successfully Delete or Drop an existing SportCourt" << std::endl;
			}
			else
			{
				std::cout << "Unable to Delete an existing SportCourt" << std::endl;
			}

		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Sport Court not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::IDSearchSportCourt() {
	std::string ID_OR_loop;
	SportCourtController sportCourtController;

	do {
		system("cls");

		std::cout << "========= Sport Court Search =========" << std::endl;
		std::cout << "Please input Sport Court ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		SportCourt* sportCourt = sportCourtController.getSportCourtDetail_S_ID(ID_OR_loop);

		if (sportCourt != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "Sport Court ID: " << sportCourt->SportCourt_ID << std::endl
				<< "Sport Court Name: " << sportCourt->SC_Name << std::endl
				<< "Sport Court Status: " << sportCourt->SC_Status << std::endl
				<< "Price Per Day: " << sportCourt->PricePerDay << std::endl
				<< "Staff ID: " << sportCourt->Staff_ID << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Sport Court not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::NameSearchSportCourt() {
	std::string Name_OR_loop;
	SportCourtController SportCourtController;

	do {
		system("cls");

		std::cout << "========= Sport Court Search  =========" << std::endl;
		std::cout << "Please input SportCourt's Name(0 to exit): ";
		std::getline(std::cin, Name_OR_loop);

		SportCourt* sportCourt = SportCourtController.getSportCourtDetail_S_Name(Name_OR_loop);

		if (sportCourt != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "SportCourt_ID: " << sportCourt->SportCourt_ID << std::endl
				<< "Sport Court Name: " << sportCourt->SC_Name << std::endl
				<< "Sport Court Status: " << sportCourt->SC_Status << std::endl
				<< "Price Per Day: " << sportCourt->PricePerDay << std::endl
				<< "Staff_ID: " << sportCourt->Staff_ID << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (Name_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Sport Court not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, Name_OR_loop);
	} while (Name_OR_loop != "0");
}

void ManagerMethod::StatusSearchSportCourt() {
	std::string SC_Status;
	SportCourtController SportCourtController;

	std::string select;
	do {

	Select:
		system("cls");
		std::cout << "========= Sport Court Search =========" << std::endl;
		std::cout << "Select Status (1=AVAILABLE, 2=MAINTENANCE, 3=UNAVAILABLE)(0 to exit): ";
		std::getline(std::cin, select);

		if (select == "1") {
			SC_Status = "AVAILABLE";
		}
		else if (select == "2") {
			SC_Status = "MAINTENANCE";
		}
		else if (select == "3") {
			SC_Status = "UNAVAILABLE";
		}
		else if (select == "0") {
			break;
		}
		else {
			std::cout << "invalid input!! please try again!\n\n";
			system("pause");
			goto Select;
		}

		SportCourt* sportCourts = SportCourtController.getSportCourtDetail_S_Status(SC_Status);

		if (sportCourts != NULL)
		{
			PrintOutSportCourtInfo(sportCourts);
		}
		else if (select == "0")
		{
			break;
		}
		else
		{
			std::cout << "SportCourt not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, select);
	} while (select != "0");
}

void ManagerMethod::PriceSearchSportCourt() {
	std::string input;
	double PricePerDay;
	SportCourtController sportCourtController;

	do {
	Price:
		system("cls");
		std::cout << "========= SportCourt PricePerDay Search =========" << std::endl;
		std::cout << "Please input SportCourt PricePerDay(0 to exit): ";
		std::getline(std::cin, input);

		// to handling user invalid input (avoid string & space except '.')
		if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
			std::cerr << "invalid input!! please try again!\n\n";
			system("pause");
			goto Price;
		}
		else {
			try {
				PricePerDay = std::stod(input);
			}
			catch (const std::exception& e) {
				std::cerr << "invalid input!! please try again!\n\n";
				system("pause");
				goto Price;
			}
		}

		SportCourt* sportCourts = sportCourtController.getSportCourtDetail_S_PricePerDay(PricePerDay);

		if (sportCourts != NULL)
		{
			PrintOutSportCourtInfo(sportCourts);
		}
		else if (input == "0")
		{
			break;
		}
		else
		{
			std::cout << "SportCourt not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

void ManagerMethod::AllSportCourtDetails() {
	system("cls");
	SportCourtController sportCourtController;

	SportCourt* sportCourts = sportCourtController.getAllSportCourtDetails();

	if (sportCourts != NULL)
	{
		PrintOutSportCourtInfo(sportCourts);
	}

	else
	{
		std::cout << "Sport Court not found" << std::endl;
	}

}

void ManagerMethod::PrintOutSportCourtInfo(SportCourt* sportCourts) {
	SportCourt* sportCourt = sportCourts;
	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(15) << " SportCourt_ID "
		<< std::setw(30) << " SportCourt Name "
		<< std::setw(30) << " SportCourt Status"
		<< std::setw(30) << " PricePerDay "
		<< std::setw(30) << " Staff ID " << std::endl; 
	std::cout << "=====================================================================================================================================================================" << std::endl << std::endl;
	do
	{
		std::cout << std::setw(14) << sportCourt->SportCourt_ID
			<< std::setw(30) << sportCourt->SC_Name
			<< std::setw(30) << sportCourt->SC_Status
			<< std::setw(30) << sportCourt->PricePerDay 
			<< std::setw(30) << sportCourt->Staff_ID << std::endl;

		sportCourt = sportCourt->next;

	} while (sportCourt != NULL);
}

//########################## Booking Method #############################
void ManagerMethod::InsertCourtBooking() {
	CustomerMethod customerMethod;
	std::string ID_OR_loop;
	CustomerController customerController;

	do {
		system("cls");

		std::cout << "========= Customer Booking =========" << std::endl;
		std::cout << "Please input Customers_ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		Customer* customer = customerController.getCustomerDetail_S_ID(ID_OR_loop);

		if (customer != NULL)
		{
			customerMethod.MakeBooking(customer);	//reuse customer booking
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Customers not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::UpdateCourtBooking() {
	std::string ID_OR_loop, StaffID;
	CourtBookingController courtBookingController;
	StaffController staffController;

	do {
	update:
		system("cls");
		std::cout << "========= CourtBooking Update =========" << std::endl;
		std::cout << "Please input CourtBooking_ID to update staff ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_BookingID(ID_OR_loop);

		if (courtBooking != NULL)
		{
			do {
				system("cls");
				std::cout << "=============== Booking information =================" << std::endl;
				std::cout << "\n=====================================================" << std::endl;
				std::cout
					<< "Court Booking_ID: " << courtBooking->CourtBooking_ID << std::endl
					<< "Customer_ID: " << courtBooking->Customers_ID << std::endl
					<< "Customer Name: " << courtBooking->C_Name << std::endl
					<< "Sport Court_ID: " << courtBooking->SportCourt_ID << std::endl
					<< "Sport Court Name: " << courtBooking->SC_Name << std::endl
					<< "Staff_ID: " << courtBooking->Staff_ID << std::endl
					<< "Staff Name: " << courtBooking->S_Name << std::endl
					<< "Date IN: " << courtBooking->DateIN << std::endl
					<< "Date OUT: " << courtBooking->DateOUT << std::endl
					<< "Total Day: " << courtBooking->TotalDay << std::endl
					<< "Total Charge: " << courtBooking->TotalCharge << std::endl
					<< "Payment Type: " << courtBooking->PaymentType << std::endl;
				std::cout << "=====================================================" << std::endl << std::endl;

				AllStaffDetails();

				std::cout << std::endl;
				std::cout << "Select Staff ID (0 to exit):";
				std::getline(std::cin, StaffID);

				Staff* staff = staffController.getStaffDetail_S_ID(StaffID);

				if (staff !=NULL)
				{
					courtBooking->Staff_ID = staff->Staff_ID;
					int status = courtBookingController.updateCourtBooking(courtBooking);

					if (status != 0) {
						std::cout << "Successfully updated" << std::endl;
					}
					else {
						std::cout << "Unable to update" << std::endl;
					}
					break;
				}
				else if (StaffID == "0") {
					goto update;
					break;
				}
				else {
					std::cout << "Staff not found" << std::endl;
					system("pause");
				}

			} while (StaffID != "0");

		}
		else if (ID_OR_loop == "0") {
			break;
		}
		else {
			std::cout << "CourtBooking not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DeleteCourtBooking() {
	CourtBookingController courtBookingController;
	std::string ID_OR_loop;

	do {
		system("cls");

		std::cout << "========= Court Booking Delete =========" << std::endl;
		std::cout << "Please input Court Booking ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_BookingID(ID_OR_loop);

		if (courtBooking != NULL) {
			int status = courtBookingController.deleteCourtBooking(courtBooking);

			if (status != 0)
			{
				std::cout << "Successfully Delete an existing Court Booking" << std::endl;
			}
			else
			{
				std::cout << "Unable to Delete an existing Court Booking" << std::endl;
			}

		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::BookingIDSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Detials by Court Booking ID =========" << std::endl;
		std::cout << "Please input Court Booking ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_BookingID(ID_OR_loop);

		if (courtBooking != NULL)
		{
			std::cout << "\n=================================================" << std::endl;
			std::cout
				<< "Court Booking_ID: " << courtBooking->CourtBooking_ID << std::endl
				<< "Customer_ID: " << courtBooking->Customers_ID << std::endl
				<< "Customer Name: " << courtBooking->C_Name << std::endl
				<< "Sport Court_ID: " << courtBooking->SportCourt_ID << std::endl
				<< "Sport Court Name: " << courtBooking->SC_Name << std::endl
				<< "Staff_ID: " << courtBooking->Staff_ID << std::endl
				<< "Staff Name: " << courtBooking->S_Name << std::endl
				<< "Date IN: " << courtBooking->DateIN << std::endl
				<< "Date OUT: " << courtBooking->DateOUT << std::endl
				<< "Total Day: " << courtBooking->TotalDay << std::endl
				<< "Total Charge: " << courtBooking->TotalCharge << std::endl
				<< "Payment Type: " << courtBooking->PaymentType << std::endl;
			std::cout << "=================================================" << std::endl;
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not found" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::CustomerIDSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Details by Customer ID =========" << std::endl;
		std::cout << "Please input Customer ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_CustomerID(ID_OR_loop);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::SportCourtIDSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Details by Sport Court ID =========" << std::endl;
		std::cout << "Please input Sport Court ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_SportCourtID(ID_OR_loop);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::StaffIDSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Details by Staff ID =========" << std::endl;
		std::cout << "Please input Staff ID(0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_StaffID(ID_OR_loop);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DateINSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Details by DateIN =========" << std::endl;
		std::cout << "Please input DateIN [YYYY/MM/DD] (0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_DateIN(ID_OR_loop);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::DateOUTSearchCourtBooking() {
	std::string ID_OR_loop;
	CourtBookingController courtBookingController;

	do {
		system("cls");

		std::cout << "========= Search Booking Details by DateOUT =========" << std::endl;
		std::cout << "Please input DateOUT [YYYY/MM/DD] (0 to exit): ";
		std::getline(std::cin, ID_OR_loop);

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_DateOUT(ID_OR_loop);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (ID_OR_loop == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, ID_OR_loop);
	} while (ID_OR_loop != "0");
}

void ManagerMethod::YearSearchCourtBooking() {
	std::string input;
	int Year;
	CourtBookingController courtBookingController;

	do {
	input:
		system("cls");

		std::cout << "========= Search Booking Details by Year =========" << std::endl;
		std::cout << "Please input Year(0 to exit): ";
		std::getline(std::cin, input);

		// to handling user invalid input (avoid string & space)
		if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
			std::cerr << "invalid input!! please try again!\n\n";
			system("pause");
			goto input;
		}
		else {
			try {
				Year = std::stod(input);
			}
			catch (const std::exception& e) {
				std::cerr << "invalid input!! please try again!\n\n";
				system("pause");
				goto input;
			}
		}
		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_Year(Year);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else if (input == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

void ManagerMethod::TotalDaySearchCourtBooking() {
	std::string input;
	int Day;
	CourtBookingController courtBookingController;

	do {
	input:
		system("cls");

		std::cout << "========= Search Booking Details by Total Day =========" << std::endl;
		std::cout << "Please input Total Day(0 to exit): ";
		std::getline(std::cin, input);

		if (input == "0")
		{
			break;
		}

		// to handling user invalid input (avoid string & space)
		if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
			std::cerr << "invalid input!! please try again!\n\n";
			system("pause");
			goto input;
		}
		else {
			try {
				Day = std::stod(input);
			}
			catch (const std::exception& e) {
				std::cerr << "invalid input!! please try again!\n\n";
				system("pause");
				goto input;
			}
		}
		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_TotalDay(Day);

		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

void ManagerMethod::TotalChargeSearchCourtBooking() {
	std::string input;
	double Price;
	CourtBookingController courtBookingController;


	do {
	Price:
		system("cls");

		std::cout << "========= Search Booking Details by Total Charge =========" << std::endl;
		std::cout << "Please input Total Charge (range +100|-100)(0 to exit): ";
		std::getline(std::cin, input);

		if (input == "0")
		{
			break;
		}

		// to handling user invalid input (avoid string & space except '.')
		if (std::count(input.begin(), input.end(), '.') > 1 || !std::all_of(input.begin(), input.end(), ::isdigit) && input.find_first_not_of("-0123456789.") != std::string::npos) {
			std::cerr << "invalid input!! please try again!\n\n";
			system("pause");
			goto Price;
		}
		else {
			try {
				Price = std::stod(input);
			}
			catch (const std::exception& e) {
				std::cerr << "invalid input!! please try again!\n\n";
				system("pause");
				goto Price;
			}
		}

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_TotalCharge(Price); //bug
	
		if (courtBooking != NULL)
		{
			PrintOutBookingInfo(courtBooking);
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

void ManagerMethod::PaymentTypeSearchCourtBooking() {
	std::string Input;
	CourtBookingController courtBookingController;

	do {
	SelectType:
		system("cls");

		std::cout << "========= Search Booking Details by Payment Type =========" << std::endl;
		std::cout << "1.Online Banking\n";
		std::cout << "2.Touch and Go (TNG eWallet)\n";
		std::cout << "3.Credit/Debit Card (Visa)\n";
		std::cout << "4.Cash\n";
		std::cout << "0.Exit\n";
		std::cout << "Please select Payment Type 1-4 (0 to exit): ";
		std::getline(std::cin, Input);

		if (Input == "1") {
			Input = "Online Banking";
		}
		else if (Input == "2") {
			Input = "Touch and Go";
		}
		else if (Input == "3") {
			Input = "Credit/Debit Card";
		}
		else if (Input == "4") {
			Input = "Cash";
		}
		else if (Input == "0") {
			break;
		}
		else {
			std::cout << "\ninvalid input!! please try again!\n";
			system("pause");
			goto SelectType;
		}

		CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_PaymentType(Input);

		if (courtBooking != NULL)
		{
			system("cls");
			PrintOutBookingInfo(courtBooking);
		}
		else if (Input == "0")
		{
			break;
		}
		else
		{
			std::cout << "Court Booking not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, Input);
	} while (Input != "0");
}

void ManagerMethod::AllCourtBookingDetails() {
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBooking = courtBookingController.getAllCourtBookingDetails();

	if (courtBooking != NULL)
	{
		PrintOutBookingInfo(courtBooking);
	}

	else
	{
		std::cout << "Not record" << std::endl;
	}
}

void ManagerMethod::AllUpComingCourtBookingDetails() {
	system("cls");
	CourtBookingController courtBookingController;

	CourtBooking* courtBooking = courtBookingController.getCourtBookingDetail_S_UpComing();

	if (courtBooking != NULL)
	{
		PrintOutBookingInfo(courtBooking);
	}

	else
	{
		std::cout << "Not record" << std::endl;
	}
}

void ManagerMethod::PrintOutBookingInfo(CourtBooking* courtBookings) {

	CourtBooking* courtBooking = courtBookings;

	std::cout << "=====================================================================================================================================================================" << std::endl;
	std::cout << std::setw(16) << " Court Booking_ID "
		<< std::setw(14) << " Customer_ID "
		<< std::setw(16) << " Sport Court_ID "
		<< std::setw(19) << " Sport Court    "
		<< std::setw(14) << " Staff_ID "
		<< std::setw(14) << " Date IN "
		<< std::setw(16) << " Date OUT "
		<< std::setw(16) << " Total Day "
		<< std::setw(17) << " Total Charge "
		<< std::setw(20) << " Payment Type " << std::endl;
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

void ManagerMethod::CalendarView(int year, int month, CourtBooking* courtBooking) {

	CourtBookingController CourtBookingCTRL;
	CourtBooking* CBDateCheck = new CourtBooking();

	std::string date ;	//format(YYYY/MM/DD)

	// Calculate the number of days in the month
	int days;
	if (month == 2) {//For this reason, not every four years is a leap year. The rule is that if the year is divisible by 100 and not divisible by 400, leap year is skipped
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			days = 29;
		}
		else {
			days = 28;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		days = 30;
	}
	else {	//month = 1,3,5,7,8,10,12
		days = 31;
	}

	// Determine the day of the week for the first day of the month
	int y = year;
	int m = month;
	if (m < 3) {
		y--;
		m += 12;
	}
	int c = y / 100;
	y %= 100;
	int w = (13 * (m + 1)) / 5;
	int x = y / 4;
	int z = c / 4;
	int dow = (w + y + x + z + 5 * c) % 7;

	// Print the calendar
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "\n\n\t\t\t\t\t\t\t          Red = Booked";
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "     White = Available\n";

	std::cout << "\n\n\t\t\t\t\t\t\t\t      Sun Mon Tue Wed Thu Fri Sat" << std::endl;
	for (int i = 0; i < dow; i++) {
		std::cout << "    ";
	}
	int booked;		//1=booked
	std::cout << "                                                                      ";
	for (int day = 1; day <= days; day++) {
		booked = 0;
		//to avoid YYYY-M-D
		if ((day >= 1 && day <= 9)&&(month >= 1 && month <= 9)) {
			date = std::to_string(year) + "-0" + std::to_string(month) + "-0" + std::to_string(day);	//set day format(YYYY-MM-DD) avoid YYYY-M-D
		}
		else if (month >= 1 && month <= 9) {
			date = std::to_string(year) + "-0" + std::to_string(month) + "-" + std::to_string(day);		//set day format(YYYY-MM-DD) avoid YYYY-M-DD
		}
		else if(day >= 1 && day <= 9) {
			date = std::to_string(year) + "-" + std::to_string(month) + "-0" + std::to_string(day);		//set day format(YYYY-MM-DD) avoid YYYY-MM-D
		}
		else {
			date = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);		//set day format(YYYY-MM-DD)

		}

		CBDateCheck = CourtBookingCTRL.getCourtBookingDetail_S_SportCourtID(courtBooking->SportCourt_ID);
		while (CBDateCheck != NULL) 
		{
			if (date >= CBDateCheck->DateIN && date <= CBDateCheck->DateOUT) {//booked formula: dateIN<=current date<=DateOUT
				booked +=1;
				break;
			}


			CBDateCheck = CBDateCheck->next;
		}

		if (booked!=0) 
		{		//booked
			SetConsoleTextAttribute(hConsole, 12);			//RED
			std::cout << std::setw(3) << day << " ";		//day print
			if ((dow + day) % 7 == 0) {
				std::cout << std::endl;
				std::cout << "\t\t\t\t\t\t\t\t      ";
			}
		}
		else 
		{
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << std::setw(3) << day << " ";		//day print
			if ((dow + day) % 7 == 0) {
				std::cout << std::endl;
				std::cout << "\t\t\t\t\t\t\t\t      ";
			}
		}
	
	}
	if ((dow + days) % 7 != 0) {
		std::cout << std::endl;

	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "\n";
}

//########################## Report Method #############################
void ManagerMethod::AnnualIncome() {
	std::string input;
	int Year;
	CourtBookingController courtBookingController;

	do {
	inputYear:
		system("cls");

		std::cout << "========= Annual Income Report =========" << std::endl;
		std::cout << "Please input Year(0 to exit)[exp:2023]: ";
		std::getline(std::cin, input);

		// to handling user invalid input (avoid string & space)
		try {
			Year = std::stoi(input);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
			system("pause");
			goto inputYear;
		}

		CourtBooking* courtBooking = courtBookingController.AnnualIncome(Year);

		if (courtBooking != NULL)
		{
			CourtBooking* CB = courtBooking;
			const int num = 100;
			float AnnualIncome = 0;
			float occupy[num] = { 0 };

			system("cls");
			//table
			std::cout << "===================================<<<< " << input << " Year Annual Report >>>>=================================== \n\n" << std::endl;
			std::cout << "========================================================================================================" << std::endl;
			std::cout << "NO       CourtBooking_ID\t   Sport Court Name\t\t  Frequency\t      Profit(RM)" << std::endl;
			std::cout << "========================================================================================================" << std::endl;
			
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			for (int i = 1; CB != NULL; i++)
			{
				SetConsoleTextAttribute(hConsole, i+1);
				

				std::cout << i << std::setw(23) << CB->SportCourt_ID
					<< std::setw(27) << CB->SC_Name
					<< std::setw(20) << CB->frequency
					<< std::fixed << std::setprecision(2) << std::setw(25) << CB->TotalCharge
					<< std::endl;
				AnnualIncome += CB->TotalCharge;
				CB = CB->next;
			}
			SetConsoleTextAttribute(hConsole, 15);

			std::cout << "\n";
			std::cout << "=======================================================================================================" << std::endl;
			std::cout << "\t\t\t\t\t\t\t\t  Total Profit:     RM" << std::setw(10) << AnnualIncome << std::endl;
			std::cout << "=======================================================================================================" << std::endl;

			//===========================  bar graph ===================================

			int graph_width = 125;
			float max_value = AnnualIncome;        //year income

			std::cout << "\n\n\n==================================<<<< " << input << " Year Annual Report  (Bar Graph) >>>>================================== \n" << std::endl;

			std::cout << std::fixed << std::setprecision(2);
			std::cout << "     SPORT COURT     |       PROFIT" << std::endl;
			std::cout << "------------------------------------------"<< std::endl;
			CourtBooking* CB1 = courtBooking;
			for (int i = 0; CB1 != NULL; i++)
			{

				SetConsoleTextAttribute(hConsole, i+2);
				


				occupy[i] = CB1->TotalCharge / AnnualIncome * 100;			//find the occupy for each 

				std::cout << std::setw(20) << CB1->SC_Name << " | ";

				int bar_width = static_cast<int>(CB1->TotalCharge / max_value * graph_width);

				for (int j = 0; j < bar_width; ++j)
				{
					std::cout << "#";
				}

				std::cout << " RM " << CB1->TotalCharge << " : " << occupy[i] << "%" << std::endl;
				CB1 = CB1->next;
			}
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "\n===================================================================================================================" << std::endl;

			//============== file =========================
			std::string file;
			std::cout << "\nDo you want to export file? (0 to cancel):";
			std::getline(std::cin, file);

			if (file != "0") {
				//export file
				std::ofstream outfile;
				outfile.open("Annual Income " + input + ".txt");

				if (outfile.is_open()) {
					if (courtBooking != NULL)
					{
						CourtBooking* CB = courtBooking;
						const int num = 100;
						float AnnualIncome = 0;
						float occupy[num] = { 0 };

						//table
						outfile << "===================================<<<< " << input << " Year Annual Report >>>>=================================== \n\n" << std::endl;
						outfile << "========================================================================================================" << std::endl;
						outfile << "NO       CourtBooking_ID\t   Sport Court Name\t\t  Frequency\t      Profit(RM)" << std::endl;
						outfile << "========================================================================================================" << std::endl;

						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

						for (int i = 1; CB != NULL; i++)
						{
							SetConsoleTextAttribute(hConsole, i + 1);


							outfile << i << std::setw(23) << CB->SportCourt_ID
								<< std::setw(27) << CB->SC_Name
								<< std::setw(20) << CB->frequency
								<< std::fixed << std::setprecision(2) << std::setw(25) << CB->TotalCharge
								<< std::endl;
							AnnualIncome += CB->TotalCharge;
							CB = CB->next;
						}
						SetConsoleTextAttribute(hConsole, 15);

						outfile << "\n";
						outfile << "=======================================================================================================" << std::endl;
						outfile << "\t\t\t\t\t\t\t\t  Total Profit:     RM" << std::setw(10) << AnnualIncome << std::endl;
						outfile << "=======================================================================================================" << std::endl;

						//===========================  bar graph ===================================

						int graph_width = 125;
						float max_value = AnnualIncome;        //year income

						outfile << "\n\n\n==================================<<<< " << input << " Year Annual Report  (Bar Graph) >>>>================================== \n" << std::endl;

						outfile << std::fixed << std::setprecision(2);
						outfile << "     SPORT COURT     |       PROFIT" << std::endl;
						outfile << "------------------------------------------" << std::endl;
						CourtBooking* CB1 = courtBooking;
						for (int i = 0; CB1 != NULL; i++)
						{

							SetConsoleTextAttribute(hConsole, i + 2);



							occupy[i] = CB1->TotalCharge / AnnualIncome * 100;			//find the occupy for each 

							outfile << std::setw(20) << CB1->SC_Name << " | ";

							int bar_width = static_cast<int>(CB1->TotalCharge / max_value * graph_width);

							for (int j = 0; j < bar_width; ++j)
							{
								outfile << "#";
							}

							outfile << " RM " << CB1->TotalCharge << " : " << occupy[i] << "%" << std::endl;
							CB1 = CB1->next;
						}
						SetConsoleTextAttribute(hConsole, 15);
						outfile << "\n===================================================================================================================" << std::endl;

						outfile.close();
						std::cout << "Successfully export Annual Income " + input + ".txt" << std::endl;
					}
				}
				else {
					std::cout << "Unable export." << std::endl;
				}
			}

		}
		else if (input == "0")		//exit
		{
			break;
		}
		else
		{
			std::cout << "Not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

void ManagerMethod::MonthlyIncome() {
	std::string input1, input2;
	int Year, month;
	CourtBookingController courtBookingController;

	do {
	inputYear:
		system("cls");

		std::cout << "========= Monthly Income Report =========" << std::endl;
		std::cout << "Please input Year(0 to exit)[exp:2023]: ";
		std::getline(std::cin, input1);

		// to handling user invalid input (avoid string & space)
		try {
			Year = std::stoi(input1);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
			system("pause");
			goto inputYear;
		}

		if (input1 == "0")
			break;

		std::cout << "Please input Month[exp:5]: ";
		std::getline(std::cin, input2);

		// to handling user invalid input (avoid string & space)
		try {
			month = std::stoi(input2);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
			system("pause");
			goto inputYear;
		}


		CourtBooking* courtBooking = courtBookingController.MonthlyIncome(Year, month);

		if (courtBooking != NULL)
		{
			CourtBooking* CB = courtBooking;
			const int num = 100;
			float Total = 0;
			float occupy[num] = { 0 };

			system("cls");
			//table
			std::cout << "========================================<<<< [ " << input1 << "  Year  " << month << "  Month " << "] >>>>========================================\n";
			std::cout << "=============================================<<<< Monthly  Report >>>>=============================================\n" << std::endl;
			std::cout << "===================================================================================================================" << std::endl;
			std::cout << "NO       CourtBooking_ID\t   Sport Court Name\t\t  Frequency\t      Profit(RM)" << std::endl;
			std::cout << "===================================================================================================================" << std::endl;
			
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			for (int i = 1; CB != NULL; i++)
			{
				SetConsoleTextAttribute(hConsole, i+1);
				std::cout << i << std::setw(23) << CB->SportCourt_ID
					<< std::setw(27) << CB->SC_Name
					<< std::setw(20) << CB->frequency
					<< std::fixed << std::setprecision(2) << std::setw(25) << CB->TotalCharge
					<< std::endl;
				Total += CB->TotalCharge;
				CB = CB->next;
			}
			std::cout << "\n";
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "===================================================================================================================" << std::endl;
			std::cout << "\t\t\t\t\t\t\t\t  Total Profit:     RM" << std::setw(10) << Total << std::endl;
			std::cout << "===================================================================================================================" << std::endl;

			//===========================  bar graph ===================================

			int graph_width = 125;
			float max_value = Total;        //year income

			std::cout << "\n\n";
			std::cout << "========================================<<<< [ " << input1 << "  Year  " << month << "  Month " << "] >>>>========================================\n";
			std::cout << "========================================<<<< Monthly Report(Bar Graph) >>>>========================================\n" << std::endl;

			std::cout << std::fixed << std::setprecision(2);

			std::cout << "     SPORT COURT     |       PROFIT" << std::endl;
			std::cout << "------------------------------------------" << std::endl;

			CourtBooking* CB1 = courtBooking;
			for (int i = 0; CB1 != NULL; i++)
			{
				SetConsoleTextAttribute(hConsole, i+2);
				occupy[i] = CB1->TotalCharge / Total * 100;			//find the occupy for each 

				std::cout << std::setw(20) << CB1->SC_Name << " | ";

				int bar_width = static_cast<int>(CB1->TotalCharge / max_value * graph_width);

				for (int j = 0; j < bar_width; ++j)
				{
					std::cout << "#";
				}

				std::cout << " RM " << CB1->TotalCharge << " : " << occupy[i] << "%" << std::endl;
				CB1 = CB1->next;
				SetConsoleTextAttribute(hConsole, 15);
			}
			std::cout << "\n===================================================================================================================" << std::endl;

			//============== file =========================
			std::string file;
			std::cout << "\nDo you want to export file? (0 to cancel):";
			std::getline(std::cin, file);

			if (file != "0") {
				//export file
				std::ofstream outfile;
				outfile.open("Monthly Income " + input1 + "" + input2 + ".txt");

				if (outfile.is_open()) {
					if (courtBooking != NULL)
					{
						CourtBooking* CB = courtBooking;
						const int num = 100;
						float Total = 0;
						float occupy[num] = { 0 };

						//table
						outfile << "========================================<<<< [ " << input1 << "  Year  " << month << "  Month " << "] >>>>========================================\n";
						outfile << "=============================================<<<< Monthly  Report >>>>=============================================\n" << std::endl;
						outfile << "===================================================================================================================" << std::endl;
						outfile << "NO       CourtBooking_ID\t   Sport Court Name\t\t  Frequency\t      Profit(RM)" << std::endl;
						outfile << "===================================================================================================================" << std::endl;

						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

						for (int i = 1; CB != NULL; i++)
						{
							SetConsoleTextAttribute(hConsole, i + 1);
							outfile << i << std::setw(23) << CB->SportCourt_ID
								<< std::setw(27) << CB->SC_Name
								<< std::setw(20) << CB->frequency
								<< std::fixed << std::setprecision(2) << std::setw(25) << CB->TotalCharge
								<< std::endl;
							Total += CB->TotalCharge;
							CB = CB->next;
						}
						outfile << "\n";
						SetConsoleTextAttribute(hConsole, 15);
						outfile << "===================================================================================================================" << std::endl;
						outfile << "\t\t\t\t\t\t\t\t  Total Profit:     RM" << std::setw(10) << Total << std::endl;
						outfile << "===================================================================================================================" << std::endl;

						//===========================  bar graph ===================================

						int graph_width = 125;
						float max_value = Total;        //year income

						outfile << "\n\n";
						outfile << "========================================<<<< [ " << input1 << "  Year  " << month << "  Month " << "] >>>>========================================\n";
						outfile << "========================================<<<< Monthly Report(Bar Graph) >>>>========================================\n" << std::endl;

						outfile << std::fixed << std::setprecision(2);

						outfile << "     SPORT COURT     |       PROFIT" << std::endl;
						outfile << "------------------------------------------" << std::endl;

						CourtBooking* CB1 = courtBooking;
						for (int i = 0; CB1 != NULL; i++)
						{
							SetConsoleTextAttribute(hConsole, i + 2);
							occupy[i] = CB1->TotalCharge / Total * 100;			//find the occupy for each 

							outfile << std::setw(20) << CB1->SC_Name << " | ";

							int bar_width = static_cast<int>(CB1->TotalCharge / max_value * graph_width);

							for (int j = 0; j < bar_width; ++j)
							{
								outfile << "#";
							}

							outfile << " RM " << CB1->TotalCharge << " : " << occupy[i] << "%" << std::endl;
							CB1 = CB1->next;
							SetConsoleTextAttribute(hConsole, 15);
						}
						outfile << "\n===================================================================================================================" << std::endl;

						outfile.close();
						std::cout << "Successfully export Monthly Income " + input1 + "" + input2 + ".txt" << std::endl;
					}
				}
				else {
					std::cout << "Unable export." << std::endl;
				}
			}

		}
		else if (input1 == "0")		//exit
		{
			break;
		}
		else
		{
			std::cout << "Not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input1);
	} while (input1 != "0");
}

void ManagerMethod::HighDemandSportCourt() {
	CourtBookingController courtBookingController;
	CourtBooking* courtBooking = courtBookingController.HighDemandSportCourt();

	if (courtBooking != NULL)
	{
		CourtBooking* CB = courtBooking;
		const int num = 100;
		float TotalF = 0;
		float occupy[num] = { 0 };

		system("cls");
		//table
		std::cout << "===================================<<<< Highest Demand Sport Court Report >>>>=================================== \n\n" << std::endl;
		std::cout << "=================================================================================================================" << std::endl;
		std::cout << "NO       CourtBooking_ID\t   Sport Court Name\t\t  Frequency\t      Profit(RM)" << std::endl;
		std::cout << "=================================================================================================================" << std::endl;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 1; CB != NULL; i++)
		{
			SetConsoleTextAttribute(hConsole, i+1);
			std::cout << i << std::setw(23) << CB->SportCourt_ID
				<< std::setw(27) << CB->SC_Name
				<< std::setw(20) << CB->frequency
				<< std::fixed << std::setprecision(2) << std::setw(25) << CB->TotalCharge
				<< std::endl;
			TotalF += CB->frequency;
			CB = CB->next;
		}
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "\n";
		std::cout << "================================================================================================================" << std::endl;

		//===========================  bar graph ===================================

		int graph_width = 150;
		float max_value = TotalF;        

		std::cout << "\n\n\n";
		std::cout << "===================================<<<< Highest Demand Sport Court Report >>>>=================================== \n" << std::endl;

		std::cout << std::fixed << std::setprecision(2);
		std::cout << "     SPORT COURT     |       FREQUENCY" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		CourtBooking* CB1 = courtBooking;
		for (int i = 0; CB1 != NULL; i++)
		{
			SetConsoleTextAttribute(hConsole, i+2);
			occupy[i] = CB1->frequency/ TotalF * 100;			//find the occupy for each 

			std::cout << std::setw(20) << CB1->SC_Name << " | ";

			int bar_width = static_cast<int>(CB1->frequency / max_value * graph_width);

			for (int j = 0; j < bar_width; ++j)
			{
				std::cout << "#";
			}

			std::cout << " Time " << CB1->frequency << " : " << occupy[i] << "%" << std::endl;
			CB1 = CB1->next;
		}
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "\n==================================================================================================================" << std::endl;
		system("pause");
	}
	else
	{
		std::cout << "Not record" << std::endl;
		system("pause");
	}
}

void ManagerMethod::SummaryReport() {

	std::string input;
	int Year;
	CourtBookingController courtBookingController;

	do {
	inputYear:
		system("cls");

		std::cout << "========= Year Summary Report =========" << std::endl;
		std::cout << "Please input Year(0 to exit)[exp:2023]: ";
		std::getline(std::cin, input);

		// to handling user invalid input (avoid string & space)
		try {
			Year = std::stoi(input);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
			system("pause");
			goto inputYear;
		}
		CourtBooking* courtBooking = courtBookingController.SummaryReport(Year);

		if (courtBooking != NULL)
		{
			CourtBooking* CB = courtBooking;
			const int num_months = 12;
			float AnnualIncome = 0;
			float occupy[12] = { 0 };
			float MonthlyIncome[num_months]={0};	//initial 0 ,to store monthly income

			std::string labels[num_months] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",		//Y-axis
								   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
			std::cout << std::fixed << std::setprecision(2);
			while (CB != NULL) {			//find the annual income, store value to monthly income

				for (int i = 1; i <= 12; i++) {
					if (CB->Month == i) {
						MonthlyIncome[i-1] = CB->MonthlyIncome;
					}
				}
				AnnualIncome += CB->MonthlyIncome;
				CB = CB->next;
			}

			system("cls");
			//table
			std::cout << "======================<<<< " << input << " Year Summary Report >>>>===================== \n" << std::endl;
			std::cout << "                          MONTH           PROFIT(RM)\n";
			std::cout << "-----------------------------------------------------------------------------\n";
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			for (int i = 0; i < num_months; ++i)
			{
				SetConsoleTextAttribute(hConsole, i+2);
				std::cout << std::setw(30) << labels[i]<<":\t\t " << std::setw(10) << MonthlyIncome[i] << std::endl;
			}
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "\n";
			std::cout << "==============================================================================" << std::endl;
			std::cout << "\t\t\tTotal Income: RM " << std::setw(10) << AnnualIncome << std::endl;
			std::cout << "==============================================================================" << std::endl;

			//===========================  bar graph ===================================

			int graph_width = 135;
			float max_value = AnnualIncome;        //year income

			CourtBooking* CB1 = courtBooking;
			while (CB1 != NULL) {			//find the occupy for each monthly income

				for (int i = 1; i <= 12; i++) {
					if (CB1->Month == i) {
						occupy[i - 1] = CB1->MonthlyIncome/AnnualIncome*100;
					}
				}
				CB1 = CB1->next;
			}


			std::cout << "\n===========================<<<< "<<input<<" Year Summary Report (Bar Graph) >>>>========================== \n" << std::endl;

			std::cout << std::fixed << std::setprecision(2);

			std::cout << "  MONTH   |     PROFIT" << std::endl;
			std::cout << "---------------------------" << std::endl;

			for (int i = 0; i < num_months; ++i)
			{
				SetConsoleTextAttribute(hConsole, i+2);
				std::cout << std::setw(6) << labels[i] << " | ";

				int bar_width = static_cast<int>(MonthlyIncome[i] / max_value * graph_width);

				for (int j = 0; j < bar_width; ++j)
				{
					std::cout << "#";
				}

				std::cout << " RM " << MonthlyIncome[i] << " : " << occupy[i] << "%" << std::endl;
			}
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "\n=================================================================================================" << std::endl;

			//============== file =========================
			std::string file;
			std::cout << "\nDo you want to export file? (0 to cancel):";
			std::getline(std::cin, file);

			if (file != "0") {
				//export file
				std::ofstream outfile;
				outfile.open("Summary Report " + input + ".txt");

				if (outfile.is_open()) {
					CourtBooking* CB = courtBooking;
					const int num_months = 12;
					float AnnualIncome = 0;
					float occupy[12] = { 0 };
					float MonthlyIncome[num_months] = { 0 };	//initial 0 ,to store monthly income

					std::string labels[num_months] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",		//Y-axis
										   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
					outfile << std::fixed << std::setprecision(2);
					while (CB != NULL) {			//find the annual income, store value to monthly income

						for (int i = 1; i <= 12; i++) {
							if (CB->Month == i) {
								MonthlyIncome[i - 1] = CB->MonthlyIncome;
							}
						}
						AnnualIncome += CB->MonthlyIncome;
						CB = CB->next;
					}

					//table
					outfile << "======================<<<< " << input << " Year Summary Report >>>>===================== \n" << std::endl;
					outfile << "                          MONTH           PROFIT(RM)\n";
					outfile << "-----------------------------------------------------------------------------\n";
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					for (int i = 0; i < num_months; ++i)
					{
						SetConsoleTextAttribute(hConsole, i + 2);
						outfile << std::setw(30) << labels[i] << ":\t\t " << std::setw(10) << MonthlyIncome[i] << std::endl;
					}
					SetConsoleTextAttribute(hConsole, 15);
					outfile << "\n";
					outfile << "==============================================================================" << std::endl;
					outfile << "\t\t\tTotal Income: RM " << std::setw(10) << AnnualIncome << std::endl;
					outfile << "==============================================================================" << std::endl;

					//===========================  bar graph ===================================

					int graph_width = 135;
					float max_value = AnnualIncome;        //year income

					CourtBooking* CB1 = courtBooking;
					while (CB1 != NULL) {			//find the occupy for each monthly income

						for (int i = 1; i <= 12; i++) {
							if (CB1->Month == i) {
								occupy[i - 1] = CB1->MonthlyIncome / AnnualIncome * 100;
							}
						}
						CB1 = CB1->next;
					}


					outfile << "\n===========================<<<< " << input << " Year Summary Report (Bar Graph) >>>>========================== \n" << std::endl;

					outfile << std::fixed << std::setprecision(2);

					outfile << "  MONTH   |     PROFIT" << std::endl;
					outfile << "---------------------------" << std::endl;

					for (int i = 0; i < num_months; ++i)
					{
						SetConsoleTextAttribute(hConsole, i + 2);
						outfile << std::setw(6) << labels[i] << " | ";

						int bar_width = static_cast<int>(MonthlyIncome[i] / max_value * graph_width);

						for (int j = 0; j < bar_width; ++j)
						{
							outfile << "#";
						}

						outfile << " RM " << MonthlyIncome[i] << " : " << occupy[i] << "%" << std::endl;
					}
					SetConsoleTextAttribute(hConsole, 15);
					outfile << "\n=================================================================================================" << std::endl;

					outfile.close();
					std::cout << "Successfully export Summary Report " + input + ".txt" << std::endl;

				}
				else {
					std::cout << "Unable export." << std::endl;
				}
			}
		}
		else if (input == "0")		//exit
		{
			break;
		}
		else
		{
			std::cout << "Not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");

	
}

void ManagerMethod::StatisticReport() {
	std::string input;
	int Year;
	CourtBookingController courtBookingController;

	do {
	inputYear:
		system("cls");

		std::cout << "========= Customer Statistic Report =========" << std::endl;
		std::cout << "Please input Year(0 to exit)[exp:2023]: ";
		std::getline(std::cin, input);

		// to handling user invalid input (avoid string & space)
		try {
			Year = std::stoi(input);
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Invalid input. Please enter a valid integer." << std::endl;
			system("pause");
			goto inputYear;
		}

		CourtBooking* courtBooking = courtBookingController.StatisticReport(Year);

		if (courtBooking != NULL)
		{
			CourtBooking* CB = courtBooking;
			const int num = 100;
			float AnnualIncome = 0;
			float occupy[num] = { 0 };

			system("cls");
			//table
			std::cout << "=======================================<<<< " << input << " Statistic Report >>>>======================================= \n" << std::endl;

			for (int i = 1; CB != NULL; i++)
			{
				AnnualIncome += CB->TypeIncome;
				CB = CB->next;
			}
			std::cout << std::fixed << std::setprecision(2);
			std::cout << "                                         Annual Income: RM" << AnnualIncome << std::endl << std::endl;
			std::cout << "=============================================================================================================" << std::endl;
			std::cout << "Profit base on user type:" << std::endl;
			std::cout << "=============================================================================================================" << std::endl << std::endl;


			//===========================  bar graph ===================================

			int graph_width = 125;
			float max_value = AnnualIncome;        //year income
			float valRatio[2], Ratio,MeanProfit[2],MeanDay[2];
			CourtBooking* CB1 = courtBooking;

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			for (int i = 0; CB1 != NULL; i++)
			{
				SetConsoleTextAttribute(hConsole, i+11);
				valRatio[i] = CB1->TypeIncome;			//i=0 for individual 1 for organization
				MeanProfit[i] = CB1->MeanProfit;
				MeanDay[i] = CB1->MeanDay;

				occupy[i] = CB1->TypeIncome / AnnualIncome * 100;			//find the occupy for each 

				std::cout << std::setw(20) << CB1->C_type << " | ";

				int bar_width = static_cast<int>(CB1->TypeIncome / max_value * graph_width);

				for (int j = 0; j < bar_width; ++j)
				{
					std::cout << "#";
				}

				std::cout << " RM " << CB1->TypeIncome << " : " << occupy[i] << "%" << std::endl;
				CB1 = CB1->next;
			}
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "\n";
			std::cout << "=============================================================================================================" << std::endl << std::endl;
			std::cout << "Content           |      INDIVIDUAL   |    ORGANIZATION" << std::endl;
			std::cout << "--------------------------------------------------------" << std::endl;
			Ratio = valRatio[1] / valRatio[0];
			std::cout << "Ratio:            |          1        :         " << Ratio << std::endl;
			std::cout << "Mean Profit:      |      " << MeanProfit[0] <<"      :       " << MeanProfit[1] << std::endl;
			std::cout << "Mean Booking Day: |        " << MeanDay[0] << "      :        " << MeanDay[1] << std::endl;
			std::cout << "\n";
			std::cout << "=============================================================================================================" << std::endl;



		}
		else if (input == "0")		//exit
		{
			break;
		}
		else
		{
			std::cout << "Not record" << std::endl;
		}
		std::cout << "Again? (press any key to continue / 0 to exit): ";
		std::getline(std::cin, input);
	} while (input != "0");
}

//tesing!
void ManagerMethod::TotalManager() {
	ManagerController managerController;
	int i = managerController.getCountManagerForSelect();
	std::cout << " cout :" << i;
}