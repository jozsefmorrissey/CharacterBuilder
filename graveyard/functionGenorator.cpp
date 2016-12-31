//#include "functionGenorator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>

using namespace std;

struct variableAttr{
	char * type;
	char * name;
	bool constant;
};

int isolateByChar(char * arr[], char * line, const char * delim, int max);
int isolateByComma(char * arr[], char * line, int max);
int isolateBySpace(char * arr[], char * line, int max);

int split(char * function, char ** prefix, char ** suffix);
int parsePrefix(char * prefixArr[], int count);
int parseSuffix(char * suffixArr[], int count);

int getName(char * namePiece);
int getRetType(char * elements[], int start, int end);

int createVarStrut(char * pieces[], variableAttr * var, int start, int end);
int verifyAsters(char * pieces[], int start, int end);
int readFunction(char * func);
void print();

#define WORD_SIZE (256)

variableAttr params[20];
char  * stat = new char [WORD_SIZE];
variableAttr retType;
char * classs = new char [WORD_SIZE];
char * name = new char [WORD_SIZE];

int numParams = -1;


int main(int argc, char* argv[]) {

	char * func = new char [WORD_SIZE];
	strcpy(func ,"static const int * ** *** * * partyies::isolateByChar(char * arr[], char * line, const char * * *  * *** * delim, jaqline * fred, pizza sause);");
	readFunction(func);
}

int readFunction(char * func){
	char * prefix = new char [WORD_SIZE];
	char * suffix = new char [WORD_SIZE];
	char * prefixArr[50];
	char * suffixArr[50];

	split(func, &prefix, &suffix);



	int preCount = isolateBySpace(prefixArr, prefix, 50);
	numParams = isolateByComma(suffixArr, suffix, 50);
	

	if(parseSuffix(suffixArr, numParams)) 
		return 1;

	if(parsePrefix(prefixArr, preCount))
		return 1;
	print();

	return 0;
}

int parsePrefix(char * prefixArr[], int count){
	int targetPiece = 0;
	char * namePiece = prefixArr[count -1];
	if(!strcmp(prefixArr[targetPiece], "static")){
		stat = prefixArr[targetPiece];
		targetPiece++;
	}
	if(getName(namePiece) || getRetType(prefixArr, targetPiece, count))
		return 1;
	return 0;
}

int getRetType(char * elements[], int start, int end){
		if(createVarStrut(elements, &retType, start, end))//verifyAsters(elements, start, end))
			return 1;
	return 0;
}



int getName(char * namePiece){
	if(namePiece == NULL)
		return 1;

	if( strstr(namePiece, ":") == NULL) 
		strcpy(name , namePiece);
	else	{
	classs = strtok(namePiece, ":");
	name = namePiece + strlen(classs) + 2;
	}

	if (name == NULL)
		return 1;
	return 0;		
}

int parseSuffix(char * suffixArr[], int count){
	char * pieces[10];
	for(int i = 0; i < count; i ++){
		int numPiece = isolateBySpace(pieces, suffixArr[i], 10);
		if(numPiece == -1 || createVarStrut(pieces, &params[i], 0, numPiece))
			return 1;
	}
	return 0;
}

int createVarStrut(char * pieces[], variableAttr  * var, int start, int end){
	int targetPiece = start;
	

	if(!strcmp(pieces[targetPiece], "const")){
		var->constant = true;
		targetPiece++;
	}
	if (verifyAsters(pieces, targetPiece, end - 1))
		return 1;
	
	var->name = pieces[end - 1];
	var->type = pieces[targetPiece];
	return 0;
}

int verifyAsters(char * word, int start, int end){
	for(int j = start; j < end; j++)
		if(word[j] != '*')
			return 1;
	return 0;
}

int verifyAsters(char * pieces[], int start, int end){

	char * var = new char[128];
	strcpy(var, pieces[start ]) ;

	for(int i  = start + 1; i < end; i ++){
		int wordEnd = strlen(pieces[i]);
		if(verifyAsters(pieces[i], 0, wordEnd))
			return 1;
		strcat(var, pieces[i]);
	}
	strcpy(pieces[start], var);	
	return 0;
}

int isolateByComma(char * arr[], char * line, int max){
	return isolateByChar(arr, line, ",", max);
}

int isolateBySpace(char * arr[], char * line, int max){
	return isolateByChar(arr, line, " ", max);
}

int isolateByChar(char * arr[], char * line, const char * delim, int max){
	arr[0] = strtok(line, delim);		
	int index = 1;
	for(; index < max && arr[index -1] != NULL; index ++){
		arr[index] = strtok(NULL, delim);
		if(index == max)
			return -1;
	}
	return index - 1;
}


int split(char * function, char ** prefix, char ** suffix){
	*prefix = strtok(function, "(");
	*suffix = function + strlen(*prefix) + 1;
	char * endSuff = strstr(*suffix, ")");
	endSuff[0] = '\0';

	if(prefix == NULL)
		return 1;
	return 0;
}

void print(){
	cout << "\nstatic: " << stat << "\n";
	cout << "retType: " << retType.type << "\n";
	cout << "class: " << classs << "\n";
	cout << "name: " << name << "\n";
	cout << "variables: " << "\n";
	for(int i = 0; i < numParams; i++)
		cout << "\t\t" << i << ": " << params[i].type << " " <<params[i]. name << "\n";
	cout << "\n";
}











