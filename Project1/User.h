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
	User(char* userName, const char* password, Address* address);//constructor
	User(const User& Other);//copy c'tor
	User(User&& Other);//move c'tor
	virtual ~User();

	bool setUserName(const char* name);
	bool setPassword(const char* password);
	void setAddress(Address& address);

	const char* getUserName() const;
	const char* getPassword() const;
	Address* getAddress() const;
};

#endif // !User_H
