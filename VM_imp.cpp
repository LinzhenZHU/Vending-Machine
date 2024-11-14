#include <iostream>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <string>
#include <limits>
#include "fstream"

#include "ProductItem.h"
#include "VendingMachine.h"
#include "System.h"

using namespace std;
fstream dataFile;

System::System()//constructor
{
    //get the system time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
    hour = ltm->tm_hour;
    minute = ltm->tm_min;
    second = ltm ->tm_sec;

}

ProductItem::ProductItem(string name, double cost)//constructor
{
    //initialize the inventory
    itemName = name;
    itemCost = cost;
    itemQuantity = 10;
}

VendingMachine::VendingMachine(ProductItem *product)//copy constructor
{
    //copy the inventory to the VM
    for (int i = 0; i < 9; i++)
    VM_Inventory[i] = product[i].itemQuantity;
    totalCost = 0;
}


void VendingMachine::menuDisplay(ProductItem *product)//Display the menu
{
    cout << setw(30) << right << "M E N U" << endl;
    cout << endl;
    cout << setw(12) << left << "[No.]";
    cout << setw(20) << left << "Product";
    cout << setw(12) << "Price";
    cout << setw(8) << right << "Inventory" << endl;
    for(int item = 0; item <=52; item ++)
    {
        cout << "-";
    }
    cout << endl;

    //loop for display each product
    for(int item = 0; item <=8; item ++)
    {

        cout << endl;
        cout << setw(12) << left << item + 1;
        cout << setw(20) << left << (product+item) -> itemName;
        cout << setw(12) << fixed << showpoint << setprecision(2) << (product+item) -> itemCost;
        cout << setw(8) << right << VM_Inventory[item] << endl;

    }

    for(int item = 0; item <=52; item ++)
    {
        cout << "-";
    }
    cout << endl;
}

int VendingMachine::buyItem(ProductItem *product, int VM_Report[9])//Enable customer to purchase
{
    cout << "Enter the [No.] (from 1 to 9) of the product you want to buy? ";
    cout << "(Enter [0] to cancel this purchase and return to the homepage)" << endl;
    cin >> p_In ;//input
    //judge the input
    while ((p_In > 9) || (p_In < 0) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number!" << endl;
            cin >> p_In;
        }
        else
        {
        cout << "Invalid input, please enter in the range of [0-9]!" << endl;
        cin >> p_In;
        }
    }

    if(p_In == 0)
    {
        return 9;
    }

    else
    {
        cout << "How many of the [" << (product-1+p_In) -> itemName << "] do you want?" << endl;
        cout << "(enter [0] to cancel select this item)" << endl;
        cin >> p_Quantity ;
        //does the amount selected resonable
        while (p_Quantity > VM_Inventory[p_In-1] || p_Quantity < 0 || cin.fail())
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_Quantity;
            }

            else if (p_Quantity < 0)
            {
                cout << "The number cannot be negative, please enter again!" << endl;
                cin >> p_Quantity;
            }

            else
            {
            cout << "Out of stock, please enter again!(enter [0] to cancel select this item)" << endl;
            cin >> p_Quantity;
            }

        }
        //display a purchase list
        VM_Inventory[p_In-1] -= p_Quantity;
        totalCost += p_Quantity * (product-1+p_In) -> itemCost;
        cout << setw(36) << right << "Purchased List" << endl;
        cout << endl;
        cout << setw(12) << left << "Amount";
        cout << setw(20) << left << "Product";
        cout << setw(12) << "Price";
        cout << setw(8) << right << "Cost" << endl;
        for(int item = 0; item <=52; item ++)
        {
            cout << "-";
        }
        cout << endl;

        for(int item = 0; item <=8; item ++)
        {
            if(((product+item) -> itemQuantity - VM_Inventory[item]) > 0)
            {
                cout << endl;
                cout << setw(12) << left << ((product+item) -> itemQuantity - VM_Inventory[item]);
                cout << setw(20) << left << (product+item) -> itemName;
                cout << setw(12) << fixed << showpoint << setprecision(2) << (product+item) -> itemCost;
                cout << setw(8) << right << fixed << showpoint << setprecision(2) << ((product+item) -> itemQuantity - VM_Inventory[item]) * (product+item) -> itemCost << endl;
            }


        }

        for(int item = 0; item <=52; item ++)
        {
            cout << "-";
        }
        cout << endl << setw(12) << "total cost: " << setw(40) << right  << totalCost << endl << endl;
        cout << "Enter [1] to MENU." << endl << "If finished, Enter [0] for Billing." << endl << endl;//select what's to do next
        cin >> p_In;
        while((p_In < 0)||(p_In > 1)|| cin.fail())
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_In;
            }
            else
            {
                cout << "Invalid input" << endl;
                cout << "Enter [1] to MENU," << endl;
                cout << "If finished, Enter [0] for Billing." << endl;
                cin >> p_In;
            }
        }
        if(p_In == 0)
        {
            for(int item = 0; item < 9; item ++)
            {
                VM_Report[item] +=  ((product+item) -> itemQuantity - VM_Inventory[item]);//calculate the overall for generate the final report
            }
            return 11;
        }
        else
        {
            return 10;
        }
    }
}

