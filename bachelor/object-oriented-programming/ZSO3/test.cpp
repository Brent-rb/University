#include <iostream>

using namespace std;

void foo();

int main(int argc, char const *argv[])
{
	for(int i = 0; i < 10; i++)
		foo();
	int x = 0;

	foo();

	return 0;
}

void foo() {
	static int x = 0;

	cout << x << "\n";
	x++;
}