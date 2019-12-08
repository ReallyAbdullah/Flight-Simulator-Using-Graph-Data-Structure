//
//  Simulator.h
//  Project_2
//
//  Created by Momin Salar+AR+Abdullah on 01/12/2019.
//  Copyright © 2019 Momin Salar. All rights reserved.
//

#ifndef Simulator_h
#define Simulator_h

#include "Origin.h"
#include "Passenger.h"
#include "Vector.h"
#include "Queue.h"

class FlightSimulator{
public:
    Origin OriginObj;
    Passenger PassengerObj;
    
    FlightSimulator(){
        OriginObj.ReadFromFile("Flights.txt");
        OriginObj.ReadHotelCharges("HotelCharges_perday.txt");
    }
    
    void BookAFlight(){
        PassengerObj.BookFlight();
        if (FindBooking()){
            cout << "FLIGHT BOOKED\n";
            return;
        }
        cout << "FLIGHT NOT FOUND\n";
    }
    
    bool DirectFlight(OriginNode* tempOrigin, DestinationNode* tempDesti, AirLines* tempAir) {
        
        while (tempOrigin != NULL) {
            DestinationNode* tempDesti = tempOrigin->Next;
            bool OriginFound = false;
            if (tempOrigin->OriginName == PassengerObj.getOrigin()) {
                OriginFound = true;
            }
            if (OriginFound) {           // ONLY GO IN DESTI WHEN ORIGIN FOUND
                
                while (tempDesti != NULL) {
                    AirLines* tempAir = tempDesti->Air;
                    
                    bool DestiFound = false;
                    if (tempDesti->destination == PassengerObj.getDestination()) {
                        DestiFound = true;
                    }
                    
                    if (DestiFound) {    // ONLY GO IN AIRLINES IF DESTINATION FOUND
                        
                        while (tempAir != NULL) {
                            bool AirLineFound = false;
                            if (tempAir->Name == PassengerObj.getAirLine() && tempAir->date.date == PassengerObj.date && tempAir->date.Month == PassengerObj.month && tempAir->date.Year == PassengerObj.year) {
                                AirLineFound = true;
                            }
                            if (AirLineFound) {
                                cout << tempOrigin->OriginName << " TO " << tempDesti->destination << endl;
                                tempAir->DisplayAll();
                                
                                char ConfirmFlight;
                                
                                cout << "Do you want to book this Flight? " << endl;
                                cout << "Y: Yes" << endl << "N: No" << endl;
                                cin >> ConfirmFlight;
                                
                                if (ConfirmFlight == 'Y' || ConfirmFlight == 'y') {
                                    return true;
                                }
                                else if (ConfirmFlight == 'N' || ConfirmFlight == 'n'){
                                    //cout << "Please re-enter your flight preferences for date: " << endl;
                                    //PassengerObj.setDate();
                                    tempAir = tempAir->next;
                                    
                                    continue;
                                }
                            }
                            else if (!AirLineFound) {
                                cout << "Sorry for inconvience but your specific Airline doesnot Go from: " << PassengerObj.Origin << " TO: " << PassengerObj.Destination << "." << endl;
                                cout << "However the Airlines below do provide these services. Do you want to change Airlines? Y: Yes, N: No" << endl;
                                tempAir->DisplayAll();
                                
                                char ChangeAirlines = false;
                                cin >> ChangeAirlines;
                                
                                if (ChangeAirlines == 'Y' || ChangeAirlines == 'y') {
                                    PassengerObj.AirLine = tempAir->Name;
                                    cout << "Your Flight has been booked Thank you for Traveling with us. :D" << endl;
                                    return true;
                                }
                                
                                
                            }
                            tempAir = tempAir->next;
                            
                            if (!tempAir) {
                                cout << "Sorry but you cannot take a Direct Flight. Please follow the instructions below: " << endl;
                                break;
                            }
                        }
                        
                    }
                    tempDesti = tempDesti->next;
                    if (!tempDesti) {
                        cout << "Sorry but you cannot take a Direct Flight. Please follow the instructions below: " << endl;
                        break;
                    }
                    
                }
            }
            
            tempOrigin = tempOrigin->Down;
        }
        return false;
    }
    
    
    
