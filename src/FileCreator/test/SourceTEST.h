#include "../../src/FileCreator/Source.h"
#include <string>

class SourceTEST{

	private:
		static string function1;
		static string header1;
		static Declaration dec1;
		static Source src1;
		static string comment1;
		static string body1;

		static string function2;
		static string header2;
		static Declaration dec2;
		static Source src2;	
		static int constructionTEST();
		static void initializeTestFunctions();

	public:

		static int getFunctionTEST();
		static int getTestFunctionTEST();
		static int getCommentTEST();
		static int getFunctionBodyTEST();
		int isolateByChar(char * arr[], char * line, const char * delim, int max);
		int isolateByComma(char * arr[], char * line, int max);
		int isolateBySpace(char * arr[], char * line, int max);

		int split(char * function, char ** prefix, char ** suffix);
		int parsePrefix(char * prefixArr[], int count);
		int parseSuffix(char * suffixArr[], int count);

		int parseName(char * namePiece);
		int parseRetType(char * elements[], int start, int end);
		int addSomeShit(char * garb);
		int addSomemoreShit(char * garb);

		int createVarStrut(char * pieces[], variableAttr * var, int start, int end);
		int verifyAsters(char * pieces[], int start, int end);
		int verifyAsters(char * word, int start, int end);
		int readFunction(char * func);
		int parseFailed();

		char * getReturnComment();
		char * getCommentBody();
		char * getParameterComments();
		char * getParamComment(variableAttr var);

};



