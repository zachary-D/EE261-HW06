#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

using std::string;

const string inputFile = "mailTest.dat";
const string outputFile = "addresses.dat";

std::ifstream fileIn;
std::ofstream fileOut;

//Variables for controlling the test data generator
const int lowCharBound = 32;
const int highCharBound = 126;

const int numTests = 10000;

bool isValid(char inp)		//Returns true when 'inp' is a valid, and can be in an email address
{
	return ('a' <= inp && inp <= 'z') || ('A' <= inp && inp <= 'Z') || ('0' <= inp && inp <= '9') || inp == '_' || inp == '.';
}

void extractEmailFrom(string line)
{
	int center = line.find('@');	//The position of the '@' symbol in the email (aka the 'center' of the email)
	int current = center;		//The current position being processed in the string

	//The beginning and end of the email in the line
	int beginning = center;
	int end = center;

	//Find the beginning of the email
	do {	//Loop backwards until an invalid character is reached
		current--;
		if (current == -1)
		{
			break;
		}
	} while (isValid(line[current]));

	beginning = current + 1;

	//Find the end of the email
	current = center;	//reset to the center of the email

	do {	//Loop forward until an invalid character is reached
		current++;
		if (current == line.size()) {
			break;
		}
	} while (isValid(line[current]));
	
	end = current;

	//Extract the substring that is the address
	string address = line.substr(beginning, end - beginning);


	//Preform some validation, make sure the address is in the format
	// name@domain.com, and remove any trailing characters if they
	// violate this (used to correct from trailing periods)

	center = address.find('@');


	int firstPeriod = address.find('.', center);	//The position of
													//the first period after the '@'

	if (firstPeriod == string::npos) return;	//If there's no period, this email is invalid

	int secondPeriod = address.find('.', firstPeriod + 1);	//The position of the second period after the '@'
															//(if it exists)

	if (secondPeriod != string::npos)
	{
		//If a second period is found (it shouldn't be there) remove it
		address = address.substr(0, secondPeriod);
	}

	//Check for ".." or ".@" or "@.", as these can't exist inside a valid address
	for (int iter = 0; iter < address.size() - 2; iter++)		//The loop is limited to address.size() -2
																//the loop will be addressing the current
																//element and the one after it
	{
		string curr = address.substr(iter, 2);
		if (curr == ".." || curr == ".@" || curr == "@.") return;
			
	}

	if (center == 0 || center == address.size() - 1) return;	//If the '@' sign is the first or last
																//character in the email, it is invalid

	//There can't be periods without valid characters surrounding them
	if (address[0] == '.' || address[address.size() - 1] == '.') return;

	cout << "Address found: " << address << endl;

	fileOut << address << endl;
}

char genRandomChar()
{
	int ret =  rand() % (highCharBound - lowCharBound - 1) + lowCharBound;
	if (ret == 64) ret++;		//Avoid adding a second '@' symbol
	return ret;
}

string genRandStr(int length)
{
	string ret;
	for (int i = 0; i < length; i++) ret.push_back(genRandomChar());
	return ret;
}

void generateTestData2()
{
	srand(time(NULL));

	fileOut.open(inputFile);

	const int nameLength = 5;
	const int domainLength = 5;
	const int extensionLength = 3;
	
	const int beforeLength = 4;
	const int afterLength = 4;

	//Generate a test dataset
	for (int counter = 0; counter < numTests; counter++)
	{
		string name = genRandStr(nameLength);
		string domain = genRandStr(domainLength);
		string extension = genRandStr(extensionLength);

		string beforeEmail = genRandStr(beforeLength);
		string afterEmail = genRandStr(afterLength);
		
		fileOut << beforeEmail + " " + name + "@" + domain + "." + extension + " " + afterEmail << endl;
	}


	fileOut.close();

}


int main()
{
	generateTestData2();

	fileIn.open(inputFile);
	fileOut.open(outputFile);

	do
	{
		string line;
		std::getline(fileIn, line);
		if (line.find('@') != string::npos)
		{
			extractEmailFrom(line);
		}

	} while (fileIn.eof() == false);

	fileIn.close();
	fileOut.close();

	cin.get();	//Hold the window open

	return 0;
}