    void printpath(Vector<string>& path)
    {
        unsigned long size = path.size();
        for (int i = 0; i < size; i++)
            cout << path[i] << " ";
        //cout << PassengerObj.Destination;
        cout << endl;
    }
    
    int isNotVisited(string  x, Vector<string >& path)
    {
        //if (x!=PassengerObj.Destination && x!=PassengerObj.Origin){
        unsigned long size = path.size();
        for (int i = 0; i < size; i++)
            if (path[i] == x )
                return 0;
        
        return 1;
        //}
        //return 0;
    }
    int findMinCost(AirLines * & aPtr){
        AirLines* somethin = aPtr;
        int minCost = 9999999999;
        while (somethin){
            int cost = somethin->Cost;
            if (minCost>cost){
                minCost = cost;
                aPtr = somethin;
            }
            somethin = somethin->next;
        }
        return minCost;
    }
    
    int getPathCost(Vector<string>& myPath) {
        int costOfpath = 0;
        int pathSize = 0;

        for (int i = 0; i < myPath.size(); i++) {
            DestinationNode* desti = OriginObj[OriginObj.OriginReturn(myPath[i])]->Next;
            while (desti != nullptr && desti->destination != myPath[i + 1]) {
                desti = desti->next;
            }
            if (desti != nullptr) {
                AirLines* aPtr = desti->Air;
                while (aPtr != nullptr && aPtr->Name != PassengerObj.AirLine) {
                    aPtr = aPtr->next;
                }
                if (aPtr==NULL){
                    aPtr = desti->Air;
                    costOfpath += findMinCost(aPtr);
                }
                else if (aPtr != nullptr) {
                    //cout << aPtr->Name << " ****" ;
                    costOfpath += aPtr->Cost;
                }
                cout<<endl;
                if (myPath.size()>2 && myPath.size()-i>2){
                    DestinationNode *tempDestiNext = OriginObj[OriginObj.OriginReturn(desti->destination)]->Next;
                    while (tempDestiNext->destination!=myPath[i+2]){
                        tempDestiNext = tempDestiNext->next;
                    }
                    double time = tempDestiNext->Air->FlyingTime.convertInHours()-desti->Air->LandingTime.convertInHours();
                    cout << "**********TIME OF TRANSIT**********" << time;
                    if (time<0)
                        time+=24;
                    if (time>12.0){
                        costOfpath += OriginObj[OriginObj.OriginReturn(desti->destination)]->HotelCost;
                        cout << desti->destination << " ";
                        cout << "HOTEL COST " << OriginObj[OriginObj.OriginReturn(desti->destination)]->HotelCost << "ADDED ";
                    }
                    
                }
                cout << "FROM " << myPath[i] <<  " TO " << myPath[i+1] << endl;
                aPtr->DisplayAll();
                cout<<endl;
            }
        }
        
        return costOfpath;
    }
    
