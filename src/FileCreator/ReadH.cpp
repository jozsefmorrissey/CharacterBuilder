#include "ReadH.h"


ReadH::ReadH(string fileName){
	inFile.open(fileName.c_str());
	className = "";
	found = true;

	if(!read())
		found = false;
}


ReadH::~ReadH(){
	inFile.close();
	privateFuncs.clear();
	protectedFuncs.clear();
	publicFuncs.clear();
}



/**		Reads through source file line by line looking for variables, commented functions, and functions.
 * 		
 * 		@return - true if file was successfully opened
 */
int ReadH::read(){
	if(!inFile.good())
		return 0;

	vector<Declaration>* currVect = &privateFuncs;
	string line;
	while(getline(inFile, line)){
		if(findClass(line))
			currVect = &privateFuncs;
		if(className.compare("")){
			setVector(line, &currVect);
			findDeclaration(line, currVect);
		}
	}

return 1;
}


/**		TODO: comment on function use
 * 		
 * 		@return - TODO: comment on return value
 */
bool ReadH::findClass(string line){
	size_t c = line.find("class ");
	if(c == string::npos)
		return false;

	string cName = line.substr(c + 6);
	cName = StringManipulation::removeWhiteSpace(cName);
	 
	size_t bracket =cName.find("{");
	size_t colon = cName.find(":");
	size_t newLine = cName.find("\n");

	if(colon != string::npos)
		className = cName.substr(0, colon);
	else if(bracket != string::npos)
		className = cName.substr(0, bracket);
	else
		className = cName.substr(0, newLine);

return true;
}


/**		
 * 		This function changes the vector that is being added to based on when it finds an access
 * 		specifier. Note: I role over the max value string::npos so that Loc vars are zero when not found
 * 		this allows to compare locations and  get the last specifier within a line.
 * 		example line: 		"	private:		protected: "		changes *vec to protected.
 */
void ReadH::setVector(string line, vector<Declaration>** vec){
	size_t privLoc = line.find("private:") + 1;
	size_t pubLoc = line.find("public:") + 1;
	size_t protLoc = line.find("protected:") + 1;

	if(privLoc > pubLoc && privLoc > protLoc)
		*vec = &privateFuncs;
	if(pubLoc > privLoc && pubLoc > protLoc)
		*vec = &publicFuncs;
	if(protLoc > pubLoc && protLoc > privLoc)
		*vec = &protectedFuncs;
}


/**		Finds a declaration or function, if declaration creates and adds Declaration to funcs.
 * 		
 * 		@param line - line within file.
 * 		@param funcs - appropriate function vector.
 * 		@return - true if a declaration or function is found;
 */
bool ReadH::findDeclaration(string line, vector<Declaration>* funcs){
	size_t hash = line.find("#");
	size_t openParen = line.find("(");
	if(hash != string::npos || openParen == string::npos)
		return false;

	string currLine;
	while(line.find(";") == string::npos && line.find("{") == string::npos){
		getline(inFile, currLine);
		line += currLine;
	}

	if(line.find(";") != string::npos){
		Declaration d(line, className);
		if(d.functionValid())
			funcs->push_back(d);
	}
	else{
		//should write a generalized function for this.
		string currentLine;
		int openBrackets  = StringManipulation::countChars(line, '{');
		int closedBrackets = StringManipulation::countChars(line, '}');
		while(openBrackets != closedBrackets){
			getline(inFile, currentLine);
			openBrackets  += StringManipulation::countChars(currentLine, '{');
			closedBrackets += StringManipulation::countChars(currentLine, '}');
		}	
	}

	return true;
}


vector<Declaration> ReadH::getPrivateFunctions(){
return privateFuncs;
}


vector<Declaration> ReadH::getProtectedFunctions(){
	return protectedFuncs;
}


vector<Declaration> ReadH::getPublicFunctions(){
	return publicFuncs;
}


bool ReadH::fileFound(){ return found;}
