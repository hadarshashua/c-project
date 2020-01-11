#ifndef FEEDBACK_H
#define FEEDBACK_H
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ostream>

using namespace std;

//#include "E-CommerceSystem.h"
#include "Buyer.h"
#include "Date.h"


//const int MAX_LENGTH = 21;
//const int MAX_FEEDBACK_LENGTH = 200;

class FeedBack
{
private:
	char feedBackGiver[MAX_LENGTH];
	Date dateOfFeedBack;
	char message[MAX_FEEDBACK_LENGTH];

public:
	FeedBack() = default;
	FeedBack(char* feedBackGiver, Date dateOfFeedBack, char* message); //constructor
	FeedBack(const FeedBack& other);

	void setFeedBackGiverName(Buyer buyername);
	void setDateOfFeedBack(int day, int month, int year);
	void setMessage(char* feedback);

	 const char* getFeedBackGiver() const;//CHANGED THEM ALL TO CONST 
	 Date getDate() const ;
	const char* getMessage()const ;


	friend ostream& operator<<(ostream& os, const FeedBack& feedback);
};

#endif // !FEEDBACK_H


