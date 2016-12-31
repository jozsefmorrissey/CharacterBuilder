#include <string>
#include <fstream>
#include "Source.h"
#include <iostream>


/** 		Being a dev tool this class is not prepared for malicious input that being
 * 		said there are a few rules that need to be followed to insure text is read 	
 * 		properly.
 * 		1.	Make sure file compiles
 * 		2.	There can bee no spaces in between [::functionName(]
 * 		3.	To be safe do not leave spaces betwween variable declarations and 
 * 				thier modifiers i.e. 	good(char* x, vector<string> y)
 * 		  		                                    	bad(char * x, vector < string > y)
 * 		4.	When declaring variables in a source file make sure the assignment
 * 				operator  is on the same line as the declaration and name of variable.
 */
using namespace std;

class ReadCpp{

	private:

		vector<Source> functions;
		vector<string> variables;
		vector<string> unparsed;
	
		int read();
		bool findVariable(string line);
		bool findComment(string line);
		bool findFunction(string line);
		bool parseFunction(string * line);
	
	public:
		fstream inFile;
		ReadCpp(string fileName);
		~ReadCpp();

		vector<Source> getFunctions();
		vector<string> getVariables();
		vector<string> getUnparsed();
};


