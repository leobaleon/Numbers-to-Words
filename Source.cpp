#include <iostream>
#include "ListsOfWords.h"

void retrieveValidInput(std::string &input);
void normalizeInput(std::string &input);

int main() 
{
	std::string input;

	do
	{
		retrieveValidInput(input);
		normalizeInput(input);

		//ends remaining used to determine which ending should be used in the large array
		auto endsRemaining{ (input.length() - 1) / 3 };

		//flags to decide between using ones values or teens values or adding dashes
		bool tensFlag{ false }, teensFlag{ false };

		for (unsigned int i = 0; i < input.length(); i++)
		{
			//triplet used to divide large numbers into sets of 3, digit converts char within string to its corresponding int value
			int triplet{ i % 3 }, digit{ int(input[i]) - 48 };

			if (triplet == 0)
			{
				if (digit > 0) // hundreds place digit
					std::cout << ones[digit] << " hundred "; //pull value from ones array and append "hundred"
			}
			else if (triplet == 1)
			{
				if (digit > 1) // tens place
				{
					std::cout << tens[digit];
					tensFlag = true; //to hyphenate between 21-99
				}
				if (digit == 1) //if second digit in triplet was a 1, we pull from teens array
					teensFlag = true;
			}
			else
			{
				if (teensFlag)
					std::cout << teens[digit]; //pull from teens instead of ones
				else { //if not a teen value (10-19)
					if (input[0] == 48 && input[1] == 48 && input[2] == 48) //meant to handle if the user types in only 0
					{
						std::cout << ones[digit];
					}
					else
					{
						//hyphenate if needed, dont display any value if 3rd digit is a 0
						std::cout << (tensFlag && input[i] != 48 ? "-" : "") << (input[i] == 48 ? "" : ones[digit]) << " ";
						if (endsRemaining > 0) //if an ending is needed 
							std::cout << endings[--endsRemaining] << " "; //decrement ends remaining and also output corresponding ending
						teensFlag = tensFlag = false; //reset flags
					}
				}
			}
		}
		std::cout << std::endl;
	} while (input != "0-1"); //keep going until user decides to quit

	system("pause");
	return 0;
}

void retrieveValidInput(std::string &input)
{
	unsigned int index{ 0 };

	std::cout << "Please enter real numbers only and in proper format: ";
	std::getline(std::cin, input);

	while (input.length() == 0 || index < input.length()) //prevent no input, keep looping throughout the entire string
	{
		if ((input[0] == 48 && input[1] != 46) || //only accept 0s if followed by a decimal
			!(isdigit(input[index])) &&  //make sure every character is a digit
			!(input[index] == 45) &&  //or a negative sign
			!(input[index] == 46)) //or a decimal point
		{
			std::cout << "Please enter real numbers only and in proper format: ";
			std::getline(std::cin, input); // retry
			index = 0;
		}
		else
			++index;
	}
}

void normalizeInput(std::string &input)
{
	if (input.length() % 3 == 1) //insert 2 0's to make the string length a multiple of 3 for easier handling later
	{
		input.insert(0, "00");
	}
	else if (input.length() % 3 == 2) //insert a single 0
	{
		input.insert(0, "0");
	}
}
