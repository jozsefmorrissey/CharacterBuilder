#include "Function.h"


int Function::readFunction(char * func){
	char * prefix = new char [WORD_SIZE];
	char * suffix = new char [WORD_SIZE];
	char * prefixArr[50];
	char * suffixArr[50];

	if(func != NULL && strstr(func, ")") && strstr(func, "("))
		split(func, &prefix, &suffix);
	else
		return 1;

	int preCount = isolateBySpace(prefixArr, prefix, 50);
	numParams = isolateByComma(suffixArr, suffix, 50);
	

	if(parseSuffix(suffixArr, numParams)) 
		return parseFailed();

	if(parsePrefix(prefixArr, preCount))
		return parseFailed();

	return 0;
}

int Function::parseFailed(){
	numParams = -1;
	return 1;
}


int Function::parsePrefix(char * prefixArr[], int count){
	int targetPiece = 0;
	char * namePiece = prefixArr[count -1];
	if(!strcmp(prefixArr[targetPiece], "static")){
		stat = prefixArr[targetPiece];
		targetPiece++;
	}
	if(parseName(namePiece) || parseRetType(prefixArr, targetPiece, count))
		return 1;
	return 0;
}


int Function::parseRetType(char * elements[], int start, int end){
		retType = new variableAttr;
		if(createVarStrut(elements, retType, start, end))//verifyAsters(elements, start, end))
			return 1;
	return 0;
}


