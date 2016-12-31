#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>
#include <errno.h>

#include "Function.h"


using namespace std;

class FormatCPP{
private:
	#define NUM_FUNCTIONS (1024)
	#define NUM_COMMENT_LINES (24)
	#define SMALL_STRING (256)
	#define MED_STRING (4096)
	#define LARGE_STRING (131072)

	char * SRC_FILE_EXT;
	char * HEADER_FILE_EXT;

	enum FileType {SRC, HEADER, TEST, EMPTY};

	FILE * file;
	FileType currentFileType; 
	const char * fileName;
	const char * filePath;
	const char * testPath;
	char * className;

	int functionCount;
	Function * functions[NUM_FUNCTIONS];

	int numParameterComments;
	int numCommentLines;
	char * commentLines[NUM_COMMENT_LINES];
	char * parameterComments[NUM_COMMENT_LINES];

	int openReadFile(const char * fileName);
	int openReadCppFile();
	int openReadHFile();

	void foundClass(char * line);
	void foundClassEnd();
	void foundFunction(Function * func, bool isPublic);

	int findClass(char * line);
	int findClassEnd(char * line);
	char * findFunction(char * line);
	int isComment(char * line);
	int findPublic(char * line);
	int findPrivate(char * line);
	int findEnum(char * line);

	int writeFile(char * fileName, char * text);

	int createCPPFile();
	int createTestFiles();
	char * createCPPText();
	char * createHeaderText();

	char * removeLeadingWhiteSpace(char * line);	
	char * removeFromFront(char * line, const char * target);
	char * removeLeadingCommentSymbols(char * line);

 	void saveFunctionText(Function * func);
	//void saveHeaderText(Function func);
	void saveCommentText(char * lines[], int size);

	 char * getCompleteSrcFileName(char * ext);
	char * getCompleteTestFileName(char * ext);

	void searchHeaderFile(char * line, bool isPublic);

	void initialize();
	void reset();

public:

	FormatCPP(){
	initialize();

}

	void compareFunctions(FormatCPP * other);

	int generateCPP();	
//	int updateComments();
	int readExistingCPP();
	int generateTests();

	void setFileName(const char * name){
			fileName = new char[SMALL_STRING];
			fileName = name;
	}

	void setFilePath(const char * path){
			filePath = new char[SMALL_STRING];
			filePath = path;
	}

	void setTestFilePath(const char * path){
	testPath = new char[SMALL_STRING];
		testPath = path;
	}

};






