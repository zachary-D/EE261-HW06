#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

using std::string;


bool isValid(char inp)		//Returns true when 'inp' is a valid, and can be in an email address
{
	return ('a' <= inp && inp <= 'z') || ('A' <= inp && inp <= 'Z') || ('0' <= inp && inp <= '9') || inp == '_' || inp == '.';
}

string extractEmailFrom(string line)
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
			current--;
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
													//the first period

	int secondPeriod = address.find('.', firstPeriod + 1);

	if (secondPeriod != string::npos)
	{
		//If a second period is found (it shouldn't be there) remove it
		address = address.substr(0, secondPeriod);
	}

	cout << "Address found: " << address << endl;

	return address;
}


const string inputFile = "mail.dat";
const string outputFile = "addresses.dat";

std::ifstream fileIn;
std::ofstream fileOut;

const int lowCharBound = 32;
const int highCharBound = 126;



void generateTestData()
{
	

	string outputData;

	const int strLength = 10;
	for (int i = 0; i < strLength; i++)
	{
		outputData.push_back(lowCharBound);
	}
	fileOut.open(inputFile);

	while (true)
	{
		//Make sure all the characters are within the bounds
		for (int addr = outputData.size() - 1; addr >= 0; addr--)
		{

			if (outputData[addr] > highCharBound)
			{
				if (addr == 0) break;
				else {
					outputData[addr - 1]++;
					outputData[addr] = lowCharBound;
					if (addr == outputData.size() - 1 - 5)	cout << outputData[outputData.size() - 1 - 5] << endl;
				}
			}

		}

		//Export the string to the file
		fileOut << outputData << endl;

		//Incriment the final character
		outputData[outputData.size()-1]++;

	}
	fileOut.close();
}


char genRandomChar()
{
	return rand() % (highCharBound - lowCharBound) + lowCharBound;
}

void generateTestData2()
{
	srand(time(NULL));

	string data;

	string name;
	string domain;
	string extension = "com";

	const int nameLength = 3;
	const int domainLength = 2;

	for (int i = 0; i < nameLength; i++)
	{
		name.push_back(' ');
	}

	for (int i = 0; i < domainLength; i++)
	{
		domain.push_back(' ');
	}




}


int main()
{
	//generateTestData();

	fileIn.open(inputFile);
	fileOut.open(outputFile);

	do
	{
		string line;
		std::getline(fileIn, line);
		if (line.find('@') != string::npos)
		{
			fileOut << extractEmailFrom(line) << endl;
		}

	} while (fileIn.eof() == false);

	fileIn.close();
	fileOut.close();

	cin.get();	//Hold the window open

	return 0;
}