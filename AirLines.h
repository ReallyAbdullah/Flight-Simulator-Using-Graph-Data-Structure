#pragma once

#include "Time.h"
#include "Date.h"
#include <cmath>
#include <iostream>
using namespace std;

class AirLines {
public:
    string Name;
    int Cost;
    Time FlyingTime,LandingTime;
    Date date;
    AirLines* next;

    AirLines() :Name(""), Cost(0) , FlyingTime(), LandingTime() {}
    AirLines(AirLines& rhs) {
        this->Cost = rhs.Cost;
        this->FlyingTime = rhs.FlyingTime;
        this->LandingTime = rhs.LandingTime;
        this->Name = rhs.Name;
        this->date.date = rhs.date.date;
        this->date.Month = rhs.date.Month;
        this->date.Year = rhs.date.Year;
        this->next = NULL;
    }

    void SetCost(int data, int multiplier) {
        data -= 48;
        data = data * multiplier;
        Cost += data;
    }

    void setFlyingTime(string data, AirLines& a) {

        for (int i = 0, UniqueCheckID = 0, multiplier = 10; data[i] != '\0'; i++) {

            if (data[i] == ':')
                i++;
            if (UniqueCheckID == 1) {
                a.FlyingTime.setMinutes(data[i], multiplier);
                multiplier /= 10;
            }

            if (data[i + 1] != ':') {
                if (UniqueCheckID == 0) {
                    a.FlyingTime.setHours((data[i]), multiplier);
                    multiplier /= 10;
                    if (data[i + 1] == ':')
                        UniqueCheckID++;
                }
            }
            if (data[i + 1] == ':') {
                if (UniqueCheckID == 0) {
                    multiplier = 1;
                    a.FlyingTime.setHours((data[i]), multiplier);
                    if (data[i + 1] == ':')
                        UniqueCheckID++;
                }
            }
        }
    }

    void setLandingTime(string data, AirLines & a) {

        for (int i = 0, UniqueCheckID = 0, multiplier = 10; data[i] != '\0'; i++) {

            if (data[i] == ':')
                i++;
            if (UniqueCheckID == 1) {
                a.LandingTime.setMinutes(data[i], multiplier);
                multiplier /= 10;
            }

            if (data[i + 1] != ':') {
                if (UniqueCheckID == 0) {
                    a.LandingTime.setHours((data[i]), multiplier);
                    multiplier /= 10;
                    if (data[i + 1] == ':')
                        UniqueCheckID++;
                }
            }
            else {
                if (UniqueCheckID == 0) {
                    multiplier = 1;
                    a.LandingTime.setHours((data[i]), multiplier);
                    if (data[i + 1] == ':') {
                        UniqueCheckID++;
                        multiplier = 10;
                    }
                }
            }
        }
    }

    void SetDate(string data,AirLines& a) {
        //1 / 12 / 2019

        for (int i = 0, UniqueCheckID = 0, multiplier = 10; data[i] != '\0'; i++) {

            if (data[i] == '/')
                i++;

            if (UniqueCheckID == 2) {
                a.date.setYear(data[i], multiplier);
                multiplier /= 10;
            }

            if (UniqueCheckID == 1) {
                a.date.setMonth(data[i], multiplier);
                multiplier /= 10;
                if (data[i + 1] == '/') {
                    UniqueCheckID++;
                    multiplier = 1000;
                }
            }

            if (UniqueCheckID == 0) {
                a.date.setDate((data[i]));
                UniqueCheckID++;
            }
        }
    }

    void SetCost(string data, AirLines& a) {

        for (int length = data.length() - 1, multiplier = pow(10, length), i = 0; data[i] != '\0'; i++) {
            a.SetCost(data[i], multiplier);
            multiplier /= 10;
        }

    }

    void DisplayAll() {
        cout << "***********************\n";
        cout << "COST: " << Cost <<endl;
        cout << "DEPARTURE TIME: ";
        FlyingTime.DisplayTime();
        cout << endl;
        cout << "ARRIVAL TIME: ";
        LandingTime.DisplayTime();
        cout << endl;
        cout << "FLIGHT DATE: ";
        date.DisplayAll();
        cout << "AIRLINE: " << Name << endl;
        cout << "***********************\n";
    }
    void ResetAll() {
        Cost = 0;
        FlyingTime.Reset();
        LandingTime.Reset();
        this->date.ResetDate();
        Name = "";
    }
};
