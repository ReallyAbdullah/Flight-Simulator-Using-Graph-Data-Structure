#pragma once

class Date {
public:

	int date, Month, Year;
	Date() :date(0), Month(0), Year(0) {}
	Date(int da, int month, int year) :date(da), Month(month), Year(year) {}

	int getDate() {
		return date;
	}
	int getMonth() {
		return Month;
	}
	int getYear() {
		return Year;
	}
	void setDate(int Date) {
		Date -= 48;
		date += Date;
	}
	void setMonth(int month, int multiplier) {
		month -= 48;
		month = month * multiplier;
		Month += month;
	}
	void setYear(int year, int multiplier) {
		year -= 48;
		year = year * multiplier;
		Year += year;
	}
    void DisplayAll(){
        cout<<date<<"/"<<Month<<"/"<<Year<<endl;
    }
	void ResetDate() {
		date = 0;
		Month = 0;
		Year = 0;
	}
};
