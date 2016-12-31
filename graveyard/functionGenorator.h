#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>


class functionGenorator{

	private:
		char  * stat = new char [128];
		char * retType = new char [128];
		char * classs = new char [128];
		char * name = new char [128];
		char * args [20];
		char * types[20];

		int index = -1;

	void genFunc(char* function);
	void printFunctionBody();
	void printCommentSection();
	void printFunctionId(bool c);
	int parseInput(bool header);
	void printHeaderDeclaration(int index);

	public:
	void getStatic(char** func, char* tempStat);
	void eliminateWhiteSpace(char** func);
	int eliminateChar(char ** func, char target);
	int getReturnType(char ** func, char* tempRetType);

};




/*void functionGenorator::genFunc(char * func){
	char  * stat = new char [128];
	char * retType = new char [128];
	char * clas = new char [128];
	char * name = new char [128];
	char * args [20];
	char * types[20];

	stat = strtok(func, " ");
	int index = parseInput(&stat, &retType, &clas, &name, args, types, true);
	printCommentSection(index, args);
	printFunctionId(retType, clas, name, args, types, index, true);
	printFunctionBody(retType);
	printHeaderDeclaration(stat, retType, clas, name, args, types, index);
}

void functionGenorator::printHeaderDeclaration(char * stat,char * retType, char * clas, char * name, char * args[], char * types[], int index){
	std::cout << "\n\n\n"<< stat;
	printFunctionId(retType, clas, name, args, types, index, false);
	std::cout << ";\n\n";
}

void functionGenorator::printFunctionBody(char * retType){
	std::cout << "{\n\n\n";
	
	if(!strcmp("char", retType) || !strcmp("int", retType))
		std::cout << "return 0\n";
	else if(strcmp("void", retType))
		std::cout << "return NULL\n";

	std::cout << "}\n"	;


}

void functionGenorator::printCommentSection(int index, char * args[]){
std::cout << "\n/**\t\t\n * \t\t\n * \t\t\n";
	for(int i = 0; i < index; i++)
		std::cout << " * \t\t@param " << args[i] << " - \n";
	
	std::cout <<  " * \t\t@return \n */\n";
}

int functionGenorator::parseInput(char ** stat, char ** retType, char ** clas, char ** name, char * args[], char * types[], bool header){
	if(!strcmp("static", *stat)){
		*retType = strtok(NULL, " ");
		*stat = "static ";
	}
	else {
		*retType = *stat;
		*stat = "";
	}

	*clas = strtok(NULL, ":");
	*name = strtok(NULL, "(");
	int index = 0;
	types [index] = strtok(NULL, " ");

	args [index] = strtok(NULL, ", ");
	while (args[index] != NULL){
		index ++;
		types [index] = strtok(NULL, " ");
		args[index] = strtok(NULL, ", ");
	}
	args[index - 1] = strtok(args[index - 1], ")");

	return index;
}

void functionGenorator::printFunctionId(char * retType, char * clas, char * name, char * args[], char * types[], int index, bool c){	
	if (!c){
		clas = "";
		name = &name[1];
	}
	else {
		char * temp = new char [128];
		strcpy(temp, clas);
		strcat(temp, ":");
		clas = temp;
	}

	std::cout << retType  << " " << clas << name << "(";

	index = 0;
	while(args[index + 1] != NULL){
		std::cout << types[index]<< " " << args[index] << ", ";
		index ++; 
	}
	std::cout << types[index] << " " << args[index]; 
	std::cout << ")";
}


//static ret-type class::name(type arg1, ..., typeN argN){