int VendingMachine::pay()
{
   cout << endl << totalCost <<" in total." << endl;
   cout << "Choose your pay method:" << endl;
   cout << "[0] for Wechat, [1] for Alipay" << endl;
   cin >> p_In;
   while((p_In < 0)||(p_In > 1)|| cin.fail())//judge the input
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_In;
            }
            else
            {
                cout << "Invalid input, [0] for Wechat, [1] for Alipay" << endl;//select the pay method
                cin >> p_In;
            }
        }

        if(p_In == 0)
        {
            cout << "Scan the [Wechat] QR code below" << endl << endl;
            cout << "***** ******** *****" << endl;
            cout << "* * * ******** * * *" << endl;
            cout << "***** ******** ****" << endl;
            cout << "*  *  ******   *****" << endl;
            cout << "**       ***********" << endl;
            cout << "***** ***    *******" << endl;
            cout << "**** **  ***********" << endl;
            cout << "*   *******  *  ****" << endl;
            cout << "*****    * * *****" << endl;
            cout << "* * * ***********" << endl;
            cout << "***** **************" << endl;
            cout << endl;
            for (int s = 3; s >= 0; s--)
            {
                cout << "\r" << s << " seconds to back Homepage";
                sleep(1);
            }
            cout << endl << endl;
        }

        if(p_In == 1)
        {
            cout << "Scan the [Alipay] QR code below" << endl << endl;
            cout << "***** ******** *****" << endl;
            cout << "* * * ******** * * *" << endl;
            cout << "***** ****** *****" << endl;
            cout << "*  *  ******   *****" << endl;
            cout << "**       ***********" << endl;
            cout << "***** ***    *******" << endl;
            cout << "**** **  ***********" << endl;
            cout << "*   *******  *  ****" << endl;
            cout << "*****    * * *******" << endl;
            cout << "* * * **************" << endl;
            cout << "***** **********" << endl;
            cout << endl;
            for (int s = 3; s >= 0; s--)
            {
                cout << "\r" << s << " seconds to back Homepage";
                sleep(1);
            }
            cout << endl << endl;
        }



    return 12;
}

int VendingMachine::update(ProductItem *product)//update the inventory after paied
{
    totalCost = 0;
     for (int item = 0; item <= 8; item ++)
    {
        (product + item) -> itemQuantity = VM_Inventory[item];
    }
    return 9;
}

int VendingMachine::maintenancePasswordCheck(string password)//check the password before enter the maintenance mode
{
    cout << "Hello, operator!" << endl << endl;
    cout << "Enter the password to enter the maintenanceMode" << endl;
    cout << "Enter [e] to exist" << endl;
    cin >> m_Password;
    //judgee whether the input is correct
    while(m_Password != password)
    {
        if (m_Password == "e")
        {
            return 9;
        }
        cout << "incorrect, try again!" << endl;
        cin >> m_Password;
    }
    return 20;
}

int VendingMachine::refillItem(ProductItem *product)//refill, the logic is opposite to purchase, the program is similar
{
    cout << "Enter the [No.] (from 1 to 9) of the product you want to refill? ";
    cout << "(Enter [0] to cancel this refill and return to the homepage)" << endl;
    cin >> p_In ;
    //check the input
    while ((p_In > 9) || (p_In < 0) || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number!" << endl;
            cin >> p_In;
        }
        else
        {
        cout << "Invalid input, please enter in the range of [0-9]!" << endl;
        cin >> p_In;
        }
    }

    if(p_In == 0)
    {
        return 24;
    }

    else
    {
        cout << "How many of the [" << (product-1+p_In) -> itemName << "] need to be refill?" << endl;
        cout << "(enter [0] to cancel select this item)" << endl;
        cin >> p_Quantity ;

        while (p_Quantity > (10-VM_Inventory[p_In-1]) || p_Quantity < 0 || cin.fail())
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_Quantity;
            }

            else if (p_Quantity < 0)
            {
                cout << "The number cannot be negative, please enter again!" << endl;
                cin >> p_Quantity;
            }

            else
            {
            cout << "Out of limitation, please enter again!(enter [0] to cancel select this item)" << endl;
            cin >> p_Quantity;
            }

        }

        VM_Inventory[p_In-1] += p_Quantity;
        cout << "Enter [1] to MENU." << endl << "If finished, Enter [0] to confirm." << endl << endl;
        cin >> p_In;
        while((p_In < 0)||(p_In > 1)|| cin.fail())
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_In;
            }
            else
            {
                cout << "Invalid input" << endl;
                cout << "Enter [1] to MENU," << endl;
                cout << "If finished, Enter [0] to confirm." << endl;
                cin >> p_In;
            }
        }

        if(p_In == 0)
        {
            return 25;
        }
        else
        {
            return 21;
        }
    }
}
string VendingMachine::changePassword(string password)//allow the operator to change the password
{
    cout << "Please enter the new password!" << endl;
    cin >> m_NewPassword;
    cout << "Please enter again to verify the password!" << endl;
    cin >>m_Password;
    if(m_Password == m_NewPassword)//need to double check the password
    {
        cout << "Password modified successfully!" << endl;
        for (int s = 3; s >= 0; s--)
            {
                cout << "\r" << s << " seconds to back";
                sleep(1);
            }
        return m_NewPassword;

    }
    else//if not the same, the modify will be canceled
    {
        cout << "Different input, modify canceled!" << endl;
        for (int s = 3; s >= 0; s--)
            {
                cout << "\r" << s << " seconds to back";
                sleep(1);
            }
        return password;
    }
}

