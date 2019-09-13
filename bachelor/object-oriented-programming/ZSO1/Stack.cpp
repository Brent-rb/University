#include <iostream>
#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

using namespace std;


Stack::Stack() {
	printf("Constructor Def.\n");
	this->topPos = 0;
	this->maxSize = 8;
}

Stack::Stack(int size) {
	printf("Constructor Size");
	this->topPos = 0;
	this->maxSize = size;
}


void Stack::NewStack() {
	int i;

	this->stack = (char*) malloc(this->maxSize * (sizeof(char)));

	for(i = 0; i < this->maxSize; i++) {
		this->stack[i] = '\0';
	}
}

void Stack::Push(char c) {
	int i;

	if(IsFull())
		printf("De stack is full.\n");
	else {
		i = this->topPos;
		this->stack[i] = c;
		this->topPos += 1;
	}
}

char Stack::Pop() {
	int i;
	char c;

	if(IsEmpty())
		printf("Stack is empty.\n");
	else {
		i = this->topPos - 1;
		c = this->stack[i];
		this->stack[i] = '\0';
		(this->topPos)--;
	}

	return c;
}


int Stack::IsEmpty() {
	return(this->stack[0] == '\0');
}

int Stack::IsFull() {
	return(this->stack[this->maxSize - 1] != '\0');
}

void Stack::ToonStack() {
	int i = 0;

	printf("\nInhoud van de stack:\n");
	while(this->stack[i] != '\0' && i < this->maxSize) {
		printf("%c\n", this->stack[i]);
		i++;
	}
}

Stack::~Stack() {
	free(this->stack);
}


int main() {
	Stack* stack = new Stack();

	stack->NewStack();
	stack->ToonStack();

	stack->Push('b');
	stack->ToonStack();
	stack->Push('r');
	stack->Push('e');
	stack->Push('n');
	stack->Push('t');
	stack->ToonStack();

	stack->Push('f');
	stack->ToonStack();

	while(!stack->IsEmpty()) {
		printf("Popped: %c\n", stack->Pop());
		stack->ToonStack();
	}

	stack->Pop();

	delete stack;

	return 0;
}