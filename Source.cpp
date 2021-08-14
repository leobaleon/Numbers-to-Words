/*
Author: Leonardo Baleon
Description: simple program that converts numbers into US English words.
Instructions: the user must not enter anything other than digits.
			  ListOfWords.hpp must be in the same directory.
			  Ctrl+C to quit the program.
*/

#include "Conversion.hpp"
#include "Conversion.cpp"

// driver function that starts by setting some basic variables all calling
// the necessary functions to get the program started.
int main(int argc, char** argv) 
{
	Conversion obj;
	obj.solution();
	return 0;
}