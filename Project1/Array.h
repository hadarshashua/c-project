#ifndef Array_H
#define Array_H
#pragma warning(disable : 4996)
#include "Definitions.h"
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

template <class T>
class Array
{
private:
	int physicalSize, logicalSize;
	char delimiter;
	T** arr;

public:
	Array(int size = 1, char delimiter = ' ');
	Array(const Array& other);
	~Array();

	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);

	const int& getLogSize();
	const int& getPhysicalSize();
	//const T* getArr();
	T getArrByIndex(const int& index);
	T* getArray();

	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; , i < arr.logicalSize; i++)
			os << *(arr.arr[i]) << arr.delimiter;
	}
	void  Array<T>::CheckSizeOfArrayAndReAllocateIfNeeded();
};

/*template<class T>
const T* Array<T>::getArr()
{
return array;
}
*/

template<class T>
T Array<T>::getArrByIndex(const int& index)
{
	return (arr[index]);
}

template<class T>
T* Array<T>::getArray()
{
	return arr;
}

template <class T>
Array<T>::Array(int size = 1, char delimiter = ' ') :physicalSize(size), logicalSize(0), delimiter(delimiter)
{
	arr = new T[physicalSize];//allocation for physicalSize of the class T array
}

template <class T>
Array<T>::Array(const Array& other)
{
	//delete[]arr;//might do an issue if the destructor will allready work before this 
	*this = other;//the object will now be the object other (will 'take' all of his var)!
}

template <class T>
Array<T>::~Array()
{
	for (int i = 0; i < logicalSize; i++)
		delete arr[i];
	delete[]arr;
	cout << "array destructor" << endl;
}

template <class T>
const Array<T>& Array<T>:: operator=(const Array<T>& other)
{
	if (this != &other)//comparing address of objects--if its the same copy will be useless or it will make errors 
	{
		for (int i = 0; i < logicalSize; i++)
			delete arr[i];
		delete[]arr;//deallocate arr of this

		physicalSize = other.physicalSize;
		logicalSize = other.logicalSize;
		delimiter = other.delimiter;
		arr = new T[physicalSize];//new allocate 
		for (int i = 0; i < logicalSize; i++)
			*(arr[i]) = *(other.arr[i]);//using operator = of product 
	}
	return *this;
}

template <class T>
const Array<T>& Array<T>:: operator+=(const T& newVal)
{
	CheckSizeOfArrayAndReAllocateIfNeeded();
	if (logicalSize < physicalSize)
	{
		*(arr[logicalSize++]) = *(newVal);
	}
	return *this;
}

template<class T>
void  Array<T>::CheckSizeOfArrayAndReAllocateIfNeeded()
{
	T* TempArray;
	if (logicalSize >= physicalSize)//need to increase the array size 
	{
		physicalSize*=2;//hadar i increased only by 1 because if not we will need to do it ** ;(
		TempArray = new T[physicalSize];
		for (int i = 0; i < logicalSize; i++)
		{
			*(TempArray[i]) = *arr[i];
		//	TempArray[i] = arr[i];
		}
		for (int i = 0; i < logicalSize; i++)
			delete arr[i];
		delete[]arr;
	}
}

template<class T>
const int& Array<T>::getLogSize()
{
	return logicalSize;
}

template<class T>
const int& Array<T>::getPhysicalSize()
{
	return physicalSize;
}

#endif