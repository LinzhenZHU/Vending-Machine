//the default password for maintenance mode is "000000"
#include <iostream>
#include <conio.h>
#include <iomanip>

#include "ProductItem.h"
#include "VendingMachine.h"
#include "System.h"

using namespace std;

//use up down to select
int select (int num_items, string* items)
{
    cout << "Using the [UP] or [DOWN] key to select,"<< endl;
    cout << "Press the [Enter] key to enter!"<< endl << endl;
    int selected_item = 0;
    for (int i = 0; i < num_items; i++) {
        if (i == selected_item) {
            cout << "> " << items[i] << endl;
        } else {
            cout << "  " << items[i] << endl;
        }
    }

    // select using the arrow keys
    char key;
    while ((key = getch()) != '\r') {
        switch (key) {
            case 72:  // Up arrow key
                selected_item = (selected_item + num_items -1 ) % num_items;//move to up
                break;
            case 80:  // Down arrow key
                selected_item = (selected_item + num_items + 1) % num_items;//move to down
                break;
        }

        // Reprint the new selection
        system("cls");
        cout << "Using the [UP] or [DOWN] key to select,"<< endl;
        cout << "Press the [Enter] key to enter!"<< endl << endl;
        for (int i = 0; i < num_items; i++) {
            if (i == selected_item) {
                cout << "> " << items[i] << endl;
            } else {
                cout << "  " << items[i] << endl;
            }
        }
    }
    // Confirm the selection and return
    return selected_item;
}

int main()
{
    //initialize
    int status = 9;
    string password = "000000";
    int VM_Report[9] = {0,0,0,0,0,0,0,0,0};;//store the whole amount be purchased
    //Purchase-1, Select Product-10, Pay-11, Update Inventory-12
    //Maintenance-2, Select Mode-20, Refill-21, Sales Report-22, Change Password-23, Cancel Refill-24, Update Inventory-25
    //Quite-0,
    //Homepage-9;


    System Sys;

    ProductItem product[9] =
    {
        ProductItem("Sprite", 3),
        ProductItem("Coca Cola", 3),
        ProductItem("Pepsi", 3),
        ProductItem("Orange", 3),
        ProductItem("Lemon Tea", 5),
        ProductItem("Coffee", 6),
        ProductItem("Milk Tea", 6),
        ProductItem("Green Tea", 5),
        ProductItem("Mineral Water", 2)
    };

    VendingMachine* VM = new VendingMachine(product);

    while(1)
    {
        if (status == 9)//HomePage
        {
            system("cls");
            cout << Sys.year << "/" << Sys.month << "/" << Sys.day << endl;
            cout << "*******************" << endl;
            cout << "* W E L C O M E ! *" << endl;
            cout << "*******************" << endl;
            cout << endl;
            string items[3] = {"Quit", "Purchase", "Maintenance"};
            status = select(3, items);
            delete VM;

        }
        if (status == 0)//Quite
        {
            system("cls");
            return 0;
        }

        if (status == 1)//Purchase
        {
            system("cls");
            VendingMachine* VM = new VendingMachine(product);

            status = 10;
        }

        if (status == 10)//Select Product
        {
            VM->menuDisplay(product);
            status = VM->buyItem(product, VM_Report);
        }

        if (status == 11)//pay
        {
            status = VM->pay();
        }

        if (status == 12)//Update Inventory
        {
            system("cls");
            status = VM->update(product);
        }

        if (status == 2)//Maintenance
        {
            VendingMachine* VM = new VendingMachine(product);
            system("cls");
            status = VM->maintenancePasswordCheck(password);
        }

        if (status == 20)//Select Mode
        {
            system("cls");
            string items[4] = {"Quit", "Refill", "Sales Report", "Change Password"};
            status = select(4, items);
            if (status == 0) status = 9;
            else status = status + 20;
        }

        if (status == 21)//Refill
        {
            system("cls");
            VM->menuDisplay(product);
            status = VM->refillItem(product);
        }

        if (status == 22)//Report
        {
            status = VM->salesReport(product, Sys, VM_Report);
        }

        if (status == 23)//Change Password
        {
            password = VM->changePassword(password);
            status = 20;
        }

        if (status == 24)//Cancel Refill
        {
            system("cls");
            delete VM;
            VendingMachine* VM = new VendingMachine(product);
            status = 20;
        }

         if (status == 25)//Update
        {
            system("cls");
            VM->update(product);
            status = 20;
        }

    }















}
