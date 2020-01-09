#include "E-CommerceSystem.h"

static void printMenu();
static bool checkChoice(int choice);
static bool checkLettersAndNumbersOnly(char* str);
static bool passwordInCorrectLength(char* pass);
static bool isStrCorrect(char* str);
static bool isLetter(char c);
static bool isHouseNumberLegal(int num);
static void checkDay(int day);
static void checkMonth(int month);
static void checkYear(int year);


System::System(User** usersArray, int logicSizeOfUsersArray, int physicSizeOfUsersArray)//c'tor
{
	this->usersArray = usersArray;
	this->logicSizeOfUsersArray = logicSizeOfUsersArray;
	this->logicSizeOfUsersArray = logicSizeOfUsersArray;
}

System::~System() //destructor
{
	int i;
	for (i = 0; i < this->logicSizeOfUsersArray; i++)
		delete usersArray[i];
	//delete[] usersArray; //we have a problem here
}


void System::setUsersArray(User** user)
{
	this->usersArray = user;//will point to the new array
}

void System::setLogicSizeOfUsersArray(int size)
{
	logicSizeOfUsersArray = size;
}

void System::setPhysicSizeOfUsersArray(int size)
{
	physicSizeOfUsersArray = size;
}


User** System::getUsersArray()
{
	return usersArray;
}

int System::getLogicSizeOfUsersArray()
{
	return logicSizeOfUsersArray;
}

int System::getPhysicSizeOfUsersArray()
{
	return physicSizeOfUsersArray;
}


void System::systemRun()
{
	int choice = 0;
	while (choice != EXIT)
	{
		printMenu();
		cin >> choice;
		cleanBuffer();
		if (!checkChoice(choice)) // check if the choice is legal
		{
			cout << "You must choose an option between 1 to 11" << endl;
			printMenu();
			exit(-1);
		}
		else
		{
			switch (choice)
			{
			case 1:
				addNewBuyer();
				break;
			case 2:
				addNewSeller();
				break;
			case 3:
				addProductToSeller();
				break;
			case 4:
				addFeedBackToSeller();
				break;
			case 5:
				addProductToShoppingCart();
				break;
			case 6:
				MakeAnOrder();
				break;
			case 7:
				payForOrder();
				break;
			case 8:
				showAllBuyers();
				break;
			case 9:
				showAllSellers();
				break;
			case 10:
				getTheNameOfTheProduct();
				break;
			case 11:
				break;
			default:
				break;
			}
		}
	}
}

static void printMenu()
{
	cout << endl << "----------------------------------------------------" << endl;
	cout << "Please choose of the following options: " << endl;
	cout << "To add buyer PRESS 1" << endl;
	cout << "To add seller PRESS 2" << endl;
	cout << "To add product for seller PRESS 3" << endl;
	cout << "To add feedback for seller PRESS 4" << endl;
	cout << "To add product for shopping cart PRESS 5" << endl;
	cout << "To make an order PRESS 6" << endl;
	cout << "To pay for order PRESS 7" << endl;
	cout << "To show all buyers PRESS 8" << endl;
	cout << "To show all sellers PRESS 9" << endl;
	cout << "To search for products PRESS 10" << endl;
	cout << "For EXIT PRESS 11" << endl;
}

static bool checkChoice(int choice)
{
	if (choice >= 1 && choice <= 11)
		return true;
	return false;
}

void System::cleanBuffer()//cleans the buffer from enter etc..
{
	int c;
	do
	{
		c = getchar();
	} while (c != '\n');
}

int System::logIn(char* userName, char* passWord, int& index)//	THE LOGIN FUNCTION WILL RETURN A POINTER TO SELLER OR BUYER WHO IS USING CURRENTLY THE SYSTEM 
{
	cout << "Please enter your user name: " << endl;
	cin.getline(userName, MAX_LENGTH);

	if (checkIfUserNameExist(userName, index) == BUYER)//check if username exist
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect  " << endl;
			return NONE;
		}
		return BUYER;
	}
	else if (checkIfUserNameExist(userName, index) == SELLER)
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect  " << endl;
			return NONE;
		}
		return SELLER;
	}
	else//username dosent exist 
	{
		cout << "Username dosent exist" << endl;
		return NONE;
	}
}

