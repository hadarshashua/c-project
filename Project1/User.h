#ifndef User_H
#define User_H
#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Address.h"
#include "Definitions.h"

class User
{
private:
	char userName[MAX_LENGTH];
	char password[PASSWORD_LENGTH];
	Address* address;// by pointer

public:
	User(const char* userName, const char* password, const Address* address);//constructor
	User(const User& Other);//copy c'tor
	User(User&& Other);//move c'tor
	virtual ~User();//destructor---virtual to activate aswell d'tor of buyer or and seller 

	bool setUserName(const char* name);
	bool setPassword(const char* password);
	void setAddress(Address& address);

	const char* getUserName() const;
	const char* getPassword() const;
	Address* getAddress() const;

	//virtual const Buyer& operator>(const Buyer& other) = 0;//comparing between two buyers cart-using virtual to move to the operator in the Buyer class 
	//virtual const Buyer& operator+=(const Buyer& other)=0;//add buyer in array--need to check if its zero or something else 
	//virtual Seller* operator+=(const Seller& other)=0;//add seller in array 
};

#endif // !User_H
