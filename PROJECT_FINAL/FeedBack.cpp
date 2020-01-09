#include "FeedBack.h"

FeedBack::FeedBack(char* feedBackGiver, Date dateOfFeedBack, char* message) //constructor
{
	strcpy(this->feedBackGiver, feedBackGiver);
	this->dateOfFeedBack = dateOfFeedBack;
	strcpy(this->message, message);
}

FeedBack::FeedBack(const FeedBack& other) //copy c'tor
{
	strcpy(this->feedBackGiver, other.feedBackGiver);
	this->dateOfFeedBack = Date(other.dateOfFeedBack);
	strcpy(this->message, other.message);
}


void FeedBack::setFeedBackGiverName(Buyer buyername)
{
	strcpy(this->feedBackGiver, buyername.getUserName());
}

void FeedBack::setDateOfFeedBack(int day, int month, int year)
{
	dateOfFeedBack.setDate(day, month, year);
}

void FeedBack::setMessage(char* feedback)
{
	strcpy(message, feedback);
}

char* FeedBack::getFeedBackGiver() 
{
	return feedBackGiver;
}

Date FeedBack::getDate()
{
	return dateOfFeedBack;
}

char* FeedBack::getMessage()
{
	return message;
}