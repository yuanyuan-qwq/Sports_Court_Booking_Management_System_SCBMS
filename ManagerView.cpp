#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<cstdlib>  
#include<time.h>
#include <conio.h>


#include "ManagerView.h"

ManagerMethod MGMethod;

//Manager login
void ManagerView::ManagerLoginMenu() {
	std::string UserName, Password, ZeroToExit;
	int chance=3;
	ManagerController managerController;

	do {
		system("cls");
		//####### detect unnormal action #########
		if (chance == 0) {
			std::cout << "UNNORMAL ACTION DETECTED!!! \nSystem Lockdown\n";
			system("pause");
			exit(0);
		}

		std::cout << "------------- Manager Login Page ------------- \n";
		std::cout << "User Name (0 to exit): ";
		std::getline(std::cin, UserName);

		ZeroToExit = UserName;

		if (ZeroToExit == "0")
		{
			break;
		}
		//################### hide password ##################
		do {
			char c;
			std::string password;		//for temp use, after loop(while) clear data in password
			std::cout << "Enter password: ";
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
			Password = password;
			std::cout << std::endl;
		} while (false);

		Manager* manager = managerController.ManagerLogin(UserName, Password);

		if (manager != NULL && manager->status=="Active")
		{
			ManagerMainMenu(manager);
			chance = 3;
		}
		else if(manager != NULL && manager->status != "Active")
		{
			std::cout << "\nYour account is Frozen, any question please contact this email fuyuanlum@gmail.com\n";
			system("pause");
			break;
		}
		else
		{
			std::cout << "UserName and Password Not Match!!\nDo you want to try again? press any key to continue(0 to exit):";
			std::getline(std::cin, ZeroToExit);
			chance--;

		}
	} while (ZeroToExit != "0");

}

void ManagerView::ManagerMainMenu(Manager* manager) {

	std::string select;


	do {
		system("cls");
		std::cout << "Welcome Manager: " << manager->M_Name<<std::endl;
		std::cout << "========= Manager Main Menu =========" << std::endl;
		std::cout << "1.Customer Detail" << std::endl;
		std::cout << "2.Staff Detail" << std::endl;
		std::cout << "3.Manager Detail" << std::endl;
		std::cout << "4.Sport Court Detail" << std::endl;
		std::cout << "5.Booking Detail" << std::endl;
		std::cout << "6.Report Detail" << std::endl;
		std::cout << "7.Customers Statistics Detail" << std::endl;
		std::cout << "0.Logout" << std::endl;
		std::cout << "Select(0-7) :";
		std::getline(std::cin, select);

		if (select == "1")			//Customer Detail
		{
			CustomerMethodForAdmin();
		}
		else if (select == "2")		//Staff Detail
		{
			StaffMethodForAdmin();
		}
		else if (select == "3")		//Manager Detail
		{
			ManagerSelfMethod();
		}
		else if (select == "4")		//Sport court Detail
		{
			SportCourtMethod();
		}
		else if (select == "5")		//Booking Detail
		{
			CourtBookingMethod();			
		}
		else if (select == "6")		//Report Detail
		{
			GenerateReportMethod();

		}
		else if (select == "7")		//Statistics Detail
		{
			MGMethod.StatisticReport();
		}
		else if (select == "0")		//Logout
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");

}

void ManagerView::CustomerMethodForAdmin() {

	std::string select;

	do {
		system("cls");
		std::cout << "==================== Customer Detail Menu ====================" << std::endl;
		std::cout << "1.Insert Customer" << std::endl;
		std::cout << "2.Update Customer" << std::endl;
		std::cout << "3.Delete Customer" << std::endl;
		std::cout << "4.All Customer Details" << std::endl;
		std::cout << "==================== Search Customer Detail ====================" << std::endl;
		std::cout << "5.Search Customer Detail By ID" << std::endl;
		std::cout << "6.Search Customer Detail By Name" << std::endl;
		std::cout << "7.Search Customer Detail By Type" << std::endl;
		std::cout << "8.Search Customer Detail By Address" << std::endl;
		std::cout << "9.Search Customer Detail By HpNo" << std::endl;
		std::cout << "10.Search Customer Detail By Email" << std::endl;
		std::cout << "11.Search Customer Detail By Status" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-11) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertCustomer();
		}
		else if (select == "2")
		{
			MGMethod.UpdateCustomer();
		}
		else if (select == "3")
		{
			MGMethod.DeleteCustomer();
		}
		else if (select == "4")
		{
			MGMethod.AllCustomerDetails();
		}
		else if (select == "5")
		{
			MGMethod.IDSearchCustomer();
		}
		else if (select == "6")
		{
			MGMethod.NameSearchCustomer();
		}
		else if (select == "7")
		{
			MGMethod.TypeSearchCustomer();
		}
		else if (select == "8")
		{
			MGMethod.AddressSearchCustomer();
		}
		else if (select == "9")
		{
			MGMethod.HpNoSearchCustomer();
		}
		else if (select == "10")
		{
			MGMethod.EmailSearchCustomer();
		}
		else if (select == "11")
		{
			MGMethod.StatusSearchCustomer();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");

}

void ManagerView::StaffMethodForAdmin() {
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Staff Detail Menu ====================" << std::endl;
		std::cout << "1.Insert Staff" << std::endl;
		std::cout << "2.Update Staff" << std::endl;
		std::cout << "3.Delete Staff" << std::endl;
		std::cout << "4.All Staff Details" << std::endl;
		std::cout << "==================== Search Staff Detail ====================" << std::endl;
		std::cout << "5.Search Staff Detail By ID" << std::endl;
		std::cout << "6.Search Staff Detail By Manager ID" << std::endl;
		std::cout << "7.Search Staff Detail By Name" << std::endl;
		std::cout << "8.Search Staff Detail By Gender" << std::endl;
		std::cout << "9.Search Staff Detail By HpNo" << std::endl;
		std::cout << "10.Search Staff Detail By Email" << std::endl;
		std::cout << "11.Search Staff Detail By Status" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-11) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertStaff();
		}
		else if (select == "2")
		{
			MGMethod.UpdateStaff();
		}
		else if (select == "3")
		{
			MGMethod.DeleteStaff();
		}
		else if (select == "4")
		{
			system("cls");
			MGMethod.AllStaffDetails();
			system("pause");
		}
		else if (select == "5")
		{
			MGMethod.IDSearchStaff();
		}
		else if (select == "6")
		{
			MGMethod.MIDSearchStaff();
		}
		else if (select == "7")
		{
			MGMethod.NameSearchStaff();
		}
		else if (select == "8")
		{
			MGMethod.GenderSearchStaff();
		}
		else if (select == "9")
		{
			MGMethod.HpNoSearchStaff();
		}
		else if (select == "10")
		{
			MGMethod.EmailSearchStaff();
		}
		else if (select == "11")
		{
			MGMethod.StatusSearchStaff();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");
}

