#include "Order.h"

Order::Order(const char* buyerName, double totalSumCost, Product** productsArray, int logicProductsArraySize , int physicProductsArraySize ) //constructor
{
	if(buyerName!=NULL)
		strcpy(this->buyerName, buyerName);
	this->totalSumCost = totalSumCost;
	this->productsArray = productsArray;
	this->logicProductsArraySize = logicProductsArraySize;
	this->physicProductsArraySize = physicProductsArraySize;
}

Order::Order(const Order& other)//copy c'tor
{	
	this->totalSumCost = other.getTotalSumCost();
	this->productsArray = new Product*[other.getLogicProductsArraySize()];
	for (int i = 0; i < other.getLogicProductsArraySize(); i++)
		this->productsArray[i] = other.getProductsArray()[i];
	this->physicProductsArraySize = other.getPhysicProductsArraySize();
	this->logicProductsArraySize = other.getLogicProductsArraySize();
}

Order::~Order() //destructor
{
	for(int i=0;i<logicProductsArraySize;i++)
		delete productsArray[i];
	delete[]productsArray;
}


void Order::setBuyerName(char* buyerName)
{
	strcpy(this->buyerName, buyerName);
}


void Order::setTotalSumCost(double totalSumCost)
{
	this->totalSumCost = totalSumCost;
}

void Order::setProductsArray(Product** productsArray)
{
	this->productsArray = productsArray;
}

void  Order::setLogicProductsArraySize(int logicProductsArraySize)
{
	this->logicProductsArraySize = logicProductsArraySize;
}

void  Order::setPhysicProductsArraySize(int physicProductsArraySize)
{
	this->physicProductsArraySize = physicProductsArraySize;
}


const char* Order::getBuyerName() const
{
	return buyerName;
}


double Order::getTotalSumCost() const
{
	return totalSumCost;
}

Product** Order::getProductsArray() const
{
	return productsArray;
}

int  Order::getLogicProductsArraySize() const
{
	return logicProductsArraySize;
}

int  Order::getPhysicProductsArraySize() const
{
	return physicProductsArraySize;
}


void Order::addProduct(Product& product)//Add product to order
{	
	allocateProductList();
	if (logicProductsArraySize == 1)
		productsArray = new Product*[physicProductsArraySize];		
	productsArray[logicProductsArraySize - 1] = new Product(product);//copy ctor 
}


void Order::allocateProductList()
{
	int i;
	Product** tempArray;
	if (logicProductsArraySize >= physicProductsArraySize)
	{
		physicProductsArraySize *= 2;
		tempArray = new Product*[physicProductsArraySize];
		for (i = 0; i < logicProductsArraySize; i++)		
			tempArray[i] = new Product(*(this->productsArray[i]));		
		for (i = 0; i < logicProductsArraySize; i++)
			delete productsArray[i];
		delete[]productsArray;
		productsArray = tempArray;
	}
	logicProductsArraySize++;
}

void Order::updateTotalSumCost()//Calculate the cost of order
{
	double sumCost = 0;
	int i;
	double productPrice;
	for (i = 0; i < logicProductsArraySize; i++)
	{
		productPrice = this->productsArray[i]->getPrice();
		sumCost += productPrice;
	}
	this->totalSumCost = sumCost;
}