#include "BuyerAndSeller.h"

BuyerAndSeller::BuyerAndSeller( char* userName,  char* password, Address* address) :User( userName, password,  address),Buyer(userName, password, address),Seller(userName, password, address)//constructor
{
	
}

BuyerAndSeller::BuyerAndSeller(const BuyerAndSeller& other):User(other),Buyer(other),Seller(other)//copy c'tor
{
	
}

BuyerAndSeller::BuyerAndSeller(BuyerAndSeller&& other):User(other), Buyer(other), Seller(other)//move c'tor
{
	
}

BuyerAndSeller::~BuyerAndSeller()
{
	
}
