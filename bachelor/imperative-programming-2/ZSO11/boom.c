#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Knoop {
	char* name;
	int childs;
	struct Knoop* siblings;
	struct Knoop* parent;
} Knoop;

Knoop* searchKnoop(Knoop* const list);
void addKnoop(Knoop** list, Knoop* parent, char* string);
void writeBoom(Knoop* const list);
void deleteKnoop(Knoop** list, Knoop* element);
void clearTree(Knoop** list);
void printTree(Knoop* const list);

int main(int argc, char const *argv[])
{
		
	return 0;
}

Knoop* searchKnoop(Knoop* const list){

	return;
}

void addKnoop(Knoop** list, Knoop* parent, char* string){
	Knoop* tempPointer = (Knoop*) malloc(sizeof(struct Knoop));
	tempPointer->name = string;
	tempPointer->parent = parent;
	tempPointer->childs = 0;
	tempPointer->siblings = NULL;

	if(*list == NULL && tempPointer->parent == NULL) {
		*list = tempPointer;
	}
	else if(tempPointer->parent != NULL) {
		if(parent->childs == 0) {
			parent->siblings = (Knoop*) malloc(sizeof(Knoop*));
			parent->siblings = tempPointer;
			parent->childs++;
		}
		else {
			parent->childs++;
			parent->siblings = (Knoop*) realloc(parent->*siblings, sizeof(Knoop*) * parent->childs);
			parent->siblings[parent->childs - 1] = tempPointer;
		}
	}

	return;
}

void writeBoom(Knoop* const list){

	return;
}

void deleteKnoop(Knoop** list, Knoop* element){

	return;
}

void clearTree(Knoop** list){

	return;
}

void printTree(Knoop* const list) {
	if(list == NULL) {
		
	}
}
