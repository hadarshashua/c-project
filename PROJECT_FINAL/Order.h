#ifndef Order_H
#define Order_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Definitions.h"
#include "product.h"

class Order
{
private:
	char buyerName[MAX_LENGTH];
	double totalSumCost;
	Product** productsArray;
	int logicProductsArraySize, physicProductsArraySize;

public:
	Order(const char* buyerName , double totalSumCost = 0, Product** productsArray = NULL, int logicProductsArraySize = 0, int physicProductsArraySize = 1); //constructor
	Order(const Order& other); //copy c'tor
	~Order(); //destructor

	void setBuyerName(char* buyerName);
	void setTotalSumCost(double totalSumCost);
	void setProductsArray(Product** productsArray);
	void setLogicProductsArraySize(int logicProductsArraySize);
	void setPhysicProductsArraySize(int physicProductsArraySize);

	const char* getBuyerName() const;
	double getTotalSumCost() const;
	Product** getProductsArray() const; 
	int getLogicProductsArraySize() const;
	int getPhysicProductsArraySize() const;

	void addProduct(Product& product);
	void allocateProductList();
	void updateTotalSumCost();
};

#endif // !Order_H