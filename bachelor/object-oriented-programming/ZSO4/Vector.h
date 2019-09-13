#ifndef VECTOR_H
#define VECTOR_H

enum State {NOT, ALLOCATED};

class Vector {
public:
	void Allocate(int amount);
	Vector();
	~Vector();
	void SchrijfUit();
	bool IsAllocated();

	void Set(int const place, double number) {if(place < this->size) this->vectorArray[place] = number;} 
protected:
	int size;
	double* vectorArray;
	State state;
};


#endif