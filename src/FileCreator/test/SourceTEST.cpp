#include "SourceTEST.h"


//--------------------------  Variables  --------------------------//


string SourceTEST::function1 = "/**\t\tTODO: comment on function use - check\n *\t\t\n *\t\t@line - \n *\t\t@target - \n *\t\t@happyThoughts - \n *\t\t@return - TODO: comment on return value\n */\nchar * StringManipulation::removeFromFront(char [][] line, const char * target, vector happyThoughts){}\n\n";

string SourceTEST::header1 = "char * removeFromFront(char [][] line, const char * target, vector happyThoughts);";

Declaration SourceTEST::dec1 = Declaration(header1, "StringManipulation");

Source SourceTEST::src1 = Source(function1);

string SourceTEST::comment1 = "/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@line - \n *\t\t@target - \n *\t\t@happyThoughts - \n *\t\t@return - TODO: comment on return value\n */";

string SourceTEST::body1 = "{\n\t//TODO: Implement\n\treturn NULL;\n}\n";

string SourceTEST::function2 = "string Declaration::getArguments(){\n\tstring args = \"\";\n\tif(arguments.size() == 0)\n\treturn \"\";\n\tfor(vector<string>::iterator it = arguments.begin(); it != arguments.end(); ++it)\n\t\targs += *it + \", \";\n\n\t	args.replace(args.end() - 2, args.end(), "");\n\treturn args;\n}\n\n";

string SourceTEST::header2 = "virtual string getArguments();";

Declaration SourceTEST::dec2 = Declaration(header2, "Declaration");

Source SourceTEST::src2 = Source(function2);


//--------------------------  Private  --------------------------//


/**		tests that source and declarations created from pared statments can 
 * 		be accratly compared to each other.
 * 		
 * 		@return - 0 on success
 */
int SourceTEST::constructionTEST(){
	Error err = Error();

	if(!src1.compare(dec1) || !src2.compare(dec2)){
		err.non_zero_error(1, "Src declaration and header declaration comparison failure", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

		if(src2.compare(dec1) || src1.compare(dec2)){
		err.non_zero_error(1, "Src declaration and header declaration comparison failure", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

return 0;
}


/**		TODO: comment on function use
 *		
 */
void SourceTEST::initializeTestFunctions(){
	//TODO: Implement

}



//--------------------------  Public  --------------------------//


/**		This tests that parsed comments and functionbodies are being saved and reproduced
 * 		
 * 		@return - 1 on error
 */
int SourceTEST::getFunctionTEST(){
	Error err = Error();

	string func1 = function1.substr(0, function1.size() - 4) + body1;
	if(src1.getFunction().compare(func1)){
		err.non_zero_error(1, "Function failed to create properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}



	string commTemplate = "\n/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@return - TODO: comment on return value\n */\n";
	if(src2.getFunction().compare(commTemplate + function2)){
		err.non_zero_error(1, "Function failed to create properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}


return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int SourceTEST::getTestFunctionTEST(){
	//TODO: Implement
	return 0;
}


/**		used to narrow error search
 * 		
 * 		@return - 0 on success
 */
int SourceTEST::getCommentTEST(){
	Error err = Error();

	string comm1 = "/**\t\tTODO: comment on function use - check\n *\t\t\n *\t\t@line - \n *\t\t@target - \n *\t\t@happyThoughts - \n *\t\t@return - TODO: comment on return value\n */\n";

	if(src1.getComment().compare(comm1)){
		err.non_zero_error(1, "Comment was not saved successfully", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	string commTemplate = "\n/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@return - TODO: comment on return value\n */\n";
	if(src2.getComment().compare(commTemplate)){
		err.non_zero_error(1, "Comment was not added successfully", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

return 0;
}


/**		used to narrow error search
 * 		
 * 		@return - 0 on success
 */
int SourceTEST::getFunctionBodyTEST(){
	Error err = Error();

	if(src1.getFunctionBody().compare(body1)){
		err.non_zero_error(1, "Body was not created successfully", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	string func2body = "{\n\tstring args = \"\";\n\tif(arguments.size() == 0)\n\treturn \"\";\n\tfor(vector<string>::iterator it = arguments.begin(); it != arguments.end(); ++it)\n\t\targs += *it + \", \";\n\n\t	args.replace(args.end() - 2, args.end(), "");\n\treturn args;\n}\n\n";
	if(src2.getFunctionBody().compare(func2body)){
		err.non_zero_error(1, "Body was not saved successfully", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}


return 0;
}


/**		TODO: comment on function use
 *		
 *		@arr[] - 
 *		@line - 
 *		@delim - 
 *		@max - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::isolateByChar(char * arr[], char * line, const char * delim, int max){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@arr[] - 
 *		@line - 
 *		@max - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::isolateByComma(char * arr[], char * line, int max){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@arr[] - 
 *		@line - 
 *		@max - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::isolateBySpace(char * arr[], char * line, int max){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@function - 
 *		@prefix - 
 *		@suffix - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::split(char * function, char ** prefix, char ** suffix){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@prefixArr[] - 
 *		@count - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::parsePrefix(char * prefixArr[], int count){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@suffixArr[] - 
 *		@count - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::parseSuffix(char * suffixArr[], int count){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@namePiece - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::parseName(char * namePiece){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@elements[] - 
 *		@start - 
 *		@end - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::parseRetType(char * elements[], int start, int end){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@garb - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::addSomeShit(char * garb){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@garb - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::addSomemoreShit(char * garb){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@pieces[] - 
 *		@var - 
 *		@start - 
 *		@end - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::createVarStrut(char * pieces[], variableAttr * var, int start, int end){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@pieces[] - 
 *		@start - 
 *		@end - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::verifyAsters(char * pieces[], int start, int end){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@word - 
 *		@start - 
 *		@end - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::verifyAsters(char * word, int start, int end){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@func - 
 *		@return - TODO: comment on return value
 */
int SourceTEST::readFunction(char * func){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int SourceTEST::parseFailed(){
	//TODO: Implement
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
char * SourceTEST::getReturnComment(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
char * SourceTEST::getCommentBody(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
char * SourceTEST::getParameterComments(){
	//TODO: Implement
	return NULL;
}


/**		TODO: comment on function use
 *		
 *		@var - 
 *		@return - TODO: comment on return value
 */
char * SourceTEST::getParamComment(variableAttr var){
	//TODO: Implement
	return NULL;
}



//--------------------------  Not Declared  --------------------------//

/**		TODO: comment on function use
 *		
 */
void SourceTEST::garbage(){	Error err = Error();




return 0;
}

