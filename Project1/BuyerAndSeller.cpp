#include "BuyerAndSeller.h"

BuyerAndSeller::BuyerAndSeller( char* userName,  char* password, Address* address) :User( userName, password,  address),Buyer(userName, password, address),Seller(userName, password, address)//constructor
{
	cout << "test ctor buyerandSeller" << endl;

}



BuyerAndSeller::BuyerAndSeller(const BuyerAndSeller& other):User(other),Buyer(other),Seller(other)//copy c'tor
{
	cout << "test copy ctor buyerandSeller" << endl;

}

BuyerAndSeller::BuyerAndSeller(BuyerAndSeller&& other):User(other), Buyer(other), Seller(other)//move c'tor
{
	cout << "test move ctor buyerandSeller" << endl;

}

BuyerAndSeller::~BuyerAndSeller()
{
	cout << "test dtor buyerandSeller" << endl;
}
