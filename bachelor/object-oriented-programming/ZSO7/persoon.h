#ifndef PERSOON_H
#define PERSOON_H 

enum Gender {MAN, VROUW, UNKNOWN};

class Persoon {
public: 
	Persoon(char const name[], int const &age, Gender const &gender);
	Persoon(Persoon const &persoon);
	Persoon();
	virtual ~Persoon();

	char* getName();
	int getAge();
	Gender getGender();

	void setName(char const name[]);
	void setAge(int const age);
	void setGender(Gender const gender);
	void printPersoon();

private:
	void freeName();
	void makeName(char const name[]);
protected:
	char* name;
	int age;
	Gender gender;
};


#endif