    double countTime(Vector<string> &OnePath){        // COUNT MINIMUM TIME AND CANCEL ALL OTHER
//        cout << "CHECKING TIMES FOR PATH: ";
//        OnePath.print();
//        cout << endl;
        double timeC = 0;
        int pathSize = 0;
        
        if (OnePath.size()>2){
            pathSize=2;        //If FLIGHTS INDIRECT
        }
        else {
            pathSize=1;
        }
        
        for (int i=0; i<OnePath.size()-pathSize; i++){
            DestinationNode * tempDesti = OriginObj[OriginObj.OriginReturn(OnePath[i])]->Next;
            while (tempDesti->destination!=OnePath[i+1]){
                tempDesti = tempDesti->next;
            }
            
            cout << "Arrival TIME IN " << tempDesti->destination << " - Departure time from " << OnePath[i] << " ";
            double time = tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours();
            if (time<0)
                time+=24.0;
            timeC += time;
            cout << tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours() << endl;
            DestinationNode * tempDestiNext = OriginObj[OriginObj.OriginReturn(tempDesti->destination)]->Next;
            if (pathSize!=1){
                while (tempDestiNext->destination!=OnePath[i+2]){
                    tempDestiNext = tempDestiNext->next;
                }
                cout << "Departure TIME to " << tempDestiNext->destination << " - Arrival time in " << tempDesti->destination << " ";
                time = tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours();
                if (time<0)
                    time+=24.0;
                timeC += time;
                cout << tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours() << endl;
            }
            //cout << array[i] << endl;
        }
        return timeC;
        
    }
    
    
    bool countFlightTime(Vector<string> &OnePath, double & minTime){        // COUNT MINIMUM TIME AND CANCEL ALL OTHER
        cout << "CHECKING TIMES FOR PATH: ";
        OnePath.print();
        cout << endl;
        double timeC = 0;
        int pathSize = 0;
        
        if (OnePath.size()>2){
            pathSize=2;        //If FLIGHTS INDIRECT
        }
        else {
            pathSize=1;
        }
        
        for (int i=0; i<OnePath.size()-pathSize; i++){
            DestinationNode * tempDesti = OriginObj[OriginObj.OriginReturn(OnePath[i])]->Next;
            while (tempDesti->destination!=OnePath[i+1]){
                tempDesti = tempDesti->next;
            }
            
            cout << "Arrival TIME IN " << tempDesti->destination << " - Departure time from " << OnePath[i] << " ";
            double time = tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours();
            if (time<0)
                time+=24.0;
            timeC += time;
            cout << tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours() << endl;
            DestinationNode * tempDestiNext = OriginObj[OriginObj.OriginReturn(tempDesti->destination)]->Next;
            if (pathSize!=1){
                while (tempDestiNext->destination!=OnePath[i+2]){
                    tempDestiNext = tempDestiNext->next;
                }
                cout << "Departure TIME to " << tempDestiNext->destination << " - Arrival time in " << tempDesti->destination << " ";
                time = tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours();
                if (time<0)
                    time+=24.0;
                
                timeC += time;
                cout << tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours() << endl;
            }
            if (timeC>minTime){
                cout << "TIME VALUE ALREADY EXCEEDED THE MINIMUM TIME\n";

            }
        }
            //cout << array[i] << endl;
        cout << "TOTAL TIME " << timeC << endl;
        if (timeC<minTime){
            minTime = timeC;
            return true;
        }
        return false;
    }
        
    void sortedInput(Vector<Vector<string>> &saveAll){
        
            
        double i, key, j;
        if (saveAll.size()<2){
            return;
        }
        if (PassengerObj.criteria==2){
            for (i = 1; i < saveAll.size(); i++)
            {
                
                key = countTime(saveAll[i]);
                j = i - 1;
          
                /* Move elements of arr[0..i-1], that are
                greater than key, to one position ahead
                of their current position */
                
                while (j >= 0 && countTime(saveAll[j]) > key)
                {
                    saveAll[j + 1] = saveAll[j];
                    j = j - 1;
                }
                saveAll[j + 1] = saveAll[i];
            }
        }
        else if (PassengerObj.criteria==1){
            for (i = 1; i < saveAll.size(); i++)
              {
                  
                  key = getPathCost(saveAll[i]);
                  j = i - 1;
            
                  /* Move elements of arr[0..i-1], that are
                  greater than key, to one position ahead
                  of their current position */
                  
                  while (j >= 0 && getPathCost(saveAll[j]) > key)
                  {
                      saveAll[j + 1] = saveAll[j];
                      j = j - 1;
                  }
                  saveAll[j + 1] = saveAll[i];
              }
        }
    }
    