int System::checkIfUserNameExist(char* userName, int& index)//runs on both seller and buyer,checks if the username inserted for log in is right 
{
	int i;
	for (i = 0; i < this->logicSizeOfUsersArray; i++) //check if seller
	{
		if (strcmp(userName, usersArray[i]->getUserName()) == 0)
		{
			index = i;
			return SELLER;
		}
	}

	for (i = 0; i < this->logicSizeOfUsersArray; i++) // check if buyer
	{
		if (strcmp(userName, usersArray[i]->getUserName()) == 0)
		{
			index = i;
			return BUYER;
		}
	}
	return NONE;
}

bool System::checkIfUserPasswordCorrect(int index, char* password)
{
	bool answer = false;
	cout << "Please enter your password: " << endl;
	cin.getline(password, PASSWORD_LENGTH);

	if (index < logicSizeOfUsersArray)
		if (strcmp(usersArray[index]->getPassword(), password) == 0)
			answer = true;
	return answer;
}

void System::addNewBuyer()
{
	char tempName[MAX_LENGTH];
	char tempPassword[PASSWORD_LENGTH];//const
	Address* tempAddress;

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);//copy ctor 
	Buyer tempBuyer(tempName, tempPassword, tempAddress);
	(*this) += tempBuyer;//add buyer to the usersArray
}

void System::allocateForNewUser()
{
	int i;
	User** tempArray;
	if (logicSizeOfUsersArray == physicSizeOfUsersArray)
	{
		physicSizeOfUsersArray *= 2;
		tempArray = new User*[physicSizeOfUsersArray];//c'tor
		for (i = 0; i < logicSizeOfUsersArray; i++)
		{
			if(typeid(this->usersArray[i]) == typeid(Seller))
			tempArray[i] = new Seller(*(this->usersArray[i]));
			if (typeid(this->usersArray[i]) == typeid(Buyer))
				tempArray[i] = new Buyer(*(this->usersArray[i]));
			if (typeid(this->usersArray[i]) == typeid(BuyerAndSeller))
				tempArray[i] = new BuyerAndSeller(*(this->usersArray[i]));
		}
		for (i = 0; i < logicSizeOfUsersArray; i++)
			delete usersArray[i];
		delete[]usersArray;
		usersArray = tempArray;
	}
	logicSizeOfUsersArray++;
}

Address* System::getInfoForNewAllocationOfSellerOrBuyer(char* tempName, char*  tempPassword)
{
	Address* tempAddress;
	cout << "Choose your username, not more than 20 chars: " << endl;
	cin.getline(tempName, MAX_LENGTH);

	while (!checkIfNameIsTaken(tempName) || !checkLettersAndNumbersOnly(tempName))
	{
		cout << "Please enter a different username" << endl;
		cin.getline(tempName, MAX_LENGTH);
	}

	cout << "Please enter your password, must contain exactly 8 characters   " << endl;
	cin.getline(tempPassword, PASSWORD_LENGTH);
	
	while (!passwordInCorrectLength(tempPassword))
	{
		cout << "Password doesnt contain 8 characters, please try again: " << endl;
		cin.getline(tempPassword, PASSWORD_LENGTH);
	}
	tempAddress = new Address(addressInfo());//insert address
	return tempAddress;//returns by ref 
}

bool System::checkIfNameIsTaken(char* name)//checks if the new register can use the username he chose or not.
{
	int i;
	for (i = 0; i < logicSizeOfSellersArray; i++) //check if name is taken by other seller
	{
		if (strcmp(name, sellersArray[i]->getUserName()) == 0)
			return false;
	}
	for (i = 0; i < logicSizeOfBuyersArray; i++) // check if name is taken by other buyer
	{
		if (strcmp(name, buyersArray[i]->getUserName()) == 0)
			return false;
	}
	return true;
}

