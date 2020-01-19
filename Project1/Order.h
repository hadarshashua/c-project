#ifndef Order_H
#define Order_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "Array.h"
#include "Definitions.h"
#include "product.h"

class Order
{
private:
	char buyerName[MAX_LENGTH];
	double totalSumCost;
	Array<Product*> productsArray;//new array of part 3 !!!!!----
								 //int logicProductsArraySize, physicProductsArraySize;
								 //Array <Product**> productsArray;--for targil 3 
public:
	Order(const char* buyerName, double totalSumCost = 0, Array<Product*> productsArray = NULL, int logicProductsArraySize = 0, int physicProductsArraySize = 1); //constructor
	Order(const Order& other); //copy c'tor
	~Order(); //destructor

	void setBuyerName(const char*& buyerName);
	void setTotalSumCost(double totalSumCost);
	void setProductsArray(Array<Product*> productsArray);
	//void setLogicProductsArraySize(const int& logicProductsArraySize);
	//void setPhysicProductsArraySize(const int& physicProductsArraySize);

	const char* getBuyerName() const;
	double getTotalSumCost() const;
	Array<Product*> getProductsArray() const;
	//const int& getLogicProductsArraySize() const;
	//const int& getPhysicProductsArraySize() ;

	void addProduct(Product*& product);
	void allocateProductList();
	void updateTotalSumCost();
};

#endif // !Order_H