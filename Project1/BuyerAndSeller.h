#ifndef BuyerAndSeller_H
#define BuyerAndSeller_H

#include "Buyer.h"
#include "Seller.h"

class BuyerAndSeller : public Buyer, public Seller
{
public:
	BuyerAndSeller( char* userName, char* password,  Address* address);//constructor
	BuyerAndSeller(const BuyerAndSeller& other);//copy c'tor
	//we should do move ctor?
	//dont think we need to make our own destructor --- it will be default?
	
	BuyerAndSeller(BuyerAndSeller&& other);//move c'tor
	~BuyerAndSeller();//gonna be VIRTUAL !!!! ???????
	
};

#endif // ! BuyerAndSeller_H
