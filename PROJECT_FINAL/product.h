#ifndef Product_H
#define Product_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Definitions.h"

class Seller;

class Product
{
public:
	enum eCategory { Children, Electricity, Clothing, Office };

private:
	char name[MAX_LENGTH];
	eCategory category;
	double price;
	int serial_number;
	Seller* seller;
	static int counter;

public:
	Product(char* name = NULL, eCategory category = (eCategory)0, double price = 0, Seller* seller = NULL); //constructor
	Product(const Product& other);//copy c'tor 
	~Product(); //destructor

	void setName(char* n);
	void setCategory(eCategory c);
	void setPrice(double p);
	bool setSeller(Seller* Seller);

	const char* getName()const;
	eCategory getCategory()const;
	double getPrice()const;
	int getSerialNumber()const;
	Seller* getSeller() const;
};

#endif // !Product_H