#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
		
#include "../Utils/Error.h"


using namespace std;
	

class Declaration{

protected:
	string returnType;
	string className;
	string functionName;
	vector<string> arguments;
	bool isVirtual;
	bool isStatic;

	virtual void initialize();
	virtual int parse(string line);	
	bool varifyVariable(string var);
	bool verifyDeclartion(string dec);
	bool verifyArguments();
	void removeDecSpecKeywords(string * front);

public:

	Declaration();
	Declaration(string dec, string cN);
	
	virtual string getComment();
	virtual string getFunctionBody();

	virtual void print();
	bool compare(Declaration other);
	bool functionValid();	

	string getFunctionDefinition();
	string getDeclaration();
	string getTestDeclaration();
	string getClassName();
	string getFunctionName();
	string getArguments();
	string getArgument(int i);
	string getFunction();
	string getTestFunction();

	void setClassName();
	bool create(string dec);
};

#endif //DECLARATION_H