static bool checkLettersAndNumbersOnly(char* str)
{
	int i, size = strlen(str);
	for (i = 0; i < size; i++)
	{
		if ((str[i] < 48) || (str[i] > 57 && str[i] < 65) || (str[i] > 90 && str[i] < 97) || (str[i] > 122))//checking if there is any char that dosent contain a digit or letter 
			return false;
	}
	cout << endl;
	return true;
}

static bool passwordInCorrectLength(char* pass)
{
	int size = strlen(pass);
	if (size == 8)
		return true;
	return false;
}

Address System::addressInfo()
{
	char country[MAX_LENGTH], city[MAX_LENGTH], street[MAX_LENGTH];
	int houseNumber;

	cout << "Please enter your country: " << endl;
	cin.getline(country, MAX_LENGTH);
	while (!isStrCorrect(country))
	{
		cout << "Country is incorrect, please enter again " << endl;
		cin.getline(country, MAX_LENGTH);
	}

	cout << "Please enter your City: " << endl;
	cin.getline(city, MAX_LENGTH);
	while (!isStrCorrect(city))
	{
		cout << "City is incorrect, please enter again " << endl;
		cin.getline(city, MAX_LENGTH);
	}

	cout << "Please enter your street: " << endl;
	cin.getline(street, MAX_LENGTH);
	while (!isStrCorrect(street))
	{
		cout << "Street is incorrect, please enter again " << endl;
		cin.getline(street, MAX_LENGTH);
	}

	cout << "Please enter your house number:" << endl;
	cin >> houseNumber;
	while (!isHouseNumberLegal(houseNumber))
	{
		cout << "House number is incorrect, please enter again " << endl;
		cin >> houseNumber;
	}
	return Address(country, city, street, houseNumber);
}

static bool isStrCorrect(char* str)
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

static bool isLetter(char c)
{
	if ((c > 64 && c < 91) || (c > 96) && (c < 123)) // c is capital letter or small letter
		return true;
	return false;
}

static bool isHouseNumberLegal(int num)
{
	if (num <= 0)
		return false;
	return true;
}


void System::addNewSeller()
{
	char tempName[MAX_LENGTH];
	char tempPassword[PASSWORD_LENGTH];
	Address* tempAddress;

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);
	allocateForNewSeller();
	if (logicSizeOfSellersArray == 1)//allocate
		sellersArray = new Seller*[physicSizeOfSellersArray];
	sellersArray[logicSizeOfSellersArray - 1] = new Seller(tempName, tempPassword, tempAddress);//ctor of seller
}

void System::allocateForNewSeller()
{
	int i;
	Seller** tempArray;
	if (logicSizeOfSellersArray == physicSizeOfSellersArray)
	{
		physicSizeOfSellersArray *= 2;
		tempArray = new Seller*[physicSizeOfSellersArray];//c'tor
		for (i = 0; i < logicSizeOfSellersArray; i++)
			tempArray[i] = new Seller(*(this->sellersArray[i]));
		for (i = 0; i < logicSizeOfSellersArray; i++)
			delete sellersArray[i];
		delete[]sellersArray;
		sellersArray = tempArray;
	}
	logicSizeOfSellersArray++;
}


void System::addProductToSeller() // seif 3
{
	char userName[MAX_LENGTH];
	char passWord[PASSWORD_LENGTH];
	int indexOfSeller;
	int connected;
	connected = logIn(userName, passWord, indexOfSeller);
	if (connected == BUYER  )	
		cout << "Only seller can add new Product !" << endl;
	else if (connected == SELLER)//connected to seller 
	{
		Product product = Product(insertInfoForProduct(sellersArray[indexOfSeller]));
		sellersArray[indexOfSeller]->AddToProductList(product);
	}	
}

