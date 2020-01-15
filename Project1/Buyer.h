#ifndef Buyer_H
#define Buyer_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Address.h"
#include "product.h"
#include "Order.h"
#include "User.h"

class Buyer: virtual public User
{
private:
	Order* order;
	Order** orderCart;//array of Past Orders of the buyer 
	Product** shoppingCart;//array of products
	int logSizeOfShoppingCart, physicSizeOfShoppingCart;
	int logSizeOfOrderCart, physicSizeOfOrderCart;

public:
	Buyer(char* userName, char* password, Address* address, Order* order = NULL, Order** orderCart = NULL, Product** shoppingCart = NULL, int logSizeOfShoppingCart = 0, int physicSizeOfShoppingCart = 1, int logSizeOfOrderCart = 0, int  physicSizeOfOrderCart = 1);//c'tor default  --zero all
	Buyer(const Buyer& other);//copy c'tor 
	Buyer(Buyer&& other);//move c'tor 
	~Buyer();//destructor

	void setOrder(Order* order);
	void setOrderCart(Order** orderCart);
	void setLogSizeOfOrderCart(int logSizeOfOrderCart);
	void setPhysicSizeOfOrderCart(int physicSizeOfOrderCart);
	void setShoppingCart(Product** shoppingCart);
	void setLogSizeOfShoppingCart(int logSizeOfShoppingCart);
	void setPhysicSizeOfShoppingCart(int physicSizeOfShoppingCart);

	Order* getOrder();
	Order** GetOrderCart();//shows the list of everything youve got in the cart, Once you choose an item in the cart it will ask you how many of that item would you like , once you choose it , it will be added to the sum that you need to pay , and the item will be deleted from the list
	int getLogSizeOfOrderCart() const;
	int getPhysicSizeOfOrderCart() const;
	Product** getShoppingCart();
	int getLogSizeOfShoppingCart() const;
	int getPhysicSizeOfShoppingCart() const;

	void AddToShoppingCart(Product &  newProduct);
	void allocateShoppingCart();
	void AddToOrderCart(Order* newOrder);
	void allocateOrderCart();
	
	const bool operator>(const Buyer& other);//comparing
};

#endif // !Buyer_H