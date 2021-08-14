#include "Conversion.hpp"

Conversion::Conversion() 
: endsRemaining{ 0 }, tensFlag{ false }, teensFlag{ false }
{
}

void Conversion::solution()
{
    // infinite loop to keep getting new numbers. user will have to ctrl+c to quit
    while (true)
    {
        // get a new string
		retrieveValidInput();

		// fix for easy parsing
		normalizeInput();

		// set based on new string's length
		endsRemaining = (input.length() - 1) / 3;

		// parse number
		parse();

		// reset flags for each new string
		tensFlag = teensFlag = false;
    }
}

void Conversion::retrieveValidInput()
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

void Conversion::normalizeInput()
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

void Conversion::handleHundreds(int digit)
{
	// hundreds place digit
	if (digit > 0) 
	{
		// pull value from ones array and append "hundred"
		std::cout << ones[digit] << " hundred "; 
	}
}

void Conversion::handleTens(int digit)
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

void Conversion::handleOnes(int digit, int i)
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
				// ensure there is a number anywhere in the previous triplet to actually add an ending
				if (input[i-2] != 48 || input[i-1] != 48 || input[i] != 48)
				{
					//  output corresponding ending
					std::cout << endings[--endsRemaining] << " ";
				}
				else
				{
					endsRemaining--; 
				}
			} 
		}
	}
	//reset flags
	teensFlag = tensFlag = false; 
}

void Conversion::parse()
{
	for (int i = 0; i < input.length(); i++)
	{
		// triplet used to divide large numbers into sets of 3, 
		// digit converts char within string to its corresponding int value
		int triplet{ i % 3 }, digit{ int(input[i]) - 48 };

		if (triplet == 0)
			handleHundreds(digit);
		else if (triplet == 1)
			handleTens(digit);
		else
			handleOnes(digit, i);
	}
	
	// new line for next user prompt
	std::cout << std::endl;
}