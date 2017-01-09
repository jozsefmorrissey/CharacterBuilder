#include <string>
#include <fstream>
#include <sys/stat.h>
#include "Declaration.h"
#include <iostream>

/** 		Being a dev tool this class is not prepared for malicious input that being
 * 		said there are a few rules that need to be followed to insure text is read 	
 * 		properly.
 * 		1.	Make sure file compiles
 * 		2.	There can bee no spaces in between [::functionName(]
 * 		3.	To be safe do not leave spaces betwween variable declarations and 
 * 				thier modifiers i.e. 	good(char* x, vector<string> y)
 * 		  		                                    	bad(char * x, vector < string > y)
 */
class ReadH{

	private:
		ifstream inFile;
		bool found;
		string className;
		vector<Declaration> privateFuncs;
		vector<Declaration> protectedFuncs;
		vector<Declaration> publicFuncs;
	
		int read();
		bool findClass(string line);
		void setVector(string line, vector<Declaration>** vec);

		bool findDeclaration(string line, vector<Declaration>* funcs);

	public:
		ReadH(string fileName);
		~ReadH();

		vector<Declaration> getPrivateFunctions();
		vector<Declaration> getProtectedFunctions();
		vector<Declaration> getPublicFunctions();
		bool fileFound();
		bool continueReading();
		string getClassName();
};
