#ifndef FEEDBACK_H
#define FEEDBACK_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

//#include "E-CommerceSystem.h"
#include "Buyer.h"
#include "Date.h"


//const int MAX_LENGTH = 21;
//const int MAX_FEEDBACK_LENGTH = 200;

class FeedBack
{
private:
	char feedBackGiver[MAX_LENGTH];//we will try to do it by ref using buyer.username 
	Date dateOfFeedBack;
	char message[MAX_FEEDBACK_LENGTH];

public:
	FeedBack() = default;
	FeedBack(char* feedBackGiver, Date dateOfFeedBack, char* message); //constructor
	FeedBack(const FeedBack& other);

	void setFeedBackGiverName(Buyer buyername);
	void setDateOfFeedBack(int day, int month, int year);
	void setMessage(char* feedback);

	char* getFeedBackGiver();
	Date getDate();
	char* getMessage();
};

#endif // !FEEDBACK_H


