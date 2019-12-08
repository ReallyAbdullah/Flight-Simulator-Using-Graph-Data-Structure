#pragma once

#include "Destination.h"
#include "ListDate.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


class OriginNode: public DestinationNode {      //CLASS CONTAINING ORIGIN NAME AND DESTINATIONS POINTER
public:
    string OriginName;
    OriginNode* Down;
    DestinationNode* Next;
    ListDate date;
    int VertexNumber;
    int HotelCost;
    
    OriginNode() :OriginName(""), Down(NULL),Next(NULL),VertexNumber(0),HotelCost(0) {}
    OriginNode(string origin) :OriginName(origin), Down(NULL), Next(NULL),VertexNumber(0),HotelCost(0) {}
    OriginNode(OriginNode& rhs) {
        this->OriginName = rhs.OriginName;
        this->Next = rhs.Next;
        this->Down = rhs.Down;
        this->VertexNumber = rhs.VertexNumber;
    }
};

class Origin {
public:
    OriginNode* OriginHead, *OriginLast;
    int Originsize = 0;
    
    Origin() :OriginHead(NULL), OriginLast(NULL),Originsize(0) {}
    
    void InsertOrigin(string origin) {
        OriginNode* ToAdd = new OriginNode(origin);
        ToAdd->VertexNumber = Originsize;
        if (OriginHead == NULL) {
            OriginHead = ToAdd;
            OriginLast = ToAdd;
            Originsize++;
        }
        else {
            
            OriginNode* iterator = OriginHead;
            
            while (iterator->Down != NULL) {
                if (iterator->OriginName == origin)
                    return;
                iterator = iterator->Down;
            }
            
            if (iterator->OriginName != origin){
                iterator->Down = ToAdd;
                iterator->Down->VertexNumber = Originsize;
                Originsize++;
            }
            
        }
        
        
        
    }
    
    void InsertDestination(string source,string destination) {
        
        DestinationNode* ToAdd = new DestinationNode(destination);
        OriginNode* iterator = OriginHead;
        
        while (iterator->OriginName != source)
            iterator = iterator->Down;
        
        if (iterator->Next == NULL) {
            iterator->Next = ToAdd;
        }
        else {
            DestinationNode* DestinationIterator = iterator->Next;
            bool repeat = false;
            
            if (DestinationIterator->destination == destination) {
                repeat = true;
            }
            while (DestinationIterator->next != NULL) {
                if (DestinationIterator->destination == destination) {
                    repeat = true;
                    break;
                }
                DestinationIterator = DestinationIterator->next;
            }
            if (DestinationIterator->destination == destination) {
                repeat = true;
            }
            
            if (repeat == false)
                DestinationIterator->next = ToAdd;
        }
    }
    
    void InsertAirline(string source,string destination,AirLines& rhs) {
        AirLines* ToAdd = new AirLines(rhs);
        OriginNode* OriginIterator = OriginHead;
        
        while (OriginIterator->OriginName != source)
            OriginIterator = OriginIterator->Down;
        
        if (OriginIterator->Next == NULL) {
            return;
        }
        else {
            DestinationNode* DestinationIterator = OriginIterator->Next;
            
            while (DestinationIterator->destination != destination) {
                DestinationIterator = DestinationIterator->next;
            }
            
            if (DestinationIterator->Air == NULL)
                DestinationIterator->Air = ToAdd;
            else {
                AirLines* Airlineiterator = DestinationIterator->Air;
                
                while (Airlineiterator->next != NULL)
                    Airlineiterator = Airlineiterator->next;
                
                Airlineiterator->next = ToAdd;
            }
        }
    }
    
    void SetHotelPrice(string HotelPrice,OriginNode* Origin){
        Origin->HotelCost=0;
        for (int length = HotelPrice.length() - 1, multiplier = pow(10, length), i = 0; HotelPrice[i] != '\0'; i++) {
            Origin->HotelCost += (HotelPrice[i] - 48) * multiplier;
            multiplier /= 10;
        }
        
    }
    void DisplayDestinations() {
        OriginNode* iterator = OriginHead;
        DestinationNode* iter = iterator->Next;
        
        while (iterator != NULL) {
            
            cout << iterator->OriginName << " ";
            
            while (iter != NULL) {
                cout << iter->destination << " ";
                iter = iter->next;
            }
            
            cout << endl;
            iterator = iterator->Down;
            if (iterator)
                iter = iterator->Next;
        }
        
    }
    int AlreadyExists(string origin) {
        OriginNode* iterator = OriginHead;
        int counter = 0;
        while (iterator != NULL) {
            if (iterator->OriginName == origin)
                return counter;
            
            counter++;
            iterator = iterator->Down;
        }
        
        return -1;
    }
    int Size() {
        return Originsize;
    }
    
