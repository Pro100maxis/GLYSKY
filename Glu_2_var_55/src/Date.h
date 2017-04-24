#include <iostream>
#include <string>
#include "SupportFunc.h"

using namespace std ;

class date
{
public:

	date();
	date(int day, int mount, int year);
	~date();

	void setStringdate(string date);
	bool isLeapYear(int year);
	void setDate(int day, int mount, int year);
	void setDay(int date);
	void setMount(int date);
	void setYear(int date);
	bool chekDay(int date);
	bool chekMount(int date);
	bool chekYear(int date);
	string GetSringDate();

private:

	int Day = 1;
	int Mount = 1;
	int Year = 1900;
};