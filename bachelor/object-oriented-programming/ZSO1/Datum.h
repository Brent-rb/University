#ifndef DATUM_H
#define DATUM_H

class Datum {
public:
	Datum();
	Datum(int day, int month, int year);
	Datum(char* dateString);
	~Datum();
	int GetDay();
	int GetMonth();
	int GetYear();
	void SetDate(int day, int month, int year);
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);
private:
	int day;
	int month;
	int year;
};

#endif