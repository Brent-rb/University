#ifndef CPERSOON_H
#define CPERSOON_H
#include <string>

class CPersoon: virtual public Object
{
public:
	CPersoon();
	~CPersoon();
protected:
	string name;
	int age;
};

#endif