int Function::parseName(char * namePiece){
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


int Function::parseSuffix(char * suffixArr[], int count){
	char * pieces[10];
	for(int i = 0; i < count; i ++){
		int numPiece = isolateBySpace(pieces, suffixArr[i], 10);
		if(numPiece == -1 || createVarStrut(pieces, &params[i], 0, numPiece))
			return 1;
	}
	return 0;
}


int Function::createVarStrut(char * pieces[], variableAttr  * var, int start, int end){
	int targetPiece = start;

	if(!strcmp(pieces[targetPiece], "const")){
		var->constant = true;
		targetPiece++;
	}
	else{
		var->constant = false;
	}
	if (verifyAsters(pieces, targetPiece, end - 1))
		return 1;
	
	var->name = StringManipulation::removeLeadingWhiteSpace(pieces[end - 1]);
	var->type = StringManipulation::removeLeadingWhiteSpace(pieces[targetPiece]);
	return 0;
}


int Function::verifyAsters(char * word, int start, int end){
	for(int j = start; j < end; j++)
		if(word[j] != '*')
			return 1;
	return 0;
}


int Function::verifyAsters(char * pieces[], int start, int end){

	char * var = new char[128];
	strcpy(var, pieces[start ]) ;

	for(int i  = start + 1; i < end; i ++){
		int wordEnd = strlen(pieces[i]);
		if(verifyAsters(pieces[i], 0, wordEnd))
			return 1;
		strcat(var, pieces[i]);
	}
	strcpy(pieces[start], var);	
	delete var;
	return 0;
}


int Function::isolateByComma(char * arr[], char * line, int max){
	return isolateByChar(arr, line, ",", max);
}

int Function::isolateBySpace(char * arr[], char * line, int max){
	return isolateByChar(arr, line, " ", max);
}


int Function::isolateByChar(char * arr[], char * line, const char * delim, int max){
	arr[0] = strtok(line, delim);		
	int index = 1;
	for(; index < max && arr[index -1] != NULL; index ++){
		arr[index] = strtok(NULL, delim);
		if(index == max)
			return -1;
	}
	return index - 1;
}


int Function::split(char * function, char ** prefix, char ** suffix){
	*prefix = new char[WORD_SIZE];
	*prefix = strtok(function, "(");
	*suffix = new char[WORD_SIZE];
	*suffix = function + strlen(*prefix) + 1;
	char * endSuff = strstr(*suffix, ")");
	endSuff[0] = '\0';

	if(prefix == NULL)
		return 1;
	return 0;
}






char * Function::getArrguments(){
	char * arguments = new char[WORD_SIZE];
	arguments[0] = '\0';
	for(int i = 0; i < numParams; i++){
		if(params[i].constant){
			strcat(arguments, "const");
			strcat(arguments, " ");
		}
		strcat(arguments, params[i].type);
		strcat(arguments, " ");		
		strcat(arguments, params[i].name);
		if(i != numParams - 1)
			strcat(arguments, ", ");
		else
			strcat(arguments, "\0");
	}
	return arguments;
}


char * Function::getFunction(){
	char * func = new char[128];
	sprintf(func, "%s %s::%s(", getReturnType(), classs, name);
	if(src)
		strcat(func, getArrguments());

	strcat(func, ")");
	return func;
}

char * Function::getComplete(){
	char * complete = new char [128];
	sprintf(complete, "%s\n\n%s\n%s\n", getDeclaration(), getComment(), getFunction());
	return complete;
}

char * Function::getCommentAndFunction(){
	char * complete= new char[4096];
	sprintf(complete, "%s%s%s", getComment(), getFunction(), getFunctionBody());
	return complete;
}

char * Function::getFunctionBody(){
	char* body = new char[128];
	if(code){
		sprintf(body, "%s", getCode());
	}
	else{
		sprintf(body, "{\n%s", "\t//TODO: Implement\n");
	
		if(!strcmp("char", getReturnType()) || !strcmp("int", getReturnType()))
			strcat(body, "return 0;\n");
		else if(strcmp("void", getReturnType()))
			strcat(body, "return NULL;\n");

		strcat(body, "}\n");
	}

	return body;
}

char * Function::getCode(){
	if(!code)
		return NULL;

	char * c = new char[4096];
	sprintf(c, "%s", code);
	return c;
}


void Function::print(){
	cout << "\nstatic: " << stat << "\n";
	cout << "retType: " << getReturnType() << "\n";
	cout << "class: " << classs << "\n";
	cout << "name: " << name << "\n";
	cout << "code: " << getCode() << "\n";
	cout << "variables: " << "\n";
	for(int i = 0; i < numParams; i++)
		cout << "\t\t" << i << ": " << params[i].type << " " <<params[i]. name << "\n";
	cout << "\n";
}

char* Function::getDeclaration(){
	char * declaration = new char[128];
	sprintf(declaration, "%s %s %s(",stat, getReturnType(), name);
	if(src)
		strcat(declaration, getArrguments());
	
	strcat(declaration, ");");
	return declaration;
}


char* Function::getComment(){
	char * comment = new char[4096];
	sprintf(comment,"\n/**\t\t%s\n * \t\t\n", getCommentBody());
	if(src){
		strcat(comment, getParameterComments());

		if(strcmp(getReturnType(), "void"))
			strcat(comment, getReturnComment());
	}
	strcat(comment, " */\n");

	return comment;
}

char * Function::getReturnComment(){
	char * rc = new char [256];
	if(commentReturn)
		sprintf(rc, "%s", commentReturn);
	else
		sprintf(rc, " * \t\t@return - TODO: comment on return value\n");
	return rc;
}


char * Function::getCommentBody(){
	char * cb = new char[256];
	if(commentBody)
		sprintf(cb, "%s", commentBody);
	else
		sprintf(cb, "TODO: comment on function use");
	return cb;
}

char * Function::getParameterComments(){
	char * retVal = new char[4096];
	for(int i = 0; i < numParams; i++){
		strcat(retVal, getParamComment(params[i]));
	}
	return retVal;
}


char * Function::getParamComment(variableAttr var){
	for(int i = 0; i < cPcount; i ++)
		if(strstr(commentParams[i], var.name))
			return commentParams[i];

	char * comment = new char[4096];
	strcat(comment, " * \t\t@param ");
	strcat(comment, var.name);
	strcat(comment, " - TODO: comment of parameter\n");
	return comment;
}



int Function::setFunction(char * func){
	if(readFunction(func))
		return 1;
	return 0;
}


bool Function::isValid(){
	return numParams != -1;
}


char * Function::getClass(){
	return classs;
}


char * Function::getName(){
	return name;
}


int Function::getParameters(void * memLoc){
	for(int index = 0; index < numParams; index++){
		memcpy(&memLoc + index, &params[index], sizeof(variableAttr));
	}
	return numParams;
}


char * Function::getReturnType(){
	if(retType == NULL)
		return NULL;

	char * c = new char[128];
	if(src){
	if(retType->constant)
		sprintf(c, "const ");
	strcat(c, retType->type);
	} else
		sprintf(c, "int");
	return c;
}



bool Function::cmp(Function * func){
	if(!strcmp(this->getDeclaration(), func->getDeclaration()) && !strcmp(this->getClass(), func->getClass()))
		return 1;

	return 0;
}


bool Function::merge(Function * func){
	if(!this->cmp(func))
		return false;

	if(func->code){
		this->code = new char [4096];
		strcpy(this->code, func->code);
	}

	this->cPcount = func->cPcount;

	if(func->commentBody){
		this->commentBody = new char[4096];
		strcpy(this->commentBody, func->commentBody);
	}

	if(func->commentReturn){
		this->commentReturn = new char[256];
		strcpy(this->commentReturn, func->commentReturn);
	}

	for(int index = 0; index < func->cPcount; index++){
		this->commentParams[index] = new char[256];
		strcpy(this->commentParams[index], func->commentParams[index]);
	}
	
	return true;
}


//void Function::copy(Function * func){
//	func->stat = this->stat;
//	func->retType 
//}





