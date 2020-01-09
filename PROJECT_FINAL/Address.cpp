#include "Address.h"

static bool isStrCorrect(char* str);
static bool isLetter(char c);

Address::Address(char* country, char* city, char* street, int houseNumber) // constructor
{
	Address::setCountry(country);
	Address::setCity(city);
	Address::setStreet(street);
	Address::setHouseNumber(houseNumber);
}

Address::Address(const Address& other) //copy c'tor
{
	strcpy(this->country, other.getCountry());
	strcpy(this->city, other.getCity());
	strcpy(this->street, other.getStreet());
	this->houseNumber = other.getHouseNumber();
}

Address::Address(Address&& other) //move ctor
{
	strcpy(this->country, other.getCountry());
	strcpy(this->city, other.getCity());
	strcpy(this->street, other.getStreet());
	this->houseNumber = other.getHouseNumber();
}


bool Address::setCountry(char* country)
{
	if (!isStrCorrect(country)) // The country name is illegal
		return false;
	strcpy(this->country, country);
	return true;
}

bool Address::setCity(char* city)
{
	if (!isStrCorrect(city)) // The city name is illegal	
		return false;
	strcpy(this->city, city);
	return true;
}

bool Address::setStreet(char* street)
{
	if (!isStrCorrect(street)) // The street name is illegal	
		return false;
	strcpy(this->street, street);
	return true;
}

bool Address::setHouseNumber(int houseNumber)
{
	if (houseNumber <= 0) // The house number is illegal
		return false;
	this->houseNumber = houseNumber;
	return true;
}

const char* Address::getCountry() const
{
	return country;
}

const char* Address::getCity() const
{
	return city;
}

const char* Address::getStreet() const
{
	return street;
}

int Address::getHouseNumber() const
{
	return houseNumber;
}


bool isStrCorrect(char* str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (!isLetter(str[i]))
			return false;
		i++;
	}
	return true;
}

bool isLetter(char c)
{
	if ((c > 64 && c < 91) || (c > 97) && (c < 123)) // c is capital letter or small letter
		return true;
	return false;
}