void ManagerView::ManagerSelfMethod() {
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Manager Detail Menu ====================" << std::endl;
		std::cout << "1.Insert Manager" << std::endl;
		std::cout << "2.Update Manager" << std::endl;
		std::cout << "3.Delete Manager" << std::endl;
		std::cout << "4.All Manager Details" << std::endl;
		std::cout << "==================== Search Manager Detail ====================" << std::endl;
		std::cout << "5.Search Manager Detail By ID" << std::endl;
		std::cout << "6.Search Manager Detail By Name" << std::endl;
		std::cout << "7.Search Manager Detail By Gender" << std::endl;
		std::cout << "8.Search Manager Detail By HpNo" << std::endl;
		std::cout << "9.Search Manager Detail By Email" << std::endl;
		std::cout << "10.Search Manager Detail By Status" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-10) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertManager();
		}
		else if (select == "2")
		{
			MGMethod.UpdateManager();
		}
		else if (select == "3")
		{
			MGMethod.DeleteManager();
		}
		else if (select == "4")
		{
			MGMethod.AllManagerDetails();
			system("pause");
		}
		else if (select == "5")
		{
			MGMethod.IDSearchManager();
		}
		else if (select == "6")
		{
			MGMethod.NameSearchManager();
		}
		else if (select == "7")
		{
			MGMethod.GenderSearchManager();
		}
		else if (select == "8")
		{
			MGMethod.HpNoSearchManager();
		}
		else if (select == "9")
		{
			MGMethod.EmailSearchManager();
		}
		else if (select == "10")
		{
			MGMethod.StatusSearchManager();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");
}	

