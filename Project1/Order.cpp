#include "Order.h"

Order::Order(const char* buyerName, double totalSumCost, Array<Product*> productsArray, int logicProductsArraySize, int physicProductsArraySize) //constructor
{
	if (buyerName != NULL)
		strcpy(this->buyerName, buyerName);
	this->totalSumCost = totalSumCost;
	this->productsArray = productsArray;
	//this->logicProductsArraySize = logicProductsArraySize;
	//this->physicProductsArraySize = physicProductsArraySize;
}

Order::Order(const Order& other)//copy c'tor
{
	this->totalSumCost = other.getTotalSumCost();
	this->productsArray = other.productsArray;
	//this->physicProductsArraySize = other.getPhysicProductsArraySize();
	//this->logicProductsArraySize = other.getLogicProductsArraySize();
}

Order::~Order() //destructor
{
	cout << "order destructor!" << endl;
}


void Order::setBuyerName(const char*& buyerName)
{
	strcpy(this->buyerName, buyerName);
}


void Order::setTotalSumCost(double totalSumCost)
{
	this->totalSumCost = totalSumCost;
}

void Order::setProductsArray(Array <Product*> productsArray)
{
	this->productsArray = productsArray;
}
/*
void  Order::setLogicProductsArraySize(const int& logicProductsArraySize)
{
this->logicProductsArraySize = logicProductsArraySize;
}

void  Order::setPhysicProductsArraySize(const int& physicProductsArraySize)
{
this->physicProductsArraySize = physicProductsArraySize;
}

*/
const char* Order::getBuyerName() const
{
	return buyerName;
}

double Order::getTotalSumCost() const
{
	return totalSumCost;
}

Array<Product*> Order::getProductsArray() const
{
	return productsArray;
}

/*
const int&  Order::getLogicProductsArraySize() const
{
return  productsArray.getLogSize;
}

const int&  Order::getPhysicProductsArraySize()
{
return productsArray.getPhysicalSize();
}
*/

void Order::addProduct(Product*& product)//Add product to order
{
	productsArray += product;
}

/*
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
*/

void Order::updateTotalSumCost()//Calculate the cost of order
{
	double sumCost = 0;
	int i, logicProductsArraySize = productsArray.getLogSize();
	//Product* productsArray = dynamic_cast<Product*>(productsArray.getArr());
	for (i = 0; i < logicProductsArraySize; i++)
	{
		//	productPrice = productsArray.getArr()[i]->getPrice();
		//sumCost += productsArray.getArr(i)->getPrice();
		sumCost += productsArray.getArrByIndex(i)->getPrice();
	}
	this->totalSumCost = sumCost;
}