Product System::insertInfoForProduct(Seller* pSeller)
{
	char name[MAX_LENGTH];
	int category;
	double price;
	cout << "Please enter name for product: " << endl;
	cin.getline(name, MAX_LENGTH);
	cout << "Please choose product category: "<< endl << "for children press 0 " << endl << "for Electricty press 1" << endl << "for Clothing press 2 " << endl << "for  Office press 3 " << endl;
	cin >> category;
	cout << "Please enter the price of the product: " << name << endl;
	cin >> price;
	return (Product (name, Product::eCategory(category), price, pSeller));//returns as product--ctor
}


void System::addFeedBackToSeller() //seif 4
{
	char userName[MAX_LENGTH];
	char password[PASSWORD_LENGTH];
	int indexOfBuyer;
	int logSizeofOrderCart, i;
	Order** orderCart;
	int connected = logIn(userName, password, indexOfBuyer);

	if (connected == NONE)
		cout << "Could not log In" << endl;
	else if (connected == SELLER)
		cout << "Only Buyer can add feedback !" << endl;
	else
	{
		logSizeofOrderCart = this->buyersArray[indexOfBuyer]->getLogSizeOfOrderCart();
		orderCart = new Order*[logSizeofOrderCart];
		for (i = 0; i < logSizeofOrderCart; i++)
		{
			orderCart[i] = buyersArray[indexOfBuyer]->GetOrderCart()[i];
		}
		Seller* seller = chooseSellerForFeedBack(orderCart, logSizeofOrderCart);
		if (seller != NULL)
			createFeedBack(seller, userName);
	}
}

Seller* System::chooseSellerForFeedBack(Order** orderCart, int& size)
{
	int orderIndex;
	Product** productList;
	char productName[MAX_LENGTH];
	cout << "Please enter the name of the product for feedback: " << endl;
	cin.getline(productName, MAX_LENGTH);

	int productIndex = searchForProduct(orderCart, size, productName, orderIndex);
	if (productIndex != NONE)
	{
		productList = new Product*[orderCart[orderIndex]->getPhysicProductsArraySize()];
		productList = orderCart[orderIndex]->getProductsArray();
		return productList[productIndex]->getSeller();
	}
	return NULL;
}

int System::searchForProduct(Order** orderCart, int size, char* productName, int& orderIndex)
{
	int i, j, sizeOfProductArray;
	for (i = 0; i < size; i++)
	{
		sizeOfProductArray = orderCart[i]->getLogicProductsArraySize();
		for (j = 0; j < sizeOfProductArray; j++)
		{
			if (strcmp(orderCart[i]->getProductsArray()[j]->getName(), productName) == 0)
			{
				orderIndex = i;
				return j;
			}
		}
	}
	return NONE;
}

void System::createFeedBack(Seller* seller, char* buyerName)
{
	char message[MAX_FEEDBACK_LENGTH];
	Date date;
	int day, month, year;

	cout << "Please enter today's date: " << endl;
	cout << "Day: ";
	cin >> day;
	checkDay(day);

	cout << endl << "Month: ";
	cin >> month;
	checkMonth(month);

	cout << endl << "Year: ";
	cin >> year;
	checkYear(year);

	date = Date(day, month, year);

	cout << endl << "Please enter your feedback: " << endl;
	cleanBuffer();
	cin.getline(message, MAX_FEEDBACK_LENGTH);

	FeedBack feedback(buyerName, date, message);
	seller->addFeedbackToSeller(feedback);
}

static void checkDay(int day)
{
	while (day < 1 || day > 31)
	{
		cout << "Day is not legal, please enter again" << endl;
		cin >> day;
	}
}

static void checkMonth(int month)
{
	while (month < 1 || month > 12)
	{
		cout << "Month is not legal, please enter again" << endl;
		cin >> month;
	}
}

static void checkYear(int year)
{
	while (year <2000 || year > 2020)
	{
		cout << "Year is not legal, please enter again" << endl;
		cin >> year;
	}
}


