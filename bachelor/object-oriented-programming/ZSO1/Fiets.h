#ifndef FIETS_H
#define FIETS_H

class Bestuurder;

class Fiets {
public:
	Fiets(char* name, int age);
	void Crash();
	~Fiets();
	void PrintDriver();
private:
	Bestuurder* driver;
};

#endif