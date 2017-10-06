#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int main()
{
	int last = 1;
	int current = 1;
	long long int sum = current;
	cout << current << endl;

	while (current < 1000000000)
	{
		int next = last + current;
		last = current;
		current = next;
		sum += current;
		cout << current << endl;
	}

	cout << endl;
	cout << "Sum: " << sum << endl;

	cin.get();

	return 0;
}