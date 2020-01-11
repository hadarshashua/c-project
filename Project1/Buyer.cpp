#include "Buyer.h"

Buyer::Buyer(char* userName, char* password, Address* address, Order* order, Order** orderCart, Product** shoppingCart, int logSizeOfShoppingCart, int physicSizeOfShoppingCart, int logSizeOfOrderCart, int  physicSizeOfOrderCart) : User(userName, password, address)//c'tor default  --zero all
{
	cout << "test ctor buyer" << endl;

	this->order = order;
	this->orderCart = orderCart;
	this->shoppingCart = shoppingCart;
	this->logSizeOfOrderCart = logSizeOfOrderCart;
	this->physicSizeOfOrderCart = physicSizeOfOrderCart;
	this->logSizeOfShoppingCart = logSizeOfShoppingCart;
	this->physicSizeOfShoppingCart = physicSizeOfShoppingCart;
}

Buyer::Buyer(const Buyer& other) : User(other)// copy c'tor
{
	cout << "test copy buyer" << endl;

	int i;
	if(other.order!=NULL)//not empty
	this->order = new Order(*(other.order));
	this->orderCart = new Order*[other.getLogSizeOfOrderCart()];
	for (i = 0; i < other.getLogSizeOfOrderCart(); i++)
		this->orderCart[i] = new Order(*(other.orderCart[i]));//copying the cart

	this->shoppingCart = new Product*[other.getLogSizeOfShoppingCart()];
	for (i = 0; i < other.getLogSizeOfShoppingCart(); i++)
		this->shoppingCart[i] = new Product(*(other.shoppingCart[i]));

	this->logSizeOfOrderCart = other.getLogSizeOfOrderCart();
	this->physicSizeOfOrderCart = other.getPhysicSizeOfOrderCart();

	this->logSizeOfShoppingCart = other.getLogSizeOfShoppingCart();
	this->physicSizeOfShoppingCart = other.getPhysicSizeOfShoppingCart();
}

Buyer::Buyer(Buyer && other) : User(other)//move ctor
{
	cout << "test move buyer" << endl;

	this->order = other.order;
	other.order = NULL;

	this->orderCart = other.orderCart;
	other.orderCart = NULL;

	this->shoppingCart = other.shoppingCart;
	other.shoppingCart = NULL;

	this->logSizeOfShoppingCart = other.logSizeOfShoppingCart;
	this->logSizeOfOrderCart = other.logSizeOfOrderCart;

	this->physicSizeOfOrderCart = other.physicSizeOfOrderCart;
	this->physicSizeOfShoppingCart = other.physicSizeOfShoppingCart;
}

Buyer::~Buyer()//destructor
{
	cout << "test dtor buyer" << endl;

	int i;
	delete order;
	for (i = 0; i<this->getLogSizeOfOrderCart(); i++)
		delete orderCart[i];
	delete[] orderCart;
	for (i = 0; i<this->getLogSizeOfShoppingCart(); i++)
		delete shoppingCart[i];
	delete[]shoppingCart;
}


void Buyer::setOrder(Order* other)
{
	this->order = other;
}

void Buyer::setOrderCart(Order** orderCart)
{
	this->orderCart = orderCart;
}

void Buyer::setLogSizeOfOrderCart(int logSizeOfOrderCart)
{
	this->logSizeOfOrderCart = logSizeOfOrderCart;
}

void Buyer::setPhysicSizeOfOrderCart(int physicSizeOfOrderCart)
{
	this->physicSizeOfOrderCart = physicSizeOfOrderCart;
}

void Buyer::setShoppingCart(Product** shoppingCart)
{
	this->shoppingCart = shoppingCart;
}

void Buyer::setLogSizeOfShoppingCart(int logSizeOfShoppingCart)
{
	this->logSizeOfShoppingCart = logSizeOfShoppingCart;
}

void Buyer::setPhysicSizeOfShoppingCart(int physicSizeOfShoppingCart)
{
	this->physicSizeOfShoppingCart = physicSizeOfShoppingCart;
}


Order* Buyer::getOrder()
{
	return order;
}

 Order** Buyer::GetOrderCart()
{
	return orderCart;
}

int Buyer::getLogSizeOfOrderCart() const
{
	return logSizeOfOrderCart;
}

int Buyer::getPhysicSizeOfOrderCart() const
{
	return physicSizeOfOrderCart;
}

 Product** Buyer::getShoppingCart()
{
	return shoppingCart;
}

int Buyer::getLogSizeOfShoppingCart() const
{
	return logSizeOfShoppingCart;
}

int Buyer::getPhysicSizeOfShoppingCart() const
{
	return physicSizeOfShoppingCart;
}

void Buyer::AddToOrderCart(Order* newOrder)
{
	allocateOrderCart();
	if (logSizeOfOrderCart == 1)
		this->orderCart = new Order*[physicSizeOfOrderCart];
	orderCart[logSizeOfOrderCart - 1] = newOrder;
}

void Buyer::allocateOrderCart()
{
	int i;
	Order** tempArray;
	if (logSizeOfOrderCart == physicSizeOfOrderCart)
	{
		physicSizeOfOrderCart *= 2;
		tempArray = new Order*[physicSizeOfOrderCart];
		for (i= 0; i < logSizeOfOrderCart; i++)
			tempArray[i] = new Order (*(orderCart[i]));
		for (i = 0; i < logSizeOfOrderCart; i++)
			delete orderCart[i];
		delete[] orderCart;
		orderCart = tempArray;
	}
	logSizeOfOrderCart++;
}

void Buyer::AddToShoppingCart(Product&  newProduct)
{
	allocateShoppingCart();
	if (logSizeOfShoppingCart == 1)
		shoppingCart = new Product*[physicSizeOfShoppingCart];
	shoppingCart[logSizeOfShoppingCart - 1] = new Product(newProduct);//copy c'tor 
}

void Buyer::allocateShoppingCart()
{
	int i;
	if (logSizeOfShoppingCart == physicSizeOfShoppingCart)
	{
		physicSizeOfShoppingCart *= 2;
		Product** tempShoppingCart = new Product*[physicSizeOfShoppingCart];//ctor
		for (i = 0; i < logSizeOfShoppingCart; i++)
			tempShoppingCart[i] = new Product(*(shoppingCart[i]));//copy c'tor
		for (i = 0; i < logSizeOfShoppingCart; i++)
			delete shoppingCart[i];
		delete[]shoppingCart;
		shoppingCart = tempShoppingCart;
	}
	logSizeOfShoppingCart++;
}


const bool Buyer:: operator>(const Buyer& other)//comparing--returns the buyer with the highest sum of shopping cart
{
	double sumFirstBuyer = 0, sumSeconBuyer = 0;
	int sizeFirstBuyerCart = this->getLogSizeOfShoppingCart();
	int sizeSecondBuyerCart = other.getLogSizeOfOrderCart();
	for (int i = 0; i < sizeFirstBuyerCart; i++)
		sumFirstBuyer += shoppingCart[i]->getPrice();//summing up for first buyer
	for (int i = 0; i < sizeSecondBuyerCart; i++)
		sumSeconBuyer += other.shoppingCart[i]->getPrice();//summing for second
	if (sumFirstBuyer < sumSeconBuyer)
		return false;
	else//sumFirstBuyer>=sumSecondBuyer
		return true;
}