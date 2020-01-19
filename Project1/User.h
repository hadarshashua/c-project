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


	friend  ostream& operator<< (ostream& out, const User& user)
	{
		if (typeid(out) == typeid(ofstream))
			out << user.userName << " " << user.password << " " << *(user.address);
		else
			out << "User name: " << user.userName << "\n Password: " << user.password << "\n Address: " << *(user.address) << endl;
		return out;
	}

	friend  istream& operator>> (istream& in, User& user)
	{
		if (typeid(in) == typeid(ifstream))
			in >> user.userName >> user.password >> *(user.address);
		else//typeid(in)==typeid(ostream)
		{
			char delimiter;
			in >> user.userName >> user.password >> delimiter>> *(user.address);
		}
			return in;
	}
};

#endif // !User_H
