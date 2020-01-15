#include "Date.h"


Date::Date(const int& day,const int& month,const int& year) // constructor
{
	setDate(day, month, year);
}

Date::Date(const Date& other) // copy c'tor
{
	day = other.day;
	month = other.month;
	year = other.year;
}


bool Date::setDay(int day)
{
	if (!checkDay(day)) // check if day is legal
		return false;
	this->day = day;
	return true;
}

bool Date::setMonth(int month)
{
	if (!checkMonth(month)) // check if month is legal
		return false;
	this->month = month;
	return true;
}

bool Date::setYear(int year)
{
	if (!checkYear(year)) // check if year is legal
		return false;
	this->year = year;
	return true;
}


int Date::getDay() const
{
	return day;
}

int Date::getMonth() const
{
	return month;
}

int Date::getYear() const
{
	return year;
}


bool Date::checkDay(int day) // check if day is legal
{
	if (day >= 1 && day <= 31)
		return true;
	return false;
}

bool Date::checkMonth(int month) // check if month is legal
{
	if (month >= 1 && month <= 12)
		return true;
	return false;
}

bool Date::checkYear(int year) // check year day is legal
{
	if (year >= 2000 && year <= 2020)
		return true;
	return false;
}

void Date::setDate(int day, int month, int year) // insert all information to date
{
	this->day = day;
	this->month = month;
	this->year = year;
}

ostream& operator<<(ostream & os,const Date & date)
{
	os << "Year is :" << date.getYear() << "\n" << "Month is: " << date.getMonth() << "\n" << "Day is: " << date.getDay() << endl;
	return os;
}
