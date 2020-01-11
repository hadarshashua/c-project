#ifndef ECommercySystem_H
#define ECommercySystem_H
#pragma warning(disable : 4996)
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Definitions.h"
#include "Seller.h"
#include "BuyerAndSeller.h"
//#include "Address.h"
//#include "Date.h"
//#include "FeedBack.h"
class System
{
private:
	User** usersArray;
	int logicSizeOfUsersArray, physicSizeOfUsersArray;

public:
	//System() = default;
	System(User** usersArray = NULL, int logicSizeOfUsersArray = 0, int physicSizeOfUsersArray = 1); //constructor
	~System(); //destructor

	void setUsersArray(User** user);
	void setLogicSizeOfUsersArray(int size);
	void setPhysicSizeOfUsersArray(int size);
	
	User** getUsersArray();
	int getLogicSizeOfUsersArray();
	int getPhysicSizeOfUsersArray();

	void systemRun();
	void cleanBuffer();
	int logIn(char* userName, char* passWord, int& index);
	int checkIfUserNameExist(char* userName, int& index);
	bool checkIfUserPasswordCorrect(int index, char* password);

	void addNewBuyer(); //seif 1
	void allocateForNewUser();
	Address* getInfoForNewAllocationOfSellerOrBuyer(char* tempName, char*  tempPassword);
	bool checkIfNameIsTaken(char* name);
	Address addressInfo();

	void addNewSeller(); //seif 2
	
	void addProductToSeller();//seif 3
	Product insertInfoForProduct(Seller* pSeller);

	void addFeedBackToSeller(); //seif 4
	Seller* chooseSellerForFeedBack(Order** orderCart, int &size);
	void createFeedBack(Seller* seller, char* buyerName);
	int searchForProduct(Order** orderCart, int size, char* productName, int&orderIndex);

	void addProductToShoppingCart(); //seif 5
	int searchForSeller(char* name);
	Product searchForProductOfSpecificSeller(char* productName, Seller seller);

	void MakeAnOrder();//seif 6 
	void addChosenProductsToOrder(int shoppingCartSize, Buyer* buyer);
	void removeProductFromShoppingCart(Buyer* buyer, Product** shoppingCart, int shoppingCartSize, Product* product, int index);

	void payForOrder();//seif 7
	void finishOrder(Order* order, Buyer* buyer);

	void showAllBuyers();// seif 8

	void showAllSellers();// seif 9

	void showAllBuyersAndSellers();//seif 10

	void showAllUsersOfCertainType();//seif 11

	void getTheNameOfTheProduct(); //seif 12
	void SearchForProductExistence(char* productName);

	void checkOperators();//seif 13
	void testOperatorCout();
	void testOperatorCompare();



	void operator+=(const Buyer& other);
	void operator+=(const Seller& other);
	void operator+=(const BuyerAndSeller& other);


	//friend std::ostream& operator<<(ostream& os, const Date& date);
	//friend std::ostream& operator<<(ostream& os, const Address& address);
	//friend std::ostream& operator<<(ostream& os, const FeedBack& feedback);
	//friend ostream& operator<<(ostream& os, const Address& address);
	//friend ostream& operator<<(ostream& os, const Date& date);
	//friend ostream& operator<<(ostream& os, const FeedBack& feedback);

};

#endif // !E-CommerceSystem_H
