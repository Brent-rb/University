#include <iostream>

using namespace std;

int main() {
	float number;

	cout << "Geef een nummer in\n";
	cin >> number;

	number /= 2.54;

	cout << "Het ingegeven nummer in inches is: " << number << "\n";

	return 0;
}