int VendingMachine::salesReport(ProductItem *product, System Sys, int VM_Report[9])//generate the report
{
    //print the items to show
    cout << setw(30) << right << "SalesReport" << endl;
    cout << endl;
    cout << setw(12) << left << "Amount";
    cout << setw(20) << left << "Product";
    cout << setw(12) << "Profits";
    cout << setw(8) << right << "Inventory" << endl;
    for(int item = 0; item <=52; item ++)
    {
        cout << "-";
    }
    cout << endl;

    //loop for print each product's sales report
    for(int item = 0; item <=8; item ++)
    {

        cout << endl;
        cout << setw(12) << left << VM_Report[item];
        cout << setw(20) << left << (product+item) -> itemName;
        cout << setw(12) << fixed << showpoint << setprecision(2) << ((product+item) -> itemCost) * VM_Report[item];
        cout << setw(8) << right << VM_Inventory[item] << endl;
        totalProfits += ((product+item) -> itemCost) * VM_Report[item];

    }

    for(int item = 0; item <=52; item ++)
    {
        cout << "-";
    }
    date = std::to_string(Sys.year) + "." + std::to_string(Sys.month) + "." + std::to_string(Sys.day);
    cout << endl;
    cout << setw(20) << left << "total Profits: " << setw(32) << right  << totalProfits << endl;
    totalProfits = 0;
    cout << setw(20) << left << "Date: " << setw(32) << right << date << endl;
    cout << endl << "Enter [1] to output the report in textfile ";
    cout << "[" << date << ".txt" << "]" << endl;
    cout << "Enter [0] to return" << endl;
    cin >> p_In;//check the input
    while((p_In < 0)||(p_In > 1)|| cin.fail())
        {

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a number!" << endl;
                cin >> p_In;
            }
            else
            {
                cout << "Invalid input, please enter again!" << endl;
                cin >> p_In;
            }
        }

    if (p_In == 1)
    {
        dataFile.open(date+".txt", ios::out);//output to a txt

        dataFile << setw(30) << right << "SalesReport" << endl;
        dataFile << endl;
        dataFile << setw(12) << left << "Amount";
        dataFile << setw(20) << left << "Product";
        dataFile << setw(12) << "Profits";
        dataFile << setw(8) << right << "Inventory" << endl;
        for(int item = 0; item <=52; item ++)
        {
            dataFile << "-";
        }
        dataFile << endl;


        for(int item = 0; item <=8; item ++)
        {

            dataFile << endl;
            dataFile << setw(12) << left << VM_Report[item];
            dataFile << setw(20) << left << (product+item) -> itemName;
            dataFile << setw(12) << fixed << showpoint << setprecision(2) << ((product+item) -> itemCost) * VM_Report[item];
            dataFile << setw(8) << right << VM_Inventory[item] << endl;
            totalProfits += ((product+item) -> itemCost) * VM_Report[item];

        }

        for(int item = 0; item <=52; item ++)
        {
            dataFile << "-";
        }
        dataFile << endl;
        dataFile << setw(20) << left << "total Profits: " << setw(32) << right  << totalProfits << endl;
        dataFile << setw(20) << left << "Date: " << setw(32) << right << date << endl;
        cout << "Output successfully!" << endl;
        for (int s = 3; s >= 0; s--)
            {
                cout << "\r" << s << " seconds to back";
                sleep(1);
            }
        totalProfits = 0;
        dataFile.close();
        return 20;
    }
    if (p_In == 0) return 20;

}

VendingMachine::~VendingMachine()//deconstructor to clear the variable
{
    p_In = 0;
    p_Quantity;
}