void ManagerView::SportCourtMethod() {
	std::string select;

	do {
		system("cls");
		std::cout << "==================== SportCourt Detail Menu ====================" << std::endl;
		std::cout << "1.Insert SportCourt" << std::endl;
		std::cout << "2.Update SportCourt" << std::endl;
		std::cout << "3.Delete SportCourt" << std::endl;
		std::cout << "4.All SportCourt Details" << std::endl;
		std::cout << "==================== Search SportCourt Detail ====================" << std::endl;
		std::cout << "5.Search SportCourt Detail By ID" << std::endl;
		std::cout << "6.Search SportCourt Detail By Name" << std::endl;
		std::cout << "7.Search SportCourt Detail By Status" << std::endl;
		std::cout << "8.Search SportCourt Detail By PricePerDay" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-8) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertSportCourt();
		}
		else if (select == "2")
		{
			MGMethod.UpdateSportCourt();
		}
		else if (select == "3")
		{
			MGMethod.DeleteSportCourt();
		}
		else if (select == "4")
		{
			MGMethod.AllSportCourtDetails();
			system("pause");
		}
		else if (select == "5")
		{
			MGMethod.IDSearchSportCourt();
		}
		else if (select == "6")
		{
			MGMethod.NameSearchSportCourt();
		}
		else if (select == "7")
		{
			MGMethod.StatusSearchSportCourt();
		}
		else if (select == "8")
		{
			MGMethod.PriceSearchSportCourt();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");
}

void ManagerView::CourtBookingMethod(){
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Court Booking Detail Menu ====================" << std::endl;
		std::cout << "1.Insert CourtBooking" << std::endl;
		std::cout << "2.Update CourtBooking" << std::endl;
		std::cout << "3.Delete CourtBooking" << std::endl;
		std::cout << "4.All CourtBooking Details" << std::endl;
		std::cout << "5.All UpComing CourtBooking Details" << std::endl;
		std::cout << "==================== Search CourtBooking Detail ====================" << std::endl;
		std::cout << "6.Search CourtBooking Detail By BookingID" << std::endl;
		std::cout << "7.Search CourtBooking Detail By CustomerID" << std::endl;
		std::cout << "8.Search CourtBooking Detail By SportCourtID" << std::endl;
		std::cout << "9.Search CourtBooking Detail By StaffID" << std::endl;
		std::cout << "10.Search CourtBooking Detail By DateIN" << std::endl;
		std::cout << "11.Search CourtBooking Detail By DateOUT" << std::endl;
		std::cout << "12.Search CourtBooking Detail By Year" << std::endl;
		std::cout << "13.Search CourtBooking Detail By TotalDay" << std::endl;
		std::cout << "14.Search CourtBooking Detail By TotalCharge" << std::endl;
		std::cout << "15.Search CourtBooking Detail By PaymentType" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-15) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertCourtBooking();
		}
		else if (select == "2")
		{
			MGMethod.UpdateCourtBooking();	//not bulid yet
		}
		else if (select == "3")
		{
			MGMethod.DeleteCourtBooking();	
		}
		else if (select == "4")
		{
			MGMethod.AllCourtBookingDetails();
			system("pause");
		}
		else if (select == "5")
		{
			MGMethod.AllUpComingCourtBookingDetails();
			system("pause");
		}
		else if (select == "6")
		{
			MGMethod.BookingIDSearchCourtBooking();
		}
		else if (select == "7")
		{
			MGMethod.CustomerIDSearchCourtBooking();
		}
		else if (select == "8")
		{
			MGMethod.SportCourtIDSearchCourtBooking();
		}
		else if (select == "9")
		{
			MGMethod.StaffIDSearchCourtBooking();
		}
		else if (select == "10")
		{
			MGMethod.DateINSearchCourtBooking();
		}
		else if (select == "11")
		{
			MGMethod.DateOUTSearchCourtBooking();
		}
		else if (select == "12")
		{
			MGMethod.YearSearchCourtBooking();
		}
		else if (select == "13")
		{
			MGMethod.TotalDaySearchCourtBooking();
		}
		else if (select == "14")
		{
			MGMethod.TotalChargeSearchCourtBooking();
		}
		else if (select == "15")
		{
			MGMethod.PaymentTypeSearchCourtBooking();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");
}

void ManagerView::GenerateReportMethod(){
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Report Generate Menu ====================" << std::endl;
		std::cout << "1.Annual Report" << std::endl;
		std::cout << "2.Monthly Report" << std::endl;
		std::cout << "3.Highest Demand Sport Court" << std::endl;
		std::cout << "4.Year Summary Report" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-4) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.AnnualIncome();
		}
		else if (select == "2")
		{
			MGMethod.MonthlyIncome();
		}
		else if (select == "3")
		{
			MGMethod.HighDemandSportCourt();
		}
		else if (select == "4")
		{
			MGMethod.SummaryReport();
		}
		else if (select == "0")
		{
			break;
		}
		else						//Invalid selection
		{
			std::cout << "Invaild Input!!" << std::endl;
			system("pause");
		}

	} while (select != "0");



}



