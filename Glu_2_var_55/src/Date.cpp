

#include "Date.h"

date::~date()
{
}

date::date() : date(1, 1, 1000)
{
	
}
date::date(int day, int mount, int year)
{
	setDay(day);
	setMount(mount);
	setYear(year);
}

void date::setStringdate(string date)
{
	int _day;
	int _mount;
	int _year;

	string tmp = "";
	int num;
	int parsePart = 1;

	for (auto ch : date)
	{
		if (ch == '.')
		{
			num = StringToInt(tmp);
			if (parsePart == 1) _day = num;
			else if (parsePart == 2) _mount = num;
			else if (parsePart == 3) _year = num;
			tmp = "";
			parsePart++;
			continue;
		}
		tmp += ch;
	}
	num = StringToInt(tmp);
	_year = num;
	setDate(_day, _mount, _year);
}

bool date::isLeapYear(int year)
{
	if (year % 4 == 0) {
		if (year % 100 == 0) {
			if (year % 400 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void date::setDate(int day, int mount, int year)
{
	int tmpday = day;
	if (isLeapYear(year) == true)
	{
		if ((mount == 2) && (day >= 30))
		{
			tmpday = 29;
		}
	}

	setDay(tmpday);
	setMount(mount);
	setYear(year);
}

void date::setDay(int date)
{
	if (chekDay(date))
	{
		Day = date;
	}
	else Day = 1;

}

void date::setMount(int date)
{
	if (chekMount(date))
	{
		Mount = date;
	}
	else Mount = 1;


}

void date::setYear(int date)
{
	if (chekYear(date))
	{
		Year = date;
	}
	else Year = 1000;
}

bool date::chekDay(int date)
{
	if ((date >= 1) & (date <= 31))
		return true;
	return false;
}

bool date::chekMount(int date)
{
	if ((date >= 1) & (date <= 12))
		return true;
	return false;
}

bool date::chekYear(int date)
{
	if ((date >= 1000))
		return true;
	return false;
}


string date::GetSringDate()
{
	return  IntToString(Day) + "." + IntToString(Mount) + "." + IntToString(Year);
}