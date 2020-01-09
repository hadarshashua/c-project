#ifndef Seller_H
#define Seller_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

#include "FeedBack.h"
#include "Definitions.h"
#include "User.h"

class Seller:virtual public User
{
private:	
	FeedBack** feedbackArray;
	Product** listOfProducts;
	int logListProductSize, physicListProductSize;
	int logSizeOfFeedbackArray, physicSizeOfFeedbackArray;

public:
	Seller(char* userName, char* password, Address* address, FeedBack** feedBackArray = NULL, Product** listOfProducts = NULL, int logListProductSize = 0, int physicListProductSize = 1, int logSizeOfFeedbackArray = 0, int physicSizeOfFeedbackArray = 1);//constructor
	Seller(const Seller& other);//copy ctor 
	Seller(Seller&& other);//move c'tor
	~Seller();//destructor

	void setFeedbackArray(FeedBack**, int& logSize);
	void setListOfProducts(Product** productArray, int& logSize);
	void setLogListProductSize(int logListProductSize);
	void setPhysicListProductSize(int physicListProductSize);
	void setLogSizeOfFeedbackArray(int logSizeOfFeedbackArray);
	void setPhysicSizeOfFeedbackArray(int physicSizeOfFeedbackArray);

	FeedBack** getFeedbackArray();
	Product** getListOfProducts();
	int getLogListProductSize() const;
	int getPhysicListProductSize() const;
	int getLogSizeOfFeedbackArray() const;
	int getPhysicSizeOfFeedbackArray() const;

	void AddToProductList(Product newProduct);
	void allocateProductArray();
	void allocateForNewFeedback();
	void addFeedbackToSeller(FeedBack feedback);
};

#endif // !Seller_H