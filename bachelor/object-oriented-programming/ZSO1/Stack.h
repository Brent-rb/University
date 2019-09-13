#ifndef STACK_H
#define STACK_H

class Stack {
public:
	Stack();
	Stack(int size);
	~Stack();
	void NewStack();
	void Push(char c);
	char Pop();
	int IsEmpty();
	int IsFull();
	void ToonStack();
private:
	char* stack;
	int topPos;
	int maxSize;
};


#endif