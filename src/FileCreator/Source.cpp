#include "Source.h"

using namespace std;



Source::~Source(void){
}


Source::Source(){
	initialize();
}


Source::Source(string func){
	initialize();
	parse(func);
}


/**		Initializse values 		
 */
void Source::Initialize(){
	commentBody = "";
	functionBody = "";
	Declaration::initialize();
}


/**		The return value is not important for this class but it is for the parent class.
 * 		
 * 		@return - 0 on success
 */
int Source::parse(string func){
	//Error err = Error();
	if(!getCommentSection(&func) || !getFunctionBody(&func) || !removeClassName(&func))
		return 1;

	Declaration::create(func);
return 0;
}


/**		
 * 		@return - True if a body incapsulated by {} exists
 */
bool Source::removeClassName(string * func){
	Error err = Error();

	size_t classNameEnd = func->find("::");
	if(classNameEnd == string::npos){
		err.negative_1_error(-1, "Double colons not found", __LINE__ - 1, __PRETTY_FUNCTION__);
		return false;
	}
	
	string front = func->substr(0, classNameEnd);
	size_t classNameStart = front.rfind(" ");

	if(classNameStart == string::npos){
		err.negative_1_error(-1, "no return value", __LINE__ - 1, __PRETTY_FUNCTION__);
		return false;
	}	
	
	front = front.substr(0, classNameStart + 1);
	className = func->substr(classNameStart +1, classNameEnd - classNameStart - 1);
	*func = front + func->substr(classNameEnd + 2);


	return true;
}

/**		This function assumes the line given to it contains bracketing for only one function and
 * 		the brackets are equal and correct.
 * 		
 * 		@return - True if a body incapsulated by {} exists
 */
bool Source::getFunctionBody(string * func){
	Error err = Error();

	size_t bodyStart = func->find("{");
	size_t bodyEnd = func->rfind("}");

	bool bracketsReversed = (bodyStart > bodyEnd);
	bool missingBrackets = (bodyStart == string::npos || bodyEnd == string::npos);
	if(bracketsReversed || missingBrackets){
		err.negative_1_error(-1, "Function Body Incorrect", __LINE__ - 1, __PRETTY_FUNCTION__);
		return false;
	}

	functionBody = func->substr(bodyStart, bodyEnd - bodyStart +1) + "\n\n";
	*func = func->substr(0, bodyStart);

	return true;
}

/**		
 * 		@return - True if a comment is in the propper form or does not exist
 */
bool Source::getCommentSection(string * func){
	Error err = Error();

	size_t startComment = func->find("/**");
	size_t endComment = func->find("*/");

	bool reverseCommentMarkers =  startComment > endComment;
	bool noComment = (startComment ==  string::npos && endComment == string::npos);
	bool missingMarker = (startComment ==  string::npos || endComment == string::npos);
	if(reverseCommentMarkers || (missingMarker && !noComment)){
		err.negative_1_error(-1, "Comment Symbols Incorrect", __LINE__ - 1, __PRETTY_FUNCTION__);
		return false;
	}
	
	if(noComment)
		return true;

	commentBody = func->substr(startComment, endComment - startComment + 2) + "\n";
	*func = func->substr(endComment + 2);

	return true;
}


/**		Prints member variables primarily for debbuging.
 */
void Source::print(){
	Declaration::print();
	cout << "Comment Body:\n" << commentBody;
	cout << "\nFunction Body:\n" << functionBody;
}


/**		
 * 		@return - Existing parsed comment or a template
 */
string Source::getComment(){
	return commentBody.compare("") ? commentBody : Declaration::getComment() ;
}


/**		
 * 		@return - Existing parsed function body or a template
 */
string Source::getFunctionBody(){
	return functionBody.compare("{}\n\n") ? functionBody : Declaration::getFunctionBody();
}


/**		
 * 		@return - true if the source declarations are the same.
 */
bool Source::compare(Declaration dec){
	return !this->getFunctionDefinition().compare(dec.getFunctionDefinition());
}



