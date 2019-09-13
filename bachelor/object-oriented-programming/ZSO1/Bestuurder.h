#ifndef BESTUURD_H
#define BESTUURD_H

class Bestuurder {
public:
	Bestuurder(char* name, int age);
	~Bestuurder();
	void PrintBestuurder();

private:
	char* name;
	int age;
};

#endif