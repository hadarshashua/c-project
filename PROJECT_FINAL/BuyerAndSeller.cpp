#include "BuyerAndSeller.h"

BuyerAndSeller::BuyerAndSeller(const Buyer& buyer,const Seller& seller) : User(buyer.getUserName(), buyer.getPassword(), buyer.getAddress()), Buyer(buyer), Seller(seller)//constructor
{

}

BuyerAndSeller::BuyerAndSeller(const BuyerAndSeller& other):User(other),Buyer(other),Seller(other)//copy c'tor
{

}
/*
BuyerAndSeller::BuyerAndSeller(BuyerAndSeller&& other)//move c'tor
{

}

BuyerAndSeller::~BuyerAndSeller()
{

}
*/