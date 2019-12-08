#pragma once
#include"AirLines.h"
#include<iostream>
using namespace std;

class Time {
	int Hours, Minutes;
public:

	Time() :Hours(0), Minutes(0) {}
	Time(int hours, int mint) :Hours(hours), Minutes(mint) {}

	int getHours() {
		return Hours;
	}
	int getMinutes() {
		return Minutes;
	}
	void setHours(int hours, int multiplier) {
		hours -= 48;
		hours = hours * multiplier;
		Hours += hours;
	}
	void setMinutes(int mint, int multiplier) {
		mint -= 48;
		mint = mint * multiplier;
		Minutes += mint;

	}

    double convertInHours(){
        return (Hours*1.0)+(Minutes/60.0);
    }
	void DisplayTime() {
        if (Hours<9 && Minutes<9)
            cout << '0' <<Hours << ":0" << Minutes;
        else if (Hours<9){
            cout << '0' <<Hours << ":" << Minutes;
        }
        else if (Minutes<9){
            cout <<Hours << ":0" << Minutes;
        }
        else
            cout <<Hours << ":" << Minutes;
	}
	void Reset() {
		Hours = 0;
		Minutes = 0;
	}
};
