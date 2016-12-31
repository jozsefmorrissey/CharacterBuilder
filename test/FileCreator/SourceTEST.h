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

		static void initializeTestFunctions();

	public:
		static int constructionTEST();
		static int getFunctionTEST();
		static int getTestFunctionTEST();
		static int getCommentTEST();
		static int getFunctionBodyTEST();
};