    bool checkDate(string src, string nxt){
        DestinationNode * tempDest = OriginObj[OriginObj.OriginReturn(src)]->Next;
        while (tempDest && tempDest->destination!=nxt){
            tempDest = tempDest->next;
        }
        AirLines * tempAir = tempDest->Air;
        if (PassengerObj.AirLine!=""){
            while (tempAir && tempAir->Name!=PassengerObj.AirLine){
                tempAir = tempAir->next;
            }
            if (tempAir){
                if (tempAir->date.date == PassengerObj.date && tempAir->date.Month == PassengerObj.month && tempAir->date.Year == PassengerObj.year)
                    return true;
            }
        }
        else {
            while(tempAir){
                if (tempAir->date.date == PassengerObj.date && tempAir->date.Month == PassengerObj.month && tempAir->date.Year == PassengerObj.year)
                    return true;
                tempAir = tempAir->next;
            }
        }
        return false;
    }
    
    bool CheckTransit(Vector<string> paths){
        
        for (int i=0; i<paths.size(); i++){
            if (paths[i] == PassengerObj.TransitLocation){
                return true;
            }
        }
        
        return false;
    }
    
    void findpaths(Vector<Vector<string>>&pathf, string src, string dst,Vector<Vector<string>> &saveAllFlights){
        
        myQueue<Vector<string>> searchPath;
        Vector<string> minTimePath;
        Vector<string> paths(10);
        double minTime = 9999;
        int SourceCheck = OriginObj.OriginReturn(src);
        
        if (SourceCheck == -1) {
            cout << "Please enter a Valid Source." << endl;
            exit(0);
        }
        else {
            paths.push_back(src);                        //PUSH ORIGIN ENTERED BY USER
            searchPath.push(paths);                     // PUT FIRST Vector PATH IN QUEUE
            
            while (!searchPath.empty()) {
                
                paths = searchPath.front();
                searchPath.pop();
                
                int currentIndex = OriginObj.OriginReturn(paths[paths.size() - 1]);
                if (currentIndex==-1){      // Origin Does not exit- Therefor no leading paths, and if it isn't the destination, cancel path
                    //                cout << "\nPATH CANCELLED  ";
                    //                printpath(paths);
                    continue;
                }
                
                // traverse to all the nodes connected to
                // current vertex and push new path to queue
                for (int i = 0; i < pathf[currentIndex].size(); i++) {
                    
                    if (isNotVisited(pathf[currentIndex][i], paths)) {
                        
                        Vector<string> newpath;
                        newpath = paths;
                        
                        
                        if (pathf[currentIndex][i]!=dst){
                            newpath.push_back(pathf[currentIndex][i]);
                            searchPath.push(newpath);
                        }
                        else{
                            cout << "***";
                            Vector<string> pushString;
                            pushString = paths;
                            pushString.push_back(dst);
                            if (checkDate(pushString[0], pushString[1]))
                                cout << "                   FLIGHTS FOR SPECIFIED DATE FOUND\n\n";
                            else {
                                cout << "OTHER POSSIBLE PATHS\n";
                            }
                            
                            if (PassengerObj.criteria==2){          //CHECK ACCORDING TO TIME IF INPUT IS FOR TIME
                                bool checkMin = countFlightTime(pushString, minTime);
                                if (checkMin){
                                    minTimePath = pushString;
                                }
                                
                                
                            }
                            else if (PassengerObj.criteria==1){
                                cout << "TOTAL PATH: ";
                                printpath(pushString);
                                double cost = getPathCost(pushString);
                                cout << "TOTAL COST: "<< cost<<endl << endl;
                            }
                            if (PassengerObj.TransitLocation!=""){
                                bool checkT = CheckTransit(pushString);
                                if (checkT){
                                    printpath(pushString);
                                    saveAllFlights.push_back(pushString);
                                    cout<<endl;
                                }
                                else {
                                    cout << "PATH ";
                                    printpath(pushString);
                                    cout << "DOES NOT CONTAIN TRANSIT\n";
                                    cout<<endl;
                                }
                                
                            }
                            else{
                                cout << "TRANSIT LOCATION NOT SPECIFIED\n";
                                printpath(pushString);
                                cout<<endl;
                                saveAllFlights.push_back(pushString);
                            }
                            //sortedInput(saveAllFlights);
                        }
                        
                    }
                    
                }
                
            }
            cout << "\n\n\nThe Minimum Time Path is: ";
            minTimePath.print();
            cout << " With total hours = " << minTime;
            cout << endl;
        }
    }
    
    
    
    
    void LeastTimeSorted(Vector<Vector<string>> &AllFlights){
        double array[AllFlights.size()];
        for (int i=0; i<AllFlights.size(); i++){
            array[i] = 0;
        }
        
        for (int i=0; i<AllFlights.size(); i++){
            for (int j=0; j<AllFlights[i].size()-2; j++){
                DestinationNode * tempDesti = OriginObj[OriginObj.OriginReturn(AllFlights[i][j])]->Next;
                while (tempDesti->destination!=AllFlights[i][j+1]){
                    tempDesti = tempDesti->next;
                }
                cout << "Arrival TIME IN " << tempDesti->destination << " - Departure time from " << AllFlights[i][j] << " ";
                double time = tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours();
                if (time<0)
                    time+=24.0;
                array[i] += time;
                cout << tempDesti->Air->LandingTime.convertInHours()-tempDesti->Air->FlyingTime.convertInHours() << endl;
                DestinationNode * tempDestiNext = OriginObj[OriginObj.OriginReturn(tempDesti->destination)]->Next;
                while (tempDestiNext->destination!=AllFlights[i][j+2]){
                    tempDestiNext = tempDestiNext->next;
                }
                cout << "Departure TIME to " << tempDestiNext->destination << " - Arrival time in " << tempDesti->destination << " ";
                time = tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours();
                if (time<0)
                    time+=24.0;
                array[i] += time;
                cout << tempDestiNext->Air->FlyingTime.convertInHours()-tempDesti->Air->LandingTime.convertInHours() << endl;
                
            }
            cout << array[i] << endl;
        }
    }
    