void System::addProductToShoppingCart()//seif 5
{
	char userName[MAX_LENGTH];
	char passWord[PASSWORD_LENGTH];
	int indexOfBuyer;
	char SellerName[MAX_LENGTH];
	Product *product;
	int indexOfSeller, connected;
	char productName[MAX_LENGTH];

	connected = logIn(userName, passWord, indexOfBuyer);
	if (connected == NONE)	
		cout << "Could not connect to your account" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can add products to his shopping cart ! " << endl;
	else
	{
		cout << "Please enter the name of the seller: " << endl;
		cin.getline(SellerName, MAX_LENGTH);
		cout << "Please enter the name of the product: " << endl;
		cin.getline(productName, MAX_LENGTH);

		indexOfSeller = searchForSeller(SellerName);
		if (indexOfSeller != NONE)
		{
			product = new Product(searchForProductOfSpecificSeller(productName, *(sellersArray[indexOfSeller])));
			this->buyersArray[indexOfBuyer]->AddToShoppingCart(*product);//adding the product to the exact buyer who is currently using the system(logged In)
			delete product;
		}
	}
}

int System::searchForSeller(char* name)
{
	int index = NONE;
	for (int i = 0; i < logicSizeOfSellersArray; i++)
	{

		if (strcmp(name, this->sellersArray[i]->getUserName()) == 0)
			index = i;
	}
	if (index == NONE)
		cout << "There is no such seller" << endl;

	return index;
}

Product System::searchForProductOfSpecificSeller(char* productName, Seller seller)
{
	int index = -1;
	Product **productList = seller.getListOfProducts();

	for (int i = 0; i < seller.getLogListProductSize(); i++)
		if (strcmp(productList[i]->getName(), productName) == 0)
			index = i;
	if (index == -1)
	{
		cout << "No such product exist in the cart of this seller " << endl;
		exit(-1);
	}

	return *(productList[index]);
}


void System::MakeAnOrder()//seif 6
{
	char userName[MAX_LENGTH];
	char passWord[PASSWORD_LENGTH];
	int indexOfBuyer, sizeOfShoppingCart;
	int connected;
	Product** ShoppingCart;

	connected = logIn(userName, passWord, indexOfBuyer);//connect to the system as Buyer
	if (connected == NONE)
		cout << "Could not log in" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can make an order! " << endl;
	else
	{
		sizeOfShoppingCart = this->buyersArray[indexOfBuyer]->getLogSizeOfShoppingCart();
		if (sizeOfShoppingCart == 0)
			cout << "No products in shopping cart" << endl;
		else if (this->buyersArray[indexOfBuyer]->getOrder() != NULL)
			cout << "The last order is not completed" << endl;
		else
		{
			ShoppingCart = buyersArray[indexOfBuyer]->getShoppingCart();
			addChosenProductsToOrder(sizeOfShoppingCart, buyersArray[indexOfBuyer]);
		}
	}
}

void System::addChosenProductsToOrder(int shoppingCartSize, Buyer* buyer)
{
	int i;
	bool answer;
	Order* tempOrder;
	Product** shoppingCart;
	if (buyer->getOrder() == NULL)
	{
		tempOrder = new Order(buyer->getUserName());
		buyer->setOrder(tempOrder);//allocate
	}
	for (i = 0; i < shoppingCartSize; i++)
	{
		shoppingCart = buyer->getShoppingCart();//updates every run
		cout << "The product is : " << shoppingCart[i]->getName() << endl << "Would you like to add it to your order ?" << endl << "Press 1 for yes, 0 for no " << endl;
		cin >> answer;
		if (answer == true)
		{
			(*buyer).getOrder()->addProduct(*(shoppingCart[i]));
			removeProductFromShoppingCart(buyer, shoppingCart, shoppingCartSize, shoppingCart[i], i);
			cout << "Product added" << endl;
			shoppingCartSize--;
			i--;
		}
		cout << shoppingCartSize << endl;
	}
}

void System::removeProductFromShoppingCart(Buyer* buyer, Product** shoppingCart, int shoppingCartSize, Product* product, int index)
{
	Product** tempShoppingCart = new Product*[shoppingCartSize + 15];
	int i;
	for (i = 0; i < shoppingCartSize; i++)
	{
		if (i < index)
			tempShoppingCart[i] = new Product(*(shoppingCart[i]));
		else if (i > index)
			tempShoppingCart[i - 1] = new Product(*(shoppingCart[i]));
	}
	for (i = 0; i < shoppingCartSize; i++)
		delete shoppingCart[i];
	delete[] shoppingCart;
	buyer->setShoppingCart(tempShoppingCart);
	buyer->setLogSizeOfShoppingCart(shoppingCartSize - 1);
}


void System::payForOrder() //seif 7
{
	char userName[MAX_LENGTH];
	char passWord[PASSWORD_LENGTH];
	int indexOfBuyer;
	int connected;
	Order* order;

	connected = logIn(userName, passWord, indexOfBuyer);//connect to the system as Buyer
	if (connected == NONE)
		cout << "Could not log in" << endl;
	else if (connected == SELLER)
		cout << "Only buyer can make an order! " << endl;
	else
	{
		order = buyersArray[indexOfBuyer]->getOrder();
		if (order != NULL)
			finishOrder(order, buyersArray[indexOfBuyer]);
	}
}

void System::finishOrder(Order* order, Buyer* buyer)
{
	double sumCost, inputCost;

	order->updateTotalSumCost();
	sumCost = order->getTotalSumCost();

	cout << "The total sum cost of order is: " << sumCost << " please enter the amount needed" << endl;
	cin >> inputCost;
	if (inputCost >= sumCost)
	{
		buyer->AddToOrderCart(order);
		buyer->setOrder(NULL);
	}
	else
		cout << "Insufficent funds, order has not been completed " << endl;
}


void System::showAllBuyers()//seif 8
{
	if (this->logicSizeOfBuyersArray == 0)
		cout << "No buyers" << endl;
	for (int i = 0; i < this->logicSizeOfBuyersArray; i++)
		cout << "Username number :" << i + 1 << "'s buyer is :" << this->buyersArray[i]->getUserName() << " and his password is : " << this->buyersArray[i]->getPassword() << endl;
}


void System::showAllSellers()//seif 9 
{
	if (this->logicSizeOfSellersArray == 0)
		cout << "No sellers" << endl;
	for (int i = 0; i < this->logicSizeOfSellersArray; i++)
		cout << "Username number :" << i + 1 << "'s seller is :" << this->sellersArray[i]->getUserName() << " and his password is : " << this->sellersArray[i]->getPassword() << endl;
}


void System::getTheNameOfTheProduct()// seif 10
{
	char productName[MAX_LENGTH];

	cout << "enter the name of the product you are searching for : " << endl;
	cin.getline(productName, MAX_LENGTH);
	SearchForProductExistence(productName);
}

void System::SearchForProductExistence(char* productName) 
{
	for (int i = 0; i < this->logicSizeOfSellersArray; i++)
	{
		Product** productListTemp = new Product*[this->sellersArray[i]->getPhysicListProductSize()];
		productListTemp = this->sellersArray[i]->getListOfProducts();
		for (int j = 0; j < this->sellersArray[i]->getLogListProductSize(); j++)
		{
			if (strcmp(productName, productListTemp[j]->getName()) == 0)//checks if found a product with the exact name 
				cout << "The Seller number is : " << i + 1 << ", which his name is: " << this->sellersArray[i]->getUserName() << " has the product !" << endl;
			else
				cout << "The product has not been found" << endl;
		}
	}
}



void System::operator+=(const Buyer& other)//might be a prob because of & 
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->getUsersArray[logicSizeOfUsersArray - 1] = other;
}

void System::operator+=(const Seller*& other)
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->getUsersArray[logicSizeOfUsersArray - 1] = other;
}

void System::operator+=(const BuyerAndSeller*& other)
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->getUsersArray[logicSizeOfUsersArray - 1] = other;
}
