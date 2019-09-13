#include <sstream>
#include <string>
#include <iostream>

using namespace std;

void sayDate(istringstream & sstring);

int main(int argc, char const *argv[])
{
	istringstream sstring("17 december 2012");
	sayDate(sstring);

	return 0;
}

void sayDate(istringstream & sstring) {
	int day, year, month;

	string monthS;

	sstring >> day >> monthS >> year;

	if(monthS.compare("januari") == 0)
		month = 1;
	else if(monthS.compare("februari") == 0)
		month = 2;
	else if (monthS.compare("maart") == 0)
		month = 3;
	else if (monthS.compare("april") == 0)
		month = 4;
	else if (monthS.compare("mei") == 0)
		month = 5;
	else if (monthS.compare("juni") == 0)
		month = 6;
	else if (monthS.compare("juli") == 0)
		month = 7;
	else if (monthS.compare("augustus") == 0)
		month = 8;
	else if (monthS.compare("september") == 0)
		month = 9;
	else if (monthS.compare("oktober") == 0)
		month = 10;
	else if (monthS.compare("november") == 0)
		month = 11;
	else if (monthS.compare("december") == 0)
		month = 12;
	else
		month = 0;

	cout << day << "/" << month << "/" << year << "\n";
}