    bool FindBooking(){
        
        OriginNode * tempOrigin = OriginObj.OriginHead;
        DestinationNode * tempDesti = tempOrigin->Next;
        AirLines * tempAir = tempDesti->Air;
        Vector<Vector<string >> pathFinder(100);
        
        //pathFinder.resize(100);
        Vector<Vector<string>> saveAllFlights(11);
        
        OriginNode * temp = OriginObj[0];
        int i = 0;
        
        while(temp){
            DestinationNode * tempD = temp->Next;
            pathFinder[i].push_back(temp->OriginName);
            while (tempD){
                pathFinder[i].push_back(tempD->destination);
                tempD = tempD->next;
            }
            i++;
            temp = temp->Down;
            
        }
        cout << "////////////////////// ADJACENCY LIST //////////////////////\n";
        for (int i=0; i<=pathFinder.size(); i++){
            for (int j=0; j<pathFinder[i].size(); j++){
                if (j!=pathFinder[i].size()-1)
                    cout << pathFinder[i][j] << " -> ";
                else
                    cout << pathFinder[i][j];
            }
            cout << endl;
        }
        cout << "////////////////////// ADJACENCY LIST //////////////////////\n\n\n";
        bool FoundDirectFlight = false;
        if(PassengerObj.DirectFlight)
            FoundDirectFlight = Scenario5(PassengerObj.Origin, PassengerObj.Destination);
        
        if (!FoundDirectFlight){
            
            findpaths(pathFinder, PassengerObj.Origin, PassengerObj.Destination,saveAllFlights);
            //if (PassengerObj.criteria==2)   // TIME CRITERION
            //   LeastTimeSorted(saveAllFlights);
        }
        cout << endl;
//        for (int i=0; i<=saveAllFlights.size(); i++){
//            for (int j=0; j<saveAllFlights[i].size(); j++){
//                if (j!=saveAllFlights[i].size()-1)
//                    cout << saveAllFlights[i][j] << " -> ";
//                else
//                    cout << saveAllFlights[i][j];
//
//            }
//            int cost = getPathCost(saveAllFlights[i]);
//            if (cost != 0) {
//                cout << "TOTAL COST :" << cost;
//            }
//
//            cout << endl << endl;
//
//        }
        
        
        return 1;
    }
    
    
    bool Scenario5(string src, string dst){
        //PassengerObj.BookFlight();
        OriginNode * tempOrigin = OriginObj[OriginObj.OriginReturn(PassengerObj.Origin)];
        AirLines * saveAir;
        int flightsCount = 0;
        bool flightBool = false;
        while (tempOrigin != NULL) {
            DestinationNode* tempDesti = tempOrigin->Next;
            bool OriginFound = false;
            if (tempOrigin->OriginName == PassengerObj.getOrigin()) {
                OriginFound = true;
            }
            if (OriginFound) {           // ONLY GO IN DESTI WHEN ORIGIN FOUND
                
                while (tempDesti != NULL) {
                    AirLines* tempAir = tempDesti->Air;
                    
                    bool DestiFound = false;
                    if (tempDesti->destination == PassengerObj.getDestination()) {
                        DestiFound = true;
                    }
                    
                    if (DestiFound) {    // ONLY GO IN AIRLINES IF DESTINATION FOUND
                        saveAir = tempAir;
                        while (tempAir != NULL) {
                            if (PassengerObj.AirLine==""){
                                if (tempAir->date.date == PassengerObj.date && tempAir->date.Month == PassengerObj.month && tempAir->date.Year == PassengerObj.year) {
                                    cout << "YOUR FLIGHT FROM " << PassengerObj.Origin << " TO " << PassengerObj.Destination << " WAS FOUND\n";
                                    tempAir->DisplayAll();
                                    cout << endl;
                                    flightBool = true;
                                }
                                else{
                                    cout << "FLIGHT AVAILABLE FROM " << PassengerObj.Origin << " TO " << PassengerObj.Destination;
                                    cout << endl;
                                    tempAir->DisplayAll();
                                    cout << endl;
                                }
                            }
                            else {
                               if (tempAir->date.date == PassengerObj.date && tempAir->date.Month == PassengerObj.month && tempAir->date.Year == PassengerObj.year && tempAir->Name==PassengerObj.AirLine) {
                                    cout << "YOUR FLIGHT FROM " << PassengerObj.Origin << " TO " << PassengerObj.Destination << " WAS FOUND\n";
                                    tempAir->DisplayAll();
                                    cout << endl;
                                    flightBool = true;
                                }
                                else{
                                    cout << "FLIGHT AVAILABLE FROM " << PassengerObj.Origin << " TO " << PassengerObj.Destination;
                                    cout << endl;
                                    tempAir->DisplayAll();
                                    cout << endl;
                                }
                            }
                            tempAir = tempAir->next;
                            flightsCount++;
        
                        }
                        
                    }
                    tempDesti = tempDesti->next;
                    if (flightsCount==0 && tempAir==NULL) {
                        cout << "Sorry There is no Direct Flight available\n" << endl;
                        break;
                    }
                    if (!tempDesti){
                        if (flightsCount==0)
                            cout << "DESTINATION NOT FOUND\n";
                        break;
                    }
                    
                }
            }
            tempOrigin = tempOrigin->Down;
        }
        if (flightBool==true)
            return true;
        return false;
    }
    
    ~FlightSimulator(){}
    
};

#endif /* Simulator_h */
