#include "Seller.h"

static bool checkLettersAndNumbersOnly(char* name);
static bool userNameAboveMinSize(char* name);
static bool passwordInCorrectLength(char* pass);


Seller::Seller(char* userName, char* password, Address* address, FeedBack** feedBackArray, Product** listOfProducts, int logListProductSize, int physicListProductSize, int logSizeOfFeedbackArray, int physicSizeOfFeedbackArray) : User(userName, password, address)//constructor
{
	this->feedbackArray = feedBackArray;
	this->listOfProducts = listOfProducts;
	this->logListProductSize = logListProductSize;
	this->physicListProductSize = physicListProductSize;
	this->logSizeOfFeedbackArray = logSizeOfFeedbackArray;
	this->physicSizeOfFeedbackArray = physicSizeOfFeedbackArray;	
}

Seller::Seller(const Seller& other) : User(other)//copy ctor
{
	this->feedbackArray = new FeedBack*[other.getLogSizeOfFeedbackArray()];// c'tor of feedBack
	for (int i = 0; i < other.getLogSizeOfFeedbackArray(); i++)
		this->feedbackArray[i] = new FeedBack(*(other.feedbackArray[i]));//copy ctor 

	this->listOfProducts = new Product*[other.getLogListProductSize()];//copy List
	for (int i = 0; i < other.getLogListProductSize(); i++)
		this->listOfProducts[i] = new Product(*(other.listOfProducts[i]));

	this->logListProductSize = other.getLogListProductSize();
	this->physicListProductSize = other.getPhysicListProductSize();

	this->logSizeOfFeedbackArray = other.getLogSizeOfFeedbackArray();
	this->physicSizeOfFeedbackArray = other.getPhysicSizeOfFeedbackArray();
}

Seller::Seller(Seller&& other) : User(other)//move c'tor
{
	feedbackArray = other.feedbackArray;
	other.feedbackArray = NULL;

	listOfProducts = other.listOfProducts;
	other.listOfProducts = NULL;

	logListProductSize = other.logListProductSize;
	physicListProductSize = other.physicListProductSize;

	logSizeOfFeedbackArray = other.logSizeOfFeedbackArray;
	physicSizeOfFeedbackArray = other.physicSizeOfFeedbackArray;
}

Seller:: ~Seller()//destructor
{
	for (int i = 0; i<this->logSizeOfFeedbackArray; i++)
		delete feedbackArray[i];
	delete[]feedbackArray;
	for (int i = 0; i<this->logListProductSize; i++)
		delete listOfProducts[i];
	delete[]listOfProducts;
}


void Seller::setFeedbackArray(FeedBack** feedBackArray, int& logSize)
{

	this->feedbackArray = new FeedBack*[logSize];
	for (int i = 0; i < logSize; i++)
		this->feedbackArray[i] = new FeedBack(*(feedBackArray[i]));//copy ctor 
	physicSizeOfFeedbackArray = logSize;
}

void Seller::setListOfProducts(Product** productArray, int& logSize)
{
	this->listOfProducts = new Product*[logSize];
	for (int i = 0; i < logSize; i++)
	{
		this->listOfProducts[i] = new Product(*(productArray[i]));//copy c'tor 
	}

	physicListProductSize = logSize;
}

void Seller::setLogListProductSize(int logListProductSize)
{
	this->logListProductSize = logListProductSize;
}

void Seller::setPhysicListProductSize(int physicListProductSize)
{
	this->physicListProductSize = physicListProductSize;
}

void Seller::setLogSizeOfFeedbackArray(int logSizeOfFeedbackArray)
{
	this->logSizeOfFeedbackArray = logSizeOfFeedbackArray;
}

void Seller::setPhysicSizeOfFeedbackArray(int physicSizeOfFeedbackArray)
{
	this->physicSizeOfFeedbackArray = physicSizeOfFeedbackArray;
}


FeedBack** Seller::getFeedbackArray()
{
	return feedbackArray;
}

Product** Seller::getListOfProducts()
{
	return listOfProducts;
}

int Seller::getLogListProductSize() const
{
	return logListProductSize;
}

int Seller::getPhysicListProductSize() const
{
	return physicListProductSize;
}

int Seller::getLogSizeOfFeedbackArray() const
{
	return logSizeOfFeedbackArray;
}

int Seller::getPhysicSizeOfFeedbackArray() const
{
	return physicSizeOfFeedbackArray;
}


void Seller::AddToProductList(Product newProduct)
{
	allocateProductArray();
	if (logListProductSize == 1)
		this->listOfProducts = new Product*[physicListProductSize];
	listOfProducts[logListProductSize - 1] = new Product(newProduct);
}

void Seller::allocateProductArray()
{
	int i;
	Product** TempProductList;
	if (logListProductSize >= physicListProductSize)
	{
		physicListProductSize *= 2;
		TempProductList = new Product*[physicListProductSize];
		for (i = 0; i < logListProductSize; i++)
			TempProductList[i] = new Product(*(listOfProducts[i]));//copy c'tor 
		for (i = 0; i < logListProductSize; i++)
			delete listOfProducts[i];
		delete[]listOfProducts;
		listOfProducts = TempProductList;
	}
	logListProductSize++;
}


void Seller::allocateForNewFeedback()
{
	int i;
	FeedBack** tempArray;
	if (logSizeOfFeedbackArray >= physicSizeOfFeedbackArray)
	{
		physicSizeOfFeedbackArray *= 2;
	    tempArray = new FeedBack*[physicSizeOfFeedbackArray];
		for (i = 0; i < logSizeOfFeedbackArray; i++)
			tempArray[i] = new FeedBack(*(feedbackArray[i]));
		for (i = 0; i< logSizeOfFeedbackArray; i++)
			delete feedbackArray[i];
		delete[]feedbackArray;
		feedbackArray = tempArray;
	}
	logSizeOfFeedbackArray++;
}

void Seller::addFeedbackToSeller(FeedBack feedback)
{
	allocateForNewFeedback();
	if (logSizeOfFeedbackArray == 1)
		this->feedbackArray = new FeedBack*[physicSizeOfFeedbackArray];
	feedbackArray[logSizeOfFeedbackArray - 1] = new FeedBack(feedback);
}
