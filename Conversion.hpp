#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <iostream>
#include "ListsOfWords.hpp"

class Conversion
{
public:
    // default constructor
    Conversion();

    // function to begin the Numbers to Words app
    void solution();

    // prompts the user for a positive number and validates the input
    // before allowing the program to perform any parsing on the string
    void retrieveValidInput();

    // ensures that the string contains a total length that is a multiple of 3.
    // this is done to simplify the parsing of the entire string since numbers
    // are essentially written out based on 3 numbers at a time. ex:
    // 0 001 =                                 one 
    // 0 021 =                          twenty-one
    // 0 121 =              one hundred twenty-one
    // 2 121 = two thousand one hundred twenty-one
    void normalizeInput();

    // checks the first digit of each triplet for a value greater than
    // 0, if one exists, it simply appends the word "hundred" as necessary
    void handleHundreds(int digit);

    // checks if the value in the ones place is a '1', since it will then
    // need to use the corresponding teen naming instead of a hyphenated
    // combination of a tens value and a ones value. ex:
    // 17 = seventeen VS 27 = twenty-seven
    // note: this function only sets flags for the next function, handleOnes,
    // to perform the actual distinctions and printing of words
    void handleTens(int digit);

    // checks if flags were triggered by the handleTens function to perform
    // the correct printing of words. also, makes sure to print hyphens if needed,
    // and resets flags for the next triplet in the overall number
    void handleOnes(int digit, int i);

    // simply calculates the total number of triplets in the overall number
    // provided by the user. this function will loop once for each triplet and
    // make the corresponding function calls to handle each digit's place
    void parse();

private:
    // string used to store user input
    std::string input;

    // ends remaining used to determine which ending should be used in the large array
    unsigned long endsRemaining;
	
    // flags to decide between using ones values or teens values or adding dashes
    bool tensFlag, teensFlag;
};

#endif
