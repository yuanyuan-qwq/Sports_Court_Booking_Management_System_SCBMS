#include "StaffView.h"
#include "ManagerView.h"
#include "ManagerMethod.h"
#include <conio.h>

StaffMethod staffMethod;



//Staff login
void StaffView::StaffLoginMenu() {
	std::string UserName, Password, ZeroToExit;
	int chance = 3;
	StaffController staffController;

	do {
		system("cls");
		if (chance == 0) {
			std::cout << "UNNORMAL ACTION DETECTED!!! \nSystem Lockdown\n";
			system("pause");
			exit(0);
		}

		std::cout << "------------- Staff Login Page ------------- \n";
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

		Staff* staff = staffController.StaffLogin(UserName, Password);

		if (staff != NULL && staff->status == "Active")
		{
			StaffMainMenu(staff);
			chance = 3;
		}
		else if ((staff != NULL && staff->status != "Active"))
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

void StaffView::StaffMainMenu(Staff* staff) {

	std::string select;


	do {
		system("cls");
		std::cout << "Welcome Staff: " << staff->S_Name << std::endl;
		std::cout << "========= Staff Main Menu =========" << std::endl;
		std::cout << "1.My Information" << std::endl;
		std::cout << "2.Edit My Information" << std::endl;
		std::cout << "3.Upcoming My Task(Booking)" << std::endl;
		std::cout << "4.All My Task History" << std::endl;
		std::cout << "================ Other Method for Staff ================" << std::endl;	//below reuse manager method
		std::cout << "5.Customer Detail" << std::endl;
		std::cout << "6.Staff Detail" << std::endl;
		std::cout << "7.Manager Detail" << std::endl;
		std::cout << "8.Sport Court Detail" << std::endl;
		std::cout << "9.Booking Detail" << std::endl;
		std::cout << "0.Logout" << std::endl;
		std::cout << "Select(0-9) :";
		std::getline(std::cin, select);

		if (select == "1")			//My Information
		{
			staffMethod.StaffDetial(staff);
			system("pause");
		}
		else if (select == "2")		//StaffSelfUpdate
		{
			staffMethod.StaffSelfUpdate(staff);
		}
		else if (select == "3")		//UpComingTask
		{
			staffMethod.UpComingTask(staff);
			system("pause");
		}
		else if (select == "4")		//AllHistoryTask
		{
			staffMethod.AllHistoryTask(staff);
			system("pause");
		}
		else if (select == "5")		//Customer Detail
		{
			ManagerView managerView;
			managerView.CustomerMethodForAdmin();
		}
		else if (select == "6")		//Staff Detail
		{
			StaffSearch();				
		}
		else if (select == "7")		//Manager Detail
		{
			ManagerSearch();
		}
		else if (select == "8")		//Sport Court Detail
		{
			SportCourtMethodStaff();
		}
		else if (select == "9")		//Booking Detail
		{
			CourtBookingMethodStaff();
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

void StaffView::StaffSearch() {
	ManagerMethod MGMethod;
	std::string select;

	do {
		system("cls");

		std::cout << "==================== Staff Detail Menu ====================" << std::endl;
		std::cout << "1.All Staff Details" << std::endl;
		std::cout << "==================== Search Staff Detail ====================" << std::endl;
		std::cout << "2.Search Staff Detail By ID" << std::endl;
		std::cout << "3.Search Staff Detail By Manager ID" << std::endl;
		std::cout << "4.Search Staff Detail By Name" << std::endl;
		std::cout << "5.Search Staff Detail By Gender" << std::endl;
		std::cout << "6.Search Staff Detail By HpNo" << std::endl;
		std::cout << "7.Search Staff Detail By Email" << std::endl;
		std::cout << "8.Search Staff Detail By Status" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-8) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			system("cls");
			MGMethod.AllStaffDetails();
			system("pause");
		}
		else if (select == "2")
		{
			MGMethod.IDSearchStaff();
		}
		else if (select == "3")
		{
			MGMethod.MIDSearchStaff();
		}
		else if (select == "4")
		{
			MGMethod.NameSearchStaff();
		}
		else if (select == "5")
		{
			MGMethod.GenderSearchStaff();
		}
		else if (select == "6")
		{
			MGMethod.HpNoSearchStaff();
		}
		else if (select == "7")
		{
			MGMethod.EmailSearchStaff();
		}
		else if (select == "8")
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

void StaffView::ManagerSearch() {
	ManagerMethod MGMethod;
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Manager Detail Menu ====================" << std::endl;
		std::cout << "1.All Manager Details" << std::endl;
		std::cout << "==================== Search Manager Detail ====================" << std::endl;
		std::cout << "2.Search Manager Detail By ID" << std::endl;
		std::cout << "3.Search Manager Detail By Name" << std::endl;
		std::cout << "4.Search Manager Detail By Gender" << std::endl;
		std::cout << "5.Search Manager Detail By HpNo" << std::endl;
		std::cout << "6.Search Manager Detail By Email" << std::endl;
		std::cout << "7.Search Manager Detail By Status" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-7) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.AllManagerDetails();
			system("pause");
		}
		else if (select == "2")
		{
			MGMethod.IDSearchManager();
		}
		else if (select == "3")
		{
			MGMethod.NameSearchManager();
		}
		else if (select == "4")
		{
			MGMethod.GenderSearchManager();
		}
		else if (select == "5")
		{
			MGMethod.HpNoSearchManager();
		}
		else if (select == "6")
		{
			MGMethod.EmailSearchManager();
		}
		else if (select == "7")
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

void StaffView::SportCourtMethodStaff(){
	ManagerMethod MGMethod; //reuse some manager method
	std::string select;

	do {
		system("cls");
		std::cout << "==================== SportCourt Detail Menu ====================" << std::endl;
		std::cout << "1.All SportCourt Details" << std::endl;
		std::cout << "==================== Search SportCourt Detail ====================" << std::endl;
		std::cout << "2.Search SportCourt Detail By ID" << std::endl;
		std::cout << "3.Search SportCourt Detail By Name" << std::endl;
		std::cout << "4.Search SportCourt Detail By Status" << std::endl;
		std::cout << "5.Search SportCourt Detail By PricePerDay" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-5) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.AllSportCourtDetails();
			system("pause");
		}
		else if (select == "2")
		{
			MGMethod.IDSearchSportCourt();
		}
		else if (select == "3")
		{
			MGMethod.NameSearchSportCourt();
		}
		else if (select == "4")
		{
			MGMethod.StatusSearchSportCourt();
		}
		else if (select == "5")
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

void StaffView::CourtBookingMethodStaff() {
	ManagerMethod MGMethod; //reuse some manager method
	std::string select;

	do {
		system("cls");
		std::cout << "==================== Court Booking Detail Menu ====================" << std::endl;
		std::cout << "1.Insert CourtBooking" << std::endl;
		std::cout << "2.Delete CourtBooking" << std::endl;
		std::cout << "3.All CourtBooking Details" << std::endl;
		std::cout << "4.All UpComing CourtBooking Details" << std::endl;
		std::cout << "==================== Search CourtBooking Detail ====================" << std::endl;
		std::cout << "5.Search CourtBooking Detail By BookingID" << std::endl;
		std::cout << "6.Search CourtBooking Detail By CustomerID" << std::endl;
		std::cout << "7.Search CourtBooking Detail By SportCourtID" << std::endl;
		std::cout << "8.Search CourtBooking Detail By StaffID" << std::endl;
		std::cout << "9.Search CourtBooking Detail By DateIN" << std::endl;
		std::cout << "10.Search CourtBooking Detail By DateOUT" << std::endl;
		std::cout << "11.Search CourtBooking Detail By Year" << std::endl;
		std::cout << "12.Search CourtBooking Detail By TotalDay" << std::endl;
		std::cout << "13.Search CourtBooking Detail By TotalCharge" << std::endl;
		std::cout << "14.Search CourtBooking Detail By PaymentType" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "0.back" << std::endl;
		std::cout << "=================================================================" << std::endl;
		std::cout << "Select(0-13) :";
		std::getline(std::cin, select);

		if (select == "1")
		{
			MGMethod.InsertCourtBooking();
		}
		else if (select == "2")
		{
			MGMethod.DeleteCourtBooking();
		}
		else if (select == "3")
		{
			MGMethod.AllCourtBookingDetails();
			system("pause");
		}
		else if (select == "4")
		{
			MGMethod.AllUpComingCourtBookingDetails();
			system("pause");
		}
		else if (select == "5")
		{
			MGMethod.BookingIDSearchCourtBooking();
		}
		else if (select == "6")
		{
			MGMethod.CustomerIDSearchCourtBooking();
		}
		else if (select == "7")
		{
			MGMethod.SportCourtIDSearchCourtBooking();
		}
		else if (select == "8")
		{
			MGMethod.StaffIDSearchCourtBooking();
		}
		else if (select == "9")
		{
			MGMethod.DateINSearchCourtBooking();
		}
		else if (select == "10")
		{
			MGMethod.DateOUTSearchCourtBooking();
		}
		else if (select == "11")
		{
			MGMethod.YearSearchCourtBooking();
		}
		else if (select == "12")
		{
			MGMethod.TotalDaySearchCourtBooking();
		}
		else if (select == "13")
		{
			MGMethod.TotalChargeSearchCourtBooking();
		}
		else if (select == "14")
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