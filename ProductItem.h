#ifndef PRODUCTITEM_H_INCLUDED
#define PRODUCTITEM_H_INCLUDED
#include <string>

using namespace std;

class ProductItem
{
public:
    ProductItem(string, double);//constructor
    string itemName;
    int itemQuantity;
    double itemCost;
};


#endif // PRODUCTITEM_H_INCLUDED
