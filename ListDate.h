#pragma once
#include "Date.h"

class DateNode {
public:
	Date date;
	DateNode* Next;

	DateNode() :Next(NULL) {}
	DateNode(int d, int m, int y) :date(d, m, y),Next(NULL){}
	DateNode(DateNode& rhs):Next(NULL) {
		this->date.date = rhs.date.date;
		this->date.Month = rhs.date.Month;
		this->date.Year = rhs.date.Year;
	}

};
class ListDate{
public:
	DateNode* Head, *Last;
	
	ListDate() :Head(NULL), Last(NULL) {}

	void Insert(DateNode& Node) {
		DateNode* ToAdd = new DateNode(Node);

		if (Head == NULL) {
			Head = ToAdd;
			Last = ToAdd;
		}
		else {
			Last->Next = ToAdd;
			Last = ToAdd;
		}
	}

	DateNode& operator[](int index) {
		DateNode* iterator = Head;
		
		for (int i = 0; i < index; i++)
			iterator = iterator->Next;

		return *iterator;
	}
};
