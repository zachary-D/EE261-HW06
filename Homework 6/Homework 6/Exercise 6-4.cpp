#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int maxValue = 1000000000;

int main()
{
	int last = 1;
	int current = 1;
	long long int sum = current;
	cout << current << endl;

	while (true)
	{
		//Calculate the next number in the sequence
		int next = last + current;
		last = current;
		current = next;

		//If the new value in the sequence is less than maxValue, add it to the sum.  Otherwise, exit the loop
		if (current >= maxValue) break;
		sum += current;
		cout << current << endl;
	}

	cout << endl;
	cout << "Sum: " << sum << endl;

	cin.get();

	return 0;
}