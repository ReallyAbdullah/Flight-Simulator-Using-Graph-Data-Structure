// DataProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Destination.h"
#include "Origin.h"
#include "Date.h"
#include "Time.h"
#include "AirLines.h"
#include "ListDate.h"
#include "Passenger.h"
#include "Simulator.h"
#include "Vector.h"
using namespace std;

int main()
{
	Origin handle;

	handle.ReadFromFile("Flights.txt");

    
    OriginNode * tempOrigin = handle.OriginHead;
    while (tempOrigin!=NULL){
        DestinationNode * tempDesti = tempOrigin->Next;
        while (tempDesti!=NULL){
            AirLines * tempAir = tempDesti->Air;
            while (tempAir!=NULL){
                cout << tempOrigin->OriginName << " TO " << tempDesti->destination << endl;
                tempAir->DisplayAll();
                tempAir= tempAir->next;
            }
            tempDesti = tempDesti->next;
        }
        tempOrigin = tempOrigin->Down;
    }
    
    FlightSimulator FS;
    //cout << "/////////.//////////" << FS.OriginObj[FS.OriginObj.OriginReturn("Islamabad")]->HotelCost;
    FS.BookAFlight();
    //FS.Scenario5();
    int x = FS.OriginObj[FS.OriginObj.OriginReturn("Sydney")]->VertexNumber;
    cout << x;
    //cout << FS.OriginObj.OriginReturn("Islamabad");
    DestinationNode * tempDesti = FS.OriginObj[FS.OriginObj.OriginReturn(FS.PassengerObj.Origin)];
    

    
    //cout << "****"<<FS.OriginObj[1]->Next->next->next->next->Air->LandingTime.convertInHours();
//    Vector<Vector<string>> checkVector(10);
//    
//    checkVector[0].push("12334");
//    checkVector[0].push("LOLOLO");
//    checkVector[0].push("12334");
//    checkVector[0].push("MOMOM");
//    checkVector[1].push("12334");
//    checkVector[1].push("LOLOLO");
//    checkVector[1].push("12334");
//    checkVector[1].push("MOMOM");
//    
//    cout << checkVector[1][2];
//    cout << endl;
//    if (checkVector[1][3] == checkVector[0][3])
//        cout << "YESS";
//    else
//        cout << "NOO";
    
    
    //.VertexNumber << " " <<FS.OriginObj.OriginHead[3].OriginName;
}
