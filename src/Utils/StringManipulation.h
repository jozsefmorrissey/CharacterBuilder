#include <stdio.h>
#include <stdlib.h>
#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef> 
#include <string.h>
#include <vector>

using namespace std;  


class StringManipulation{

	public:
	static char * removeLeadingCommentSymbols(char * line);
	static char * removeFromFront(char * line, const char * target);
	static char * removeLeadingWhiteSpace(char * line);
	static int countChars(char * haystack, char needle);

	static int countChars(string haystack, char needle);
	static int trimWhiteSpace(string * s);
	static string removeWhiteSpace(string s);
	static int removeLeadingWhiteSpace(string * s);

	static int removeFromRear(string * s, char target);
	static int removeFromFront(string * s, char target);
	static string removeCharacters(string haystack, string needles);

	static string cleanFunctionID(const char * function);

	static int tokenize(vector<string> * v, string s, char delimeter);
	static string vectorToLine(vector<string> vecS);

	static void inlineCharCompare(string str1, string str2);

	static string reverse(string str);

	static string removeSurroundedText(char start, char end, string str); 
	static string removeSurroundedText(string start, string end, string str);
} ;




