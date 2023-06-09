#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>
#include<cstdlib>  
#include<time.h>
#include <conio.h>

#include "CustomerView.h"

CustomerMethod CMethod;


//customer login
void CustomerView::CustomerLoginMenu() {
	std::string UserName, Password, ZeroToExit;
	int chance = 3;
	CustomerController customerController;

	do {
		system("cls");
		//####### detect unnormal action #########
		if (chance == 0) {
			std::cout << "UNNORMAL ACTION DETECTED!!! \nSystem Lockdown\n";
			std::cout << "if you forget the password or username,or any problem please contact this email fuyuanlum@gmail.com\n";
			system("pause");
			exit(0);
		}

		std::cout << "------------- Customer Login Page ------------- \n";
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

		Customer* customer = customerController.CustomerLogin(UserName, Password);

		if(customer != NULL && customer->status == "Active")
		{
			CustomerMainMenu(customer);
			chance = 3;
		}
		else if (customer != NULL && customer->status != "Active")
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

void CustomerView::CustomerMainMenu(Customer* customer) {

	std::string select;

	do {
		system("cls");
		std::cout << "Welcome Customer: " << customer->C_Name <<std::endl;
		std::cout << "========= Customer Main Menu =========" << std::endl;
		std::cout << "1.Customer Detail" << std::endl;
		std::cout << "2.Edit Customer Detail" << std::endl;
		std::cout << "3.View All Sport Court" << std::endl;
		std::cout << "4.Make Booking" << std::endl;
		std::cout << "5.Upcoming Reservations" << std::endl;
		std::cout << "6.Check My Booking History" << std::endl;
		std::cout << "0.Logout" << std::endl;
		std::cout << "Select(0-6) :";
		std::getline(std::cin, select);

		if (select == "1")			//Customer Detail
		{
			CMethod.CustomerDetial(customer);
			system("pause");
		}
		else if (select == "2")		//Edit Customer Detail
		{
			CMethod.CustomerSelfUpdate(customer);
		}
		else if (select == "3")		//View All Sport Court
		{
			CMethod.ViewAllSportCourt();
			system("pause");
		}
		else if (select == "4")		//Make Booking
		{
			CMethod.MakeBooking(customer); 
			system("pause");
		}
		else if (select == "5")		//UpComing Booking 
		{
			CMethod.UpComing(customer);
			system("pause");
		}
		else if (select == "6")		//Check My Booking History
		{
			CMethod.CheckMyBookingHistory(customer);
			system("pause");
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
