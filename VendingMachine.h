#ifndef VENDINGMACHINE_H_INCLUDED
#define VENDINGMACHINE_H_INCLUDED
#include <string>
#include "System.h"
#include "ProductItem.h"

using namespace std;

class VendingMachine
{
public:
    VendingMachine(ProductItem *product);//copy constructor
    ~VendingMachine();//destrictor
    int p_In;//input
    int p_Quantity;//input
    double totalProfits;
    string m_Password;
    string m_NewPassword;
    string date;
    double totalCost;
    int VM_Inventory[9];//store the temporary inventory
    int VM_Purchased[9];//store the amount be purchased
    void menuDisplay(ProductItem *product);
    int buyItem(ProductItem *product, int *VM_Report);
    int update(ProductItem *product);
    int pay();
    int maintenancePasswordCheck(string password);
    int refillItem(ProductItem *product);
    string changePassword(string password);
    int salesReport(ProductItem *product, System Sys, int *VM_Report);

};

#endif // VENDINGMACHINE_H_INCLUDED


