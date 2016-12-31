#include "FormatCPP.h"


int FormatCPP::openReadFile(const char * fileName){
	FILE * f = fopen(fileName, "r");
	if(f == NULL)
		return errno;

	file =f;

	return 0;		
}


int FormatCPP::openReadCppFile(){
	char * completeFileName;
	if((completeFileName = getCompleteSrcFileName(SRC_FILE_EXT)) == NULL)
		return EBADF;
	return openReadFile(completeFileName);
}


int FormatCPP::openReadHFile(){
	char * completeFileName;
	if((completeFileName = getCompleteSrcFileName(HEADER_FILE_EXT)) == NULL)
		return EBADF;
	return openReadFile(completeFileName);
}


char * FormatCPP::getCompleteSrcFileName(char * ext){
	char * fileN = new char[SMALL_STRING];
	if(fileName == NULL)
		return NULL;

	if(filePath == NULL)
		sprintf(fileN, "%s%s", fileName, ext);		
	else
		sprintf(fileN, "%s%s%s", filePath, fileName, ext);

	return fileN;
}


char * FormatCPP::getCompleteTestFileName(char * ext){
	char * fileN = new char[SMALL_STRING];
	if(fileName == NULL)
		return NULL;

	if(testPath == NULL)
		sprintf(fileN, "%sTEST%s", fileName, ext);		
	else
		sprintf(fileN, "%s%sTEST%s", testPath, fileName, ext);

	return fileN;
}


int FormatCPP::findClass(char * line){ return (size_t)strstr(line, "class ");}
int FormatCPP::findClassEnd(char * line){ return (size_t)strstr(line, "};");}
int FormatCPP::isComment(char * line){return (size_t)strstr(line, "//") || (size_t)strstr(line, "/*");}
int FormatCPP::findPublic(char * line){return (size_t)strstr(line, "public:") > (size_t)strstr(line, "private:");}
int FormatCPP::findPrivate(char * line){return (size_t)strstr(line, "public:") < (size_t)strstr(line, "private:");}
int FormatCPP::findEnum(char * line){return (size_t)strstr(line, "enum ");}

char * FormatCPP::findFunction(char * line){
	char * newLine = new char[SMALL_STRING];
	size_t lineSize;
	//ssize_t charRead = 0;
	if(strstr(line, "(") && !strstr(line, "#")){
		/*if(currentFileType == SRC){
			int openCount = StringManipulation::countChars(line, '{');
			int closeCount = StringManipulation::countChars(line, '}');
			bool functionStarted = openCount > 0 ? true : false;
			while((openCount != closeCount || !functionStarted) && charRead != -1){
				charRead = getline(&newLine, &lineSize, file);
				openCount += StringManipulation::countChars(line, '{');
				closeCount += StringManipulation::countChars(line, '}');
				strcat(line, newLine);
				functionStarted = openCount > 0 ? true : false;
			}
		}*/
		if(currentFileType == HEADER || TEST == currentFileType || currentFileType == SRC){
			while(!strstr(line, ")")){
				getline(&newLine, &lineSize, file);
				line = strcat(line, strtok(newLine, "\n"));
			}
		}
		delete newLine;
		//TODO::find and save body if it exits
		return line;
	}
	return NULL;
}


void FormatCPP::foundClass(char * line){
	line = strstr(line, "class") + 6;
	line = strtok(line, "{");

	for(size_t i = 0; i < strlen(line); i ++)
		if(*(line + i ) != ' ' && line[i] != '\t')
			sprintf(className, "%s%c", className, line[i]); 

}


void FormatCPP::foundClassEnd(){
	char * newClassName = new char[SMALL_STRING];
	char * temp2 = new char[SMALL_STRING];
	char * temp1 = strtok(className, "::");
	while(temp1 != NULL){
		strcat(newClassName, temp2);
		sprintf(temp2, "%s%s::", temp2, temp1);
		temp1 = strtok(NULL, "::");
		sprintf(temp2, "::%s", temp2);
	}
	newClassName[strlen(newClassName) - 2] = '\0';
	if(className != NULL)
		delete className;
	className = newClassName;
	delete temp2;
}


void FormatCPP::saveFunctionText(Function * func){
	functions[functionCount++] = new Function(func->getFunction());
	functions[functionCount -1]->setCode(func->getCode());
	
	func->print();
	functions[functionCount -1]->print();
}


void FormatCPP::saveCommentText(char * lines[], int size){
	char * comment;
	for(int ind = 0; ind < size; ind++){
		comment = removeLeadingWhiteSpace(lines[ind]);
		comment = removeLeadingCommentSymbols(comment);
		removeLeadingWhiteSpace(comment);

		if(strstr(comment, "@param") == comment)
			parameterComments[numParameterComments++] = comment;
		else
			commentLines[numCommentLines] = comment;
	}
}


char * FormatCPP::removeLeadingCommentSymbols(char * line){
	char * last;
	while (last != line){
		last = line;
		line = removeFromFront(line, "/");
		line = removeFromFront(line, "*");
	}
	return line;
}


char * FormatCPP::removeFromFront(char * line, const char * target){
	if(strstr(line, target) == line)
		line = line + strlen(target);
	return line;
}

char * FormatCPP::removeLeadingWhiteSpace(char * line){
	char * last;
	while (last != line){
		last = line;
		line = removeFromFront(line, " ");
		line = removeFromFront(line, "\t");
	}
	return line;
}


int FormatCPP::writeFile(char * fileName, char * text){
	if(!strcmp(text, "\n"))
		return ENOMEDIUM;
	FILE * f = fopen(fileName, "w");
	if(f == NULL)
		return errno;

	fputs(text, f);
	fclose(f);

	return 0;
}


void FormatCPP::compareFunctions(FormatCPP * other){
	for(int thisCount = 0; thisCount < this->functionCount; thisCount++){
		Function * thisFunc = this->functions[thisCount];
		for(int  otherCount = 0; otherCount < other->functionCount; otherCount++){
			Function * otherFunc = other->functions[otherCount];
			if(thisFunc->merge(otherFunc))
				break;
		}
	}
}


int FormatCPP::createCPPFile(){
	/*if(!openReadCppFile()){
		fclose(file);
		FormatCPP * existingFile = new FormatCPP();
		existingFile->setFileName(fileName);
		existingFile->readExistingCPP();
		compareFunctions(existingFile);
		delete existingFile;
	}*/


	char * text = createCPPText();

	char * fileName = getCompleteSrcFileName(SRC_FILE_EXT);
	return writeFile(fileName, text);
}


char * FormatCPP::createCPPText(){
	char * text = new char[LARGE_STRING];
	sprintf(text, "#include \"%s.h\"\n", fileName);
	
	for(int ind = 0; ind < functionCount - 1; ind++){
		strcat(text, "\n");
		strcat(text, functions[ind]->getCommentAndFunction());
		functions[ind]->print();
	}
	return text;
}


char * FormatCPP::createHeaderText(){
	char * text = new char[MED_STRING];
	sprintf(text, "\nclass %s{\n", className);
	
	for(int ind = 0; ind < functionCount - 1; ind++){
		strcat(text, functions[ind]->getDeclaration());
		strcat(text, "\n");
	}
	strcat(text, "};");
	return text;
}



int FormatCPP::createTestFiles(){
	char * text = createCPPText();
	char * fileName = getCompleteTestFileName(SRC_FILE_EXT);
	writeFile(fileName, text);

	text = createHeaderText();
	fileName = getCompleteTestFileName(HEADER_FILE_EXT);

	return writeFile(fileName, text);
}


int FormatCPP::generateCPP(){
	if(fileName == NULL)
		return EBADF;

	reset();	
	currentFileType = HEADER;

	int err;
	if((err = openReadHFile()))
		return err;

	 char * line = new char[SMALL_STRING];
	size_t numRead;
	while(getline(&line, &numRead, file) != -1){
		searchHeaderFile(line, false);
	}
	delete line;
	fclose(file);
	return createCPPFile();
}


int FormatCPP::readExistingCPP(){
	if(fileName == NULL)
		return EBADF;

	reset();	
	currentFileType = SRC;

	int err;
	if((err = openReadCppFile()))
		return err;

	 char * line = new char[SMALL_STRING];
	size_t numRead;

	while(getline(&line, &numRead, file) != -1){
		searchHeaderFile(line, false);
	}
	delete line;
	//fclose(file);
	return 0;
}


int FormatCPP::generateTests(){
	if(fileName == NULL)
		return EBADF;

	reset();	
	currentFileType = TEST;
	
	int err;
	if((err = openReadHFile()))
		return err;

	 char * line = new char[SMALL_STRING];
	size_t numRead;
	bool isPublic = false;
	while(getline(&line, &numRead, file) != -1){
		if(findPublic(line))
			isPublic = true;
		if(findPrivate(line))
			isPublic = false;
		searchHeaderFile(line, isPublic);
	}
	delete line;
	fclose(file);
	return createTestFiles();
}


void FormatCPP::searchHeaderFile(char * line, bool isPublic){
	if(findClass(line))
		foundClass(line);
	if(findClassEnd(line) && !findEnum(line))
		foundClassEnd();
	char * funcLine = findFunction(line);
	Function * func = new Function();
	if(funcLine != NULL){
	/*char * bodyLine = NULL;
		if(strstr(funcLine, "{")){
			bodyLine = new char[4096];
			strcpy(bodyLine, strstr(funcLine, "{"));
		}*/
		*func = Function(funcLine);
		//func->setCode(bodyLine);
		//func->print();
		if(func->isValid() && className != NULL)
				foundFunction(func, isPublic);		
	}
}


void FormatCPP::foundFunction(Function * func, bool isPublic){
	
		func->setClass(className);
	if(currentFileType == HEADER || currentFileType == SRC)	{
		saveFunctionText(func);
	}
	else if (isPublic && currentFileType == TEST){
		char * testName = new char[SMALL_STRING];
		sprintf(testName, "%sTEST", func->getName());
		func->setSrc(false);
		func->setName(testName);
		saveFunctionText(func);
	}
}


void FormatCPP::initialize(){
	SRC_FILE_EXT = new char[SMALL_STRING];
	HEADER_FILE_EXT = new char[SMALL_STRING];
	fileName = NULL;
	filePath = NULL;
	testPath = NULL;
	className = new char[SMALL_STRING];

	sprintf(SRC_FILE_EXT, ".cpp");
	sprintf(HEADER_FILE_EXT, ".h");
	
	currentFileType = EMPTY; 

	reset();
}


void FormatCPP::reset(){
	//delete[] functions;
	currentFileType = EMPTY;
	functionCount = 0;
	
	numParameterComments = 0;
	numCommentLines = 0;
}



/*	if(fileName == NULL)
		return EBADF;
	
	int err;
	if(err = openReadCppFile())
		return err;

	 char * line;
	int numRead;
	int lastComment = 0;
	char * commentLines[NUM_COMMENT_LINES];
	int commentCount;
	while(getline(&line, &numRead, file) != -1){
		if(lastComment > 3)
			numParameterComments = numCommentLines = lastComment = 0;
		if(lastComment > 0)
			lastComment++;
		while(isComment(line))
			strcpy(commentLines[commentCount++], line);
		if(commentCount > 0)
			saveCommentText(commentLines, commentCount);
		
	}*/














