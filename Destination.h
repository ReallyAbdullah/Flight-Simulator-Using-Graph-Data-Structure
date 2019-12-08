#pragma once

#include "AirLines.h"
#include <iostream>
using namespace std;

class DestinationNode {
public:
	string destination;
	AirLines* Air;
	DestinationNode* next;

	DestinationNode() :destination(""), next(NULL),Air() {}
	DestinationNode(string dest) :destination(dest), next(NULL),Air() {
        
    }
	DestinationNode(DestinationNode& rhs): Air(){
		this->destination = rhs.destination;
		this->next = rhs.next;
	}

};