    //    OriginNode& operator[](int index) {
    //        OriginNode* iterator = OriginHead;
    //
    //        for (int i = 0; i < index; i++)
    //            iterator = iterator->Down;
    //
    //        return *iterator;
    //    }
    
    OriginNode * operator[](int index) {
        OriginNode* iterator = OriginHead;
        
        for (int i = 0; i < index; i++)
            iterator = iterator->Down;
        
        return iterator;
    }
    
    void ReadFromFile(string FileName) {
        string SingleLine;
        fstream ifile;
        ifile.open(FileName, ios::in);
        if (ifile)
        {
            cout << "Reading From File" << endl;
            int StringPointer = 0;
            string source,destination,temp;
            AirLines a;
            while (!ifile.eof())
            {
                getline(ifile, SingleLine);
                
                
                while (SingleLine[StringPointer] != ' ') {
                    source += SingleLine[StringPointer];
                    StringPointer++;
                }
                
                this->InsertOrigin(source);
                StringPointer++;
                while (SingleLine[StringPointer] != ' ') {
                    destination += SingleLine[StringPointer];
                    StringPointer++;
                }
                this->InsertDestination(source,destination);
                
                StringPointer++;
                
                while (SingleLine[StringPointer] != ' ') {
                    temp += SingleLine[StringPointer];
                    StringPointer++;
                }
                a.SetDate(temp, a);
                temp = "";
                
                StringPointer++;
                
                while (SingleLine[StringPointer] != ' ') {
                    temp += SingleLine[StringPointer];
                    StringPointer++;
                }
                a.setFlyingTime(temp, a);
                temp = "";
                StringPointer++;
                
                while (SingleLine[StringPointer] != ' ') {
                    temp += SingleLine[StringPointer];
                    StringPointer++;
                }
                a.setLandingTime(temp, a);
                
                temp = "";
                StringPointer++;
                
                while (SingleLine[StringPointer] != ' ') {
                    temp += SingleLine[StringPointer];
                    StringPointer++;
                }
                a.SetCost(temp, a);
                
                temp = "";
                StringPointer++;
                
                while (StringPointer < SingleLine.length()) {
                    temp += SingleLine[StringPointer];
                    StringPointer++;
                }
                a.Name = temp;
                
                this->InsertAirline(source,destination,a);
                
                source = destination = temp="";
                a.ResetAll();
                StringPointer = 0;
            }
            
        }
        else {
            cout << "File Does Not Exist";
        }
        
        ifile.close();
    }
    
    void ReadHotelCharges(string FileName){
        
        string SingleLine;
        ifstream ifile(FileName);
        int lines = 0;
        if (ifile)
        {
            cout << "Reading From Hotel File" << endl;
            int StringPointer = 0;
            string source,HotelPrice;
            while (ifile)
            {
                getline(ifile, SingleLine);
                while(SingleLine[StringPointer] != ' '){
                    source+=SingleLine[StringPointer];
                    StringPointer++;
                }
                
                StringPointer++;
                
                while(SingleLine[StringPointer] != '\r'){
                    HotelPrice += SingleLine[StringPointer];
                    StringPointer++;
                }
                //cout << source ;
               // HotelPrice.erase(HotelPrice.size()-1,HotelPrice.size());
                //cout << source ;
                SetHotelPrice(HotelPrice, FindOrigin(source));
                source="";
                HotelPrice="";
                StringPointer=0;
                lines++;
                if (lines>=10)
                    break;
            }
        }
        
        ifile.close();
    }
    OriginNode & operator[](string name){
        OriginNode * temp = OriginHead;
        while(temp->OriginName!=name){
            temp = temp->Down;
        }
        return *temp;
    }
    
    OriginNode* FindOrigin(string Origin){
        OriginNode* iterator=OriginHead;
        
        while (iterator){
            if (iterator->OriginName == Origin)
                return iterator;
            
            iterator=iterator->Down;
        }
        
        iterator=NULL;
        return NULL;
    }
    int OriginReturn(string findO){
        OriginNode * temp = OriginHead;
        
        while(temp){
            if(temp->OriginName==findO){
                return temp->VertexNumber;
            }
            temp = temp->Down;
        }
        return -1;
    }
};
