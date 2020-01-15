#ifndef FEEDBACK_H
#define FEEDBACK_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ostream>

using namespace std;

#include "Buyer.h"
#include "Date.h"

class FeedBack
{
private:
	char feedBackGiver[MAX_LENGTH];
	Date dateOfFeedBack;
	char message[MAX_FEEDBACK_LENGTH];

public:
	FeedBack() = default;
	FeedBack(const char* feedBackGiver, const Date& dateOfFeedBack, const char* message); //constructor
	FeedBack(const FeedBack& other);

	void setFeedBackGiverName(Buyer buyername);
	void setDateOfFeedBack(int day, int month, int year);
	void setMessage(char* feedback);

	const char* getFeedBackGiver() const;
	const Date& getDate() const ;
	const char* getMessage()const ;

	friend ostream& operator<<(ostream& os, const FeedBack& feedback);
};

#endif // !FEEDBACK_H


