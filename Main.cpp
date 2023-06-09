#include<iostream>
#include<cstring>
#include<string>
#include<iomanip>

#include <windows.h>

#include "CustomerView.h"
#include "StaffView.h"
#include "ManagerView.h"



/*
std::string buffer;
std::getline(std::cin, buffer);
*/

int main() {

    std::string menu;
    do {
        system("cls");
        //Start up logo
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 9);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 11);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << "####################======================================================        Colby         ======================================================####################\n";
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << "####################======================================================        College       ======================================================####################\n";
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << "####################======================================================        Sports        ======================================================####################\n";
        SetConsoleTextAttribute(hConsole, 14);
        std::cout << "####################======================================================        Centre        ======================================================####################\n";
        SetConsoleTextAttribute(hConsole, 12);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 11);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "##########################################################################################################################################################################\n";
        SetConsoleTextAttribute(hConsole, 9);
        std::cout << "##########################################################################################################################################################################\n\n\n";


        //Main Manu
        
        SetConsoleTextAttribute(hConsole, 15);
  

        std::cout << "=========================================================================================================================================================================\n";
        std::cout << "======================================================= Welcome To Sports Court Booking Management System (SCBMS) =======================================================\n";
        std::cout << "=========================================================================================================================================================================\n\n\n";
        std::cout << std::setw(94) << "1. Customer Login" << std::endl;
        std::cout << std::setw(91) << "2. Staff Login" << std::endl;
        std::cout << std::setw(93) << "3. Manager Login" << std::endl;
        std::cout << std::setw(97) << "4. Customer Register" << std::endl;
        std::cout << std::setw(84) << "0. Exit" << std::endl;
        std::cout << std::setw(85) << "Choose: ";
        std::getline(std::cin, menu);

        if (menu == "1") {
            CustomerView Cview;
            Cview.CustomerLoginMenu();
        }
        else if (menu == "2") {
            StaffView SView;
            SView.StaffLoginMenu();
        }
        else if (menu == "3") {
            ManagerView MView;
            MView.ManagerLoginMenu();
        }
        else if (menu == "4") {
            CustomerMethod CMethod;
            CMethod.CustomerRegister();
        }
        else if (menu == "0") {
            std::cout << "Program Exiting..." << std::endl;
        }
        else {
            std::cout << "Please choose between 0 - 4. ";
            system("pause");
        }

    } while (menu != "0");
    return 0;
}
