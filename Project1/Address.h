#ifndef Address_H
#define Address_H
#pragma warning(disable : 4996)
#include "Definitions.h"
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;


class Address
{
private:
	char country[MAX_LENGTH];
	char city[MAX_LENGTH];
	char street[MAX_LENGTH];
	int houseNumber;
public:
	Address(char* country, char* city, char* street, int houseNumber); //constructor
	Address(const Address& other); //copy c'tor
	Address(Address&& other); //move c'tor
	
	bool setCountry(char* country);
	bool setCity(char* city);
	bool setStreet(char* street);
	bool setHouseNumber(int houseNumber);

	const char* getCountry() const;
	const char* getCity() const;
	const char* getStreet() const;
	int getHouseNumber()const;

	friend ostream& operator<<(ostream& out, const Address& address)
	{
		if (typeid(out) == typeid(ofstream))
			out << address.country << " " << address.city << " " << address.street << " " << address.houseNumber;
		else
			out << "Country: " << address.country << "\n City: " << address.city << "\n Street: " << address.street << "\n House number: " << address.houseNumber << endl;
		return out;
	}

	friend  istream& operator>> (istream& in, Address& address)
	{
//		char delimiter;
		in >> address.country >> address.city >> address.street >> address.houseNumber;
		return in;
	}
};

#endif // !Address_H