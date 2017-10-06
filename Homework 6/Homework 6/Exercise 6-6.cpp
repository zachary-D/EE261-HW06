#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;




string reverse(string input)
{
	string output;
	for (int iter = input.size() - 1; iter >= 0; iter--)
	{
		output.push_back(input[iter]);
	}
	return output;
}

int main()
{
	string input;
	string reversed;

	cout << "Please enter a string:"; 
	std::getline(cin, input);

	reversed = reverse(input);
	cout << reversed << endl;
	cout << "This is " << ((input == reversed) ? "" : "not ") << "a palindrome" << endl;

	cin.get();

	return 0;
}