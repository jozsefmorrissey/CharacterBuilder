#include "Declaration.h"

using namespace std;




Declaration::Declaration(){initialize();}


/**		primary constructor
 * 		
 * 		@param dec - string Containing function
 */
Declaration::Declaration(string dec, string cN){
	initialize();
	className = cN;
	create(dec);

}


/**		provided to change the declaration that dictates the function outputs
 *			if parse fails existing function will also no longer be availible.	
 */
bool Declaration::create(string dec){
	if(Declaration::parse(dec))
		functionName = "";
	return functionName != "";
}

/**		Used to initialize variables to conform with older versions of cpp		
 */
void Declaration::initialize(){
	returnType = "";
	className = "";
	functionName = "";
	isVirtual = false;
	isStatic = false;
}


/*		If fuctionName is the empty string the funtion is not valid
 *			Function name is used since users have no control over it
 */
bool Declaration::functionValid(){
	return functionName.compare("") && className.compare("");
}


/**		As the class name indicates this function parses cpp declaration lines to be 
 *			used in code generation.
 * 		
 * 		@return - 0 on success
 */
int Declaration::parse(string text){
	Error err = Error(false);
	size_t openParen = text.find_first_of("(");
	size_t closeParen = text.find_first_of(")");

	if(!verifyDeclartion(text))
		return 1;
	
	string front = text.substr(0, openParen);

	string args;
	if(openParen +1 != closeParen)
		args = text.substr(openParen + 1, closeParen - openParen - 1);
	else
		args = "";

	removeDecSpecKeywords(&front);

	size_t nameStart = front.find_last_of(" ");
	if(nameStart == string::npos && (!front.compare(className) || !front.compare("~" + className))){
			returnType = "";
			functionName = front;
	}
	else{
		returnType = front.substr(0, nameStart);
		if(varifyVariable(returnType + " fakeName")){
			err.negative_1_error(-1, "return type format not correct", __LINE__ - 1, __PRETTY_FUNCTION__);
			return 1;
		}
	}

	functionName = front.substr(nameStart + 1);

	StringManipulation::tokenize(&arguments, args, ',');
	if(!verifyArguments())
		return 1;
	
return 0;
}


/**		Verifies arguments parsed are in the correct form
 */
bool Declaration::verifyArguments(){
	Error err = Error();
	for(vector<string>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
		StringManipulation::trimWhiteSpace(&(*it));
		if(varifyVariable(*it)){
			string msg = "Argument '";
			msg += *it + "' formate not correct";
			err.negative_1_error(-1, msg.c_str(), __LINE__ - 3, __PRETTY_FUNCTION__);
			return false;
		}
	}
	return true;
}


/**		Finds and removes declaration specific keywords
 */
void Declaration::removeDecSpecKeywords(string * front){
	StringManipulation::trimWhiteSpace(front);
	if(front->find("virtual ") != string::npos){
		isVirtual = true;
		*front = front->substr(front->find_first_of(" ") + 1);
	}
	else if(front->find("static ") != string::npos){
		isStatic = true;
		*front = front->substr(front->find_first_of(" ") + 1);
	}
}


/**		
 * 		@return - True if the dec has neccisary atributes to begin parsing
 */
bool Declaration::verifyDeclartion(string text){
	size_t openParen = text.find_first_of("(");
	size_t closeParen = text.find_first_of(")");

	if(openParen == string::npos || closeParen == string::npos || openParen > closeParen || text.find_first_of(":") != string::npos  || text.find_first_of("#") != string::npos ){
		Error err = Error();
		err.negative_1_error(-1, "Header string format not correct", __LINE__ - 1, __PRETTY_FUNCTION__);
		return false;
	}
	return true;
}


/**		
 * 		@return - returns true if there are only two words, three if const is present, and astericies
 */
bool Declaration::varifyVariable(string var){
	vector<string> elements;
	int wordCount = 0;
	StringManipulation::tokenize(&elements, var, ' ');

	for(vector<string>::iterator it = elements.begin(); it != elements.end(); ++it) {
		if(it != elements.begin() || it->compare("const"))
			for(size_t index = 0; index < it->size(); index++)
				if(it->at(index) != '*' && it->at(index) != '[' && it->at(index) != ']'){
					wordCount++;
					break;
				}
	}
	return wordCount != 2;
}


/**		Prints member variables primarily for debbuging.
 */
void Declaration::print(){
	cout << "Class Name: \t" << className;
	cout << "\nFunction Name \t" << functionName;
	cout << "\nReturn Type: \t" << returnType;
	cout << "\nVirtual: \t" << (isVirtual ? "Yes" : "No");
	cout << "\nStatic: \t" << (isStatic ? "Yes" : "No");
	cout << "\nArguments:\n";
	for(int index = 0; index < (int)arguments.size(); index++)
		cout << "\t\t" << getArgument(index) <<  "\n";
}


/**				
 * 		@return - Function Implementation complete with comment template and empty body.
 */
string Declaration::getFunction(){
	return getComment() + getFunctionDefinition() + getFunctionBody();
}


/**				
 * 		@return - Source file function Definition
 */
string Declaration::getFunctionDefinition(){
	string rT = returnType.compare("") ? returnType + " " : "";
	return rT + className + "::" + functionName + "(" + getArguments() + ")" ;
}


/**				 		
 * 		@return - Test function Implementation complete with comment template and empty body.
 */
string Declaration::getTestFunction(){
	return "\n/**\t\t\n *\t\tTODO: comment on function use\n */\nint " + className + "TEST::" + functionName + "TEST()" + "{\n\t//TODO: Implement\n\treturn 0;\n}\n";
}


/**		
 * 		@return - Comment template
 */
string Declaration::getComment(){
	string comment = "\n/**\t\tTODO: comment on function use\n *\t\t\n";

	for(vector<string>::iterator it = arguments.begin(); it != arguments.end(); ++it) 
			comment += " *\t\t@" + it->substr(it->find_last_of(" ") + 1) + " - \n";

	if(returnType.compare("void"))
		comment += " *\t\t@return - TODO: comment on return value\n";

	comment += " */\n";
	return comment;
}


/**		
 * 		@return - empty function value with appropriate return statment
 */
string Declaration::getFunctionBody(){
string funcBody = "{\n\t//TODO: Implement\n" ;

if(!returnType.compare("int") || !returnType.compare("char"))
	funcBody += "\treturn 0;";
else if(returnType.compare("void"))
	funcBody += "\treturn NULL;";

return funcBody + "\n}\n";
}


/**		
 * 		@return - className.h function Declaration
 */
string Declaration::getDeclaration(){
	string dec = "";
	string rT = returnType.compare("") ? returnType + " " : "";
	return dec + (isVirtual ? "virtual " : "") + (isStatic ? "static " : "") + rT + functionName + "(" + getArguments() + ");"; 
}


/**		
 * 		@return - classNameTEST.h function Declaration
 */
string Declaration::getTestDeclaration(){
	return "int " + functionName + "TEST();"; 
}



string Declaration::getClassName(){return className;}
string Declaration::getFunctionName(){return functionName;}


/**		
 * 		@return - returns the arguments in the form [type1 arg1, type2 arg2, ... , typeN argN]
 */
string Declaration::getArguments(){
	string args = "";
	if(arguments.size() == 0)
		return "";
	for(vector<string>::iterator it = arguments.begin(); it != arguments.end(); ++it) 
		args += *it + ", ";

	args.replace(args.end() - 2, args.end(), "");
return args;
}


/**		
 * 		@param i - index of the argument to be returned
 * 		@return - argument string
 */
string Declaration::getArgument(int i){return arguments.at(i);}

/**		
 * 		@return - true if the source declarations are the same.
 */
bool Declaration::compare(Declaration dec){
	return !this->getFunctionDefinition().compare(dec.getFunctionDefinition());
}











