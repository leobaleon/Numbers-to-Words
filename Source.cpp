/*
Author: Leonardo Baleon
Description: simple program that converts numbers into US English words.
Instructions: the user must not enter anything other than digits.
			  ListOfWords.hpp must be in the same directory.
			  Ctrl+C to quit the program.
*/

#include <iostream>
#include "ListsOfWords.hpp"

// prompts the user for a positive number and validates the input
// before allowing the program to perform any parsing on the string
void retrieveValidInput(std::string &input);

// ensures that the string contains a total length that is a multiple of 3.
// this is done to simplify the parsing of the entire string since numbers
// are essentially written out based on 3 numbers at a time. ex:
// 0 001 =                                 one 
// 0 021 =                          twenty-one
// 0 121 =              one hundred twenty-one
// 2,121 = two thousand one hundred twenty-one
void normalizeInput(std::string &input);

// checks the first digit of each triplet for a value greater than
// 0, if one exists, it simply appends the word "hundred" as necessary
void handleHundreds(int digit);

// checks if the value in the ones place is a '1', since it will then
// need to use the corresponding teen naming instead of a hyphenated
// combination of a tens value and a ones value. ex:
// 17 = seventeen VS 27 = twenty-seven
// note: this function only sets flags for the next function, handleOnes,
// to perform the actual distinctions and printing of words
void handleTens(int digit, bool& tensFlag, bool& teensFlag);

// checks if flags were triggered by the handleTens function to perform
// the correct printing of words. also, makes sure to print hyphens if needed,
// and resets flags for the next triplet in the overall number
void handleOnes(std::string input, int digit, bool& tensFlag, bool& teensFlag, int& endsRemaining, int i);

// simply calculates the total number of triplets in the overall number
// provided by the user. this function will loop once for each triplet and
// make the corresponding function calls to handle each digit's place
void parse(std::string input, int endsRemaining, bool& tensFlag, bool& teensFlag);

// driver function that starts by setting some basic variables all calling
// the necessary functions to get the program started.
int main(int argc, char** argv) 
{
	// string used to store user input
	std::string input;

	// ends remaining used to determine which ending should be used in the large array
	unsigned long endsRemaining{ 0 };

	// flags to decide between using ones values or teens values or adding dashes
	bool tensFlag{ false }, teensFlag{ false };

	// infinite loop to keep getting new numbers. user will have to ctrl+c to quit
	while (true)
	{
		// get a new string
		retrieveValidInput(input);

		// fix for easy parsing
		normalizeInput(input);

		// set based on new string's length
		endsRemaining = (input.length() - 1) / 3;

		// reset flags for each new string
		tensFlag = teensFlag = false;

		// parse number
		parse(input, endsRemaining, tensFlag, teensFlag);
	}

	return 0;
}

void retrieveValidInput(std::string &input)
{
	unsigned int i{ 0 };

	std::cout << "Please enter positive real numbers only: ";
	std::getline(std::cin, input);

	//prevent no input, keep looping throughout the entire string
	while (input.length() == 0 || i < input.length()) 
	{
		//make sure every character is a digit
		if (!(isdigit(input[i]))) 
		{
			std::cout << "Please enter positive real numbers only: ";
			std::getline(std::cin, input); // retry
			i = 0;
		}
		else
		{
			++i;
		}
	}	
}

void normalizeInput(std::string &input)
{
	// since we parse the entire number 3 digits at a time, 
	// insert 0's to make the string length a multiple of 3 for easier handling later
	if (input.length() % 3 == 1) 
	{
		input.insert(0, "00");
	}
	else if (input.length() % 3 == 2) 
	{
		input.insert(0, "0");
	}
}

void handleHundreds(int digit)
{
	// hundreds place digit
	if (digit > 0) 
	{
		// pull value from ones array and append "hundred"
		std::cout << ones[digit] << " hundred "; 
	}
}

void handleTens(int digit, bool& tensFlag, bool& teensFlag)
{
	// tens place
	if (digit > 1) 
	{
		std::cout << tens[digit];

		// to hyphenate between 21-99
		tensFlag = true; 
	}
	//if second digit in triplet was a 1, we pull from teens array
	if (digit == 1) 
	{
		teensFlag = true;
	}
}

void handleOnes(std::string input, int digit, bool& tensFlag, bool& teensFlag, int& endsRemaining, int i)
{
	if (teensFlag)
	{
		// pull from teens instead of ones
		std::cout << teens[digit]; 
	}
	else //if not a teen value (10-19)
	{ 
		// meant to handle if the user types in only 0
		if (input[0] == 48 && input[1] == 48 && input[2] == 48) 
		{
			std::cout << ones[digit];
		}
		else
		{
			// hyphenate if needed, dont display any value if 3rd digit is a 0
			std::cout << (tensFlag && input[i] != 48 ? "-" : "") << (input[i] == 48 ? "" : ones[digit]) << " ";

			if (endsRemaining > 0) //if an ending is needed 
			{
				// decrement ends remaining and also output corresponding ending
				std::cout << endings[--endsRemaining] << " "; 
			}

			//reset flags
			teensFlag = tensFlag = false; 
		}
	}
}

void parse(std::string input, int endsRemaining, bool& tensFlag, bool& teensFlag)
{
	for (int i = 0; i < input.length(); i++)
	{
		// triplet used to divide large numbers into sets of 3, 
		// digit converts char within string to its corresponding int value
		int triplet{ i % 3 }, digit{ int(input[i]) - 48 };

		if (triplet == 0)
			handleHundreds(digit);
		else if (triplet == 1)
			handleTens(digit, tensFlag, teensFlag);
		else
			handleOnes(input, digit, tensFlag, teensFlag, endsRemaining, i);
	}
	
	// new line for next user prompt
	std::cout << std::endl;
}