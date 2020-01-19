#include "product.h"
int Product::counter = 0;

Product::Product(char* name, eCategory category, double& price, Seller*& seller)//constructor
{
	if (name)//!=NULL
		strcpy(this->name, name);
	this->category = category;
	this->price = price;
	serial_number = ++counter;
	this->seller = seller;
}

Product::Product(const Product& other)//copy c'tor
{
	strcpy(this->name, other.name);
	this->category = other.category;
	this->price = other.price;
	this->serial_number = other.serial_number;
	this->seller = other.seller;//will point to the same seller	
}

Product::~Product() //destructor
{
	
	seller = NULL;	
}


void Product::setName(char* name)
{
	strcpy(this->name, name);
}

void Product::setCategory(Product::eCategory category)
{
	this->category = category;
}

void Product::setPrice(double price)
{
	this->price = price;
}


const char* Product::getName() const
{
	return name;
}

bool Product::setSeller(Seller* Seller)
{
	if (Seller == NULL)
		return false;
	this->seller = Seller;
	return true;
}


Product::eCategory Product::getCategory() const
{
	return category;
}

double Product::getPrice() const
{
	return price;
}

int Product::getSerialNumber() const
{
	return serial_number;
}

Seller* Product::getSeller() const 
{
	return this->seller;
}


const Product& Product:: operator=(const Product& other)
{
	if (this != &other)
	{
		strcpy(this->name, other.name);
		this->category = other.category;
		this->price = other.price;
		this->serial_number = other.serial_number;
		this->seller = other.seller;
		this->counter = other.counter;
	}
	return *this;
}