#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	Object();
	~Object();
	void ChangeId(int id) {this->id = id;}
protected:
	int id;
};

#endif