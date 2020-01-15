#include "FeedBack.h"

FeedBack::FeedBack(const char* feedBackGiver, const Date& dateOfFeedBack, const char* message) //constructor
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

const char* FeedBack::getFeedBackGiver() const
{
	return feedBackGiver;
}

 const Date& FeedBack::getDate() const
{
	return dateOfFeedBack;
}

 const char* FeedBack::getMessage() const 
{
	return message;
}

 ostream & operator<<(ostream & os, const FeedBack & feedback)
{
	os << "feedback giver name is: " << feedback.getFeedBackGiver() << "\n" << "date of feedback is: \n" << feedback.getDate() << "the feedback is: " << feedback.getMessage() << endl;
	return os;
}
