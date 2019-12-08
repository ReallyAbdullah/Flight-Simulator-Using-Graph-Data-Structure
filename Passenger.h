//
//  AirLine.h
//  Project_1
//
//  Created by Momin Salar on 29/11/2019.
//  Copyright Â© 2019 Momin Salar. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
using namespace std;


#ifndef AirLine_h
#define AirLine_h

class Passenger {
public:
    string Origin;
    string Destination;
    int date=0, month=0, year=0;
    string TransitLocation;
    int TransitDuration;
    string AirLine;
    int criteria;        //1: FOR COST,   2: FOR TIME
    bool DirectFlight;


    Passenger() {
        Origin = "";
        Destination = "";
        date = month = year = 0;
        TransitLocation = "";
        TransitDuration = 0;
        AirLine = "";
        criteria = 0;
        DirectFlight = 0;
    }

    // // // // // //       GETTERS AND SETTERS       // // // // // //

    void setOrigin(string orig) {
        Origin = orig;
    }
    void setDestination(string dest) {
        Destination = dest;
    }
    void setDate() {
        cout << "Enter your Date as: " << endl << "Day: ";
        cin >> date;
        cout << endl << "Month: ";
        cin >> month;
        cout << endl << "Year: ";
        cin >> year;
    
    }
    void setTransitLocation(string TC) {
        TransitLocation = TC;
    }
    void setAirLine(string AL) {
        AirLine = AL;
    }
    void setCriteria(int crit) {
        criteria = crit;
    }

    string getOrigin()const {
        return Origin;
    }
    string getDestination()const {
        return Destination;
    }
    //string getDate()const {
    //    return Date;
    //}
    string getTransitLocation()const {
        return TransitLocation;
    }
    string getAirLine()const {
        return AirLine;
    }
    // // // // // //       GETTERS AND SETTERS       // // // // // //

    void BookFlight() {
        string temp;

        cout << "What's your Origin? ";
        getline(cin, temp);
        cin.clear();
        Origin = temp;
        if (Origin == "") {

            do {
                cout << "Please enter a Source/Origin"<<endl;
                getline(cin, Origin);
                cin.clear();
            } while (Origin == "");

        }
        cin.clear();
        temp = "";
        cout << "What's your Destination? ";
        getline(cin, temp);
        cin.clear();
        Destination = temp;

        cout << "Enter Your date as following: "<<endl;
        cout << "Day: " << endl;
        cin >> date;
        cout << "Month: " << endl;
        cin >> month;
        cout << "Year: " << endl;
        cin >> year;
        
        cout << "Would you like a direct flight?\n1: Yes\n0: No\n ";
        cin >> DirectFlight;
        cin.ignore();
        if (DirectFlight==0){
            
        
            cout << "Would you like to have a Transit?\nY: Yes\nN: No\n";
            //cout << "***NOTE: In case No Direct Flight is found, you will be provided with other transit options. " << endl;
            char trans;
            cin >> trans;
            cin.ignore();
            if (trans == 'Y' || trans == 'y') {
                cout << "What's your Transit Location? ";
                getline(cin, temp);
                cin.clear();
                TransitLocation = temp;

                cout << "How long do you plan on Transiting? ";
                cin >> TransitDuration;
                cin.ignore();
            }
        }
        char air;
        cout << "Would you like to specify an airline?\nY: Yes\nN: No\n";
        cin>>air;
        cin.ignore();
        if (air=='Y' || air=='y'){
            getline(cin, temp);
            AirLine = temp;
            cin.clear();
        }
        cout << "Would you like to have Min Cost or Min Time ?\n1: Cost\n2: Time\n3: No Preference\n";
        cin >> criteria;
        if (criteria!=3){
            while (criteria != 1 && criteria != 2) {
                cin.ignore();
                cout << "Invalid Input.\n1: Cost\n2: Time\n";
                cin >> criteria;
            }
        }

    }

    void DisplayInfo() {
        cout << "THE ORIGIN: " << Origin << endl;
        cout << "THE DESTINATION: " << Destination << endl;
        cout << "DATE: " << date << "/" << month << "/" << year << endl;
        cout << "THE Transit Location: " << TransitLocation << endl;
        cout << "THE Transit Duration: " << TransitDuration << endl;
        cout << "THE AIRLINE: " << AirLine << endl;
        cout << "THE CRITERIA: ";
        cout << "DIRECT FLIGHT: " << DirectFlight << endl;
        if (criteria == 1)
            cout << "MIN COST\n";
        else if (criteria == 2)
            cout << "MIN TIME\n";
    }

};


#endif /* AirLine_h */
