#include "User.h"

static bool checkLettersAndNumbersOnly(char* str);
static bool userNameAboveMinSize(char* name);
static bool passwordInCorrectLength(char* pass);

User::User(const char* userName, const char* password, const Address* address)//constructor
{
	strcpy(this->userName, userName);
	strcpy(this->password, password);
	this->address = new Address(*address);
}

User::User(const User& other)//copy c'tor
{
	strcpy(this->userName, other.userName);//copying Other username
	strcpy(this->password, other.password);//copying Other password
	this->address = new Address(*other.address);//copy c'tor 
}

User::User(User&& other)//move c'tor
{
	strcpy(this->userName, other.userName);
	other.setUserName(NULL);
	strcpy(this->password, other.password);
	other.setPassword(NULL);

	this->address = other.address;//will point to other.address -by pointer 
	other.address = NULL;
}

User::~User()//destructor
{
	delete address;
}


bool User::setUserName(const char* name) 
{
	if (checkLettersAndNumbersOnly(name) && userNameAboveMinSize(name)) //checks that the name is right by the rules
	{
		strcpy(userName, name);
		return true;
	}
	return false; //Didnt pass the check (and the dinamic string (TempPassWord) will be released)
}

bool User::setPassword(const char* password)
{
	if (checkLettersAndNumbersOnly(password) && passwordInCorrectLength(passWord)) //checks that the password is right by the rules
	{
		strcpy(this->password, passWord);
		return true;
	}
	return false; //Didnt pass the check (and the dinamic string (TempPassWord) will be released afterwards)
}

void User::setAddress(Address& address)
{
	this->address = new Address(address);//will point to the new address
}

const char* User::getUserName() const
{
	return userName;
}

const char* User::getPassword() const
{
	return password;
}

Address* User::getAddress() const
{
	return address;
}


static bool checkLettersAndNumbersOnly(const char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 48) || (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 97) || (str[i] > 122))//checking if there is any char that dosent contain a digit or letter 
			return false;
	}
	return true;
}

static bool userNameAboveMinSize(const char* name)
{
	int size = strlen(name);
	if (size >= 6)
		return true;
	return false;
}

static bool passwordInCorrectLength(const char* pass)
{
	int size = strlen(pass);
	if (size == 8)
		return true;
	return false;
}



void operator+=(const Buyer* other, User** usersArray, int logSize);