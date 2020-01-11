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
	this->physicSizeOfUsersArray = physicSizeOfUsersArray;
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
			cout << "You must choose an option between 1 to 14" << endl;
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
				showAllBuyersAndSellers();
				break;
			case 11:
				showAllUsersOfCertainType();
				break;
			case 12:
				getTheNameOfTheProduct();
				break;
			case 13:
				checkOperators();
				break;
			case 14:
				break;//for exit
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
	cout << "To show all buyers and sellers PRESS 10" << endl;
	cout << "To show all users of certain type PRESS 11" << endl;
	cout << "To search for products PRESS 12" << endl;
	cout << "To check operators press 13 " << endl;
	cout << "For EXIT PRESS 14" << endl;
}

static bool checkChoice(int choice)//check this
{
	if (choice >= 1 && choice <= 14)
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
	else if (checkIfUserNameExist(userName, index) == BUYER_AND_SELLER)
	{
		if (!checkIfUserPasswordCorrect(index, passWord))
		{
			cout << "Password is incorrect  " << endl;
			return NONE;
		}
		return BUYER_AND_SELLER;
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
			if (typeid(this->usersArray[i]) == typeid(Buyer))
				return BUYER;
			else if (typeid(this->usersArray[i]) == typeid(Seller))
				return SELLER;
			else
				return BUYER_AND_SELLER;
		}
		return NONE;
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
	int onlyBuyer = 0;
	char tempName[MAX_LENGTH];
	char tempPassword[PASSWORD_LENGTH];//const
	Address* tempAddress;

	cout << "If you want to be also seller press 0, else press 1" << endl;
	cin >> onlyBuyer;//problem here we dont get the username!!!!!!!!! FIXED
	cleanBuffer();

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);//copy ctor
	if (!onlyBuyer)
	{//DOSENT WORK 
		BuyerAndSeller tempBuyerSeller(tempName, tempPassword, tempAddress);
		(*this) += tempBuyerSeller;//add buyer and seller to the usersArray---DOSENT WORK 
	}
	else
	{
		Buyer tempBuyer(tempName, tempPassword, tempAddress);
		(*this) += tempBuyer;//add buyer to the usersArray
	}
	
}

void System::allocateForNewUser()
{
	int i;
	User** tempArray;
	if (logicSizeOfUsersArray >= physicSizeOfUsersArray)
	{
		physicSizeOfUsersArray *= 2;
		tempArray = new User*[physicSizeOfUsersArray];//c'tor
		for (i = 0; i < logicSizeOfUsersArray; i++)
		{
			if(typeid(this->usersArray[i]) == typeid(Seller))
				tempArray[i] = new Seller(*((Seller**)usersArray)[i]);
			if (typeid(this->usersArray[i]) == typeid(Buyer))
				tempArray[i] = new Buyer(*((Buyer**)usersArray)[i]);
			if (typeid(this->usersArray[i]) == typeid(BuyerAndSeller))
				tempArray[i] = new BuyerAndSeller(*((BuyerAndSeller**)usersArray)[i]);
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
	for (i = 0; i < logicSizeOfUsersArray; i++) //check if name is taken by other user
	{
		if (strcmp(name, usersArray[i]->getUserName()) == 0)
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
	if (size == PASSWORD_LENGTH-1)
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
	int onlySeller = 0;
	char tempName[MAX_LENGTH];
	char tempPassword[PASSWORD_LENGTH];
	Address* tempAddress;

	cout << "If you want to be also buyer press 0, else press 1" << endl;
	cin >> onlySeller;
	cleanBuffer();

	tempAddress = getInfoForNewAllocationOfSellerOrBuyer(tempName, tempPassword);
	
	if (!onlySeller)
	{
		BuyerAndSeller tempBuyerSeller(tempName, tempPassword, tempAddress);
		(*this) += tempBuyerSeller;//add buyer and seller to the usersArray
	}
	else
	{
		Seller tempSeller(tempName, tempPassword, tempAddress);
		(*this) += tempSeller;//add seller to the usersArray	
	}
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
	else if (connected == SELLER || connected == BUYER_AND_SELLER)//connected to seller 
	{
		Product product = Product(insertInfoForProduct(((Seller**)usersArray)[indexOfSeller]));
		(((Seller**)usersArray)[indexOfSeller])->AddToProductList(product);
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
	while (category != 0 && category != 1 && category != 2 && category != 3)
	{
		cout << "Category incorrect, please enter again: " << endl;
		cin >> category;
	}
	cout << "Please enter the price of the product: " << name << endl;
	cin >> price;
	while (price < 0)
	{
		cout << "Price is illegal, please enter again: " << name << endl;
		cin >> price;
	}
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
		logSizeofOrderCart = (((Buyer**)usersArray)[indexOfBuyer])->getLogSizeOfOrderCart();
		if (logSizeofOrderCart == 0)
			cout << "You must purchase product before adding feedback" << endl;
		else
		{
			orderCart = new Order*[logSizeofOrderCart];
			for (i = 0; i < logSizeofOrderCart; i++)
			{
				orderCart[i] = (((Buyer**)usersArray)[indexOfBuyer])->GetOrderCart()[i];
			}
			Seller* seller = chooseSellerForFeedBack(orderCart, logSizeofOrderCart);
			if (seller != NULL)
				createFeedBack(seller, userName);
		}
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
	else
		cout << "Product has not been found" << endl;
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
	else //you are buyer or buyer and seller
	{
		cout << "Please enter the name of the seller: " << endl;
		cin.getline(SellerName, MAX_LENGTH);
		cout << "Please enter the name of the product: " << endl;
		cin.getline(productName, MAX_LENGTH);

		indexOfSeller = searchForSeller(SellerName);
		if (indexOfSeller != NONE)
		{
			product = new Product(searchForProductOfSpecificSeller(productName, *(((Seller**)usersArray)[indexOfSeller])));
			(((Buyer**)usersArray)[indexOfBuyer])->AddToShoppingCart(*product);//adding the product to the exact buyer who is currently using the system(logged In)
			delete product;
		}
		else
			cout << "Seller has not been found" << endl;
	}
}

int System::searchForSeller(char* name)
{
	int index = NONE;
	for (int i = 0; i < logicSizeOfUsersArray; i++)
	{
		if (strcmp(name, this->usersArray[i]->getUserName()) == 0)
			index = i;
	}
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
		cout << "Product doesnt exist for this seller " << endl;
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
	else //you are buyer or buyer and seller
	{
		sizeOfShoppingCart = (((Buyer**)usersArray)[indexOfBuyer])->getLogSizeOfShoppingCart();
		if (sizeOfShoppingCart == 0)
			cout << "No products in shopping cart" << endl;
		else if ((((Buyer**)usersArray)[indexOfBuyer])->getOrder() != NULL)
			cout << "The last order is not completed" << endl;
		else //you can start the order
		{
			ShoppingCart = (((Buyer**)usersArray)[indexOfBuyer])->getShoppingCart();
			addChosenProductsToOrder(sizeOfShoppingCart, (((Buyer**)usersArray)[indexOfBuyer]));
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
	else //you are buyer or buyer and seller
	{
		order = (((Buyer**)usersArray)[indexOfBuyer])->getOrder();
		if (order != NULL)
			finishOrder(order, (((Buyer**)usersArray)[indexOfBuyer]));
		else
			cout << "You payed for all your orders :)" << endl;
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
	if (this->logicSizeOfUsersArray == 0)
		cout << "No users!" << endl;
	int countBuyers = 0;
	for (int i = 0; i < this->logicSizeOfUsersArray; i++)
	{
		if (typeid(*(usersArray[i])) == typeid(Buyer))
		{
			cout << "Username number :" << i + 1 << "'s buyer is :" << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countBuyers++;
		}
	}
	if (countBuyers == 0) // no buyers 
		cout << "No buyers!" << endl;
}


void System::showAllSellers()//seif 9 
{
	if (this->logicSizeOfUsersArray == 0)
		cout << "No users!" << endl;
	int countSellers = 0;
	for (int i = 0; i < this->logicSizeOfUsersArray; i++)
	{
		if (typeid(*(usersArray[i])) == typeid(Seller))
		{
			cout << "Username number :" << i + 1 << "'s seller is :" << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countSellers++;
		}
	}
	if (countSellers == 0) // no sellers
		cout << "No sellers!" << endl;
}


void System::showAllBuyersAndSellers()//seif 10
{
	if (this->logicSizeOfUsersArray == 0)
		cout << "No users!" << endl;
	int countBuyersAndSellers = 0;
	for (int i = 0; i < this->logicSizeOfUsersArray; i++)
	{
		if (typeid(*(usersArray[i])) == typeid(BuyerAndSeller))
		{
			cout << "Username number :" << i + 1 << "   buyerAndSeller name is:" << this->usersArray[i]->getUserName() << " and his password is : " << this->usersArray[i]->getPassword() << endl;
			countBuyersAndSellers++;
		}
	}
	if (countBuyersAndSellers == 0) // no buyer and sellers
		cout << "No buyer and sellers!" << endl;
}


void System::showAllUsersOfCertainType()//seif 11
{
	int user;
	cout << "Please enter the users you are looking for: \n" <<  "0 for sellers \n" << "1 for buyers \n" << "2 for buyer and sellers " << endl;
	cin >> user;
	if (user == SELLER)
		showAllSellers();
	else if (user == BUYER)
		showAllBuyers();
	else if (user == BUYER_AND_SELLER)
		showAllBuyersAndSellers();
	else
		cout << "Your choice is illegal" << endl;
}


void System::getTheNameOfTheProduct()// seif 12
{
	char productName[MAX_LENGTH];

	cout << "enter the name of the product you are searching for : " << endl;
	cin.getline(productName, MAX_LENGTH);
	SearchForProductExistence(productName);
}

void System::SearchForProductExistence(char* productName) 
{
	for (int i = 0; i < this->logicSizeOfUsersArray; i++)
	{
		Product** productListTemp = new Product*[(((Seller**)usersArray)[i])->getPhysicListProductSize()];
		productListTemp = (((Seller**)usersArray)[i])->getListOfProducts();
		for (int j = 0; j < (((Seller**)usersArray)[i])->getLogListProductSize(); j++)
		{
			if (strcmp(productName, productListTemp[j]->getName()) == 0)//checks if found a product with the exact name 
				cout << "The Seller number is : " << i + 1 << ", which his name is: " << this->usersArray[i]->getUserName() << " has the product, the price is: " << productListTemp[j]->getPrice() << endl;
			else
				cout << "The product has not been found" << endl;
		}
	}
}


void System::checkOperators()//seif 13
{
	testOperatorCout();
	testOperatorCompare();
}

void System::testOperatorCout()
{
	cout << "TEST OF OPERATOR << : " << endl;
	Date testDate(2, 6, 2020);//test
	Address testAddress("testCountry", "testCity", "testStreet", 11);//test
	FeedBack testFeedback("feedBackGiverTest", testDate, "this is a Test message!!");
	cout << "-------------------------------------" << endl;
	cout << "test DATE operator" << endl;
	cout << testDate;
	cout << "-------------------------------------" << endl;
	cout << "test ADDRESS operator" << endl;
	cout << testAddress;
	cout << "-------------------------------------" << endl;
	cout << "test FEEDBACK operator" << endl;
	cout << testFeedback;//test all of operators << made 
}

void System::testOperatorCompare()
{
	char* nameOne= ("nitzan");
	cout << "TEST OF OPERATOR > : " << endl;
	int i;
	Buyer testBuyer1("hadar", "12345678", &Address("testCountry", "testCity", "testStreet", 11));
	Buyer testBuyer2("nitzan", "12345678", &Address("testCountry", "testCity", "testStreet", 11));
}


void System::operator+=(const Buyer& other)//might be a prob because of & 
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->usersArray[logicSizeOfUsersArray - 1] = new Buyer(other);
}

void System::operator+=(const Seller& other)
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->usersArray[logicSizeOfUsersArray - 1] = new Seller(other);
}

void System::operator+=(const BuyerAndSeller& other)//DOSENT WORKKKKKKKKKK
{
	this->allocateForNewUser();//allocation
	if (logicSizeOfUsersArray == 1)//allocate
		usersArray = new User*[physicSizeOfUsersArray];
	this->usersArray[logicSizeOfUsersArray - 1] = new BuyerAndSeller(other);
}

