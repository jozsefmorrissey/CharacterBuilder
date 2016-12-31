#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>

#include "../../src/Utils/StringManipulation.h"

using namespace std;

struct variableAttr{
	char * type;
	char * name;
	bool constant;
};

class Function{
	private:
		#define WORD_SIZE (256)

		variableAttr params[20];
		char  * stat;
		variableAttr * retType;
		char * classs;
		char * name;
		bool src;

		char * commentBody;
		int cPcount;
		char * commentParams[];
		char * commentReturn;
		char * code = NULL;

		int numParams;

		void initialize(){
		stat = new char [WORD_SIZE];
		classs = new char [WORD_SIZE];
		name = new char [WORD_SIZE];

		commentBody = NULL;
		//code = NULL;
		commentReturn = NULL;
		retType = NULL;
		cPcount = 0;
		numParams = -1;
		src = true;
		}

		int isolateByChar(char * arr[], char * line, const char * delim, int max);
		int isolateByComma(char * arr[], char * line, int max);
		int isolateBySpace(char * arr[], char * line, int max);

		int split(char * function, char ** prefix, char ** suffix);
		int parsePrefix(char * prefixArr[], int count);
		int parseSuffix(char * suffixArr[], int count);

		int parseName(char * namePiece);
		int parseRetType(char * elements[], int start, int end);

		int createVarStrut(char * pieces[], variableAttr * var, int start, int end);
		int verifyAsters(char * pieces[], int start, int end);
		int verifyAsters(char * word, int start, int end);
		int readFunction(char * func);
		int parseFailed();

		char * getReturnComment();
		char * getCommentBody();
		char * getParameterComments();
		char * getParamComment(variableAttr var);

	public:

		Function(){initialize();}

		Function(char * func){
			initialize();
			if(readFunction(func)) 
				numParams = -1;
		}

		/*~Function(){
		//variableAttr parsams[20];
		delete stat;
		delete retType;
		delete classs;
		delete name;

		delete commentBody;
		//delete commentParams[];
		delete commentReturn;
		delete code;
		}*/

		int setFunction(char* func);
		bool isValid();
		char * getClass();
		char * getName();
		int getParameters(void * memLoc);
		char * getReturnType();

		char * getArrguments();
		char* getDeclaration();
		char* getFunction();
		char* getComment();
		char * getCommentAndFunction();
		char* getFunctionBody();
		char* getComplete();
		char * getCode();

		void setClass(char * c){classs = c;}
		void setName(char * n){name = n;}
		void setSrc(bool s){src = s;}
		void setCode(char * c){code = c;}

		bool merge(Function * func);
		bool cmp(Function * func);
		void print();
};



















