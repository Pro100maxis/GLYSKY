#include <iostream>
#include <string>
#include <sstream>

#include "SupportFunc.h"
using namespace std;

string IntToString(int num)
{
	stringstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;

}

int StringToInt(string str)
{
//	return atoi(str.c_str());

	stringstream ss;
	ss << str;
	int intt;
	ss >> intt;
	return intt;	
}