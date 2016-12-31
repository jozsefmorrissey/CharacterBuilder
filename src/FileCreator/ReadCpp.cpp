#include "ReadCpp.h"


ReadCpp::ReadCpp(string fileName){
	inFile.open(fileName.c_str());
	read();
}

ReadCpp::~ReadCpp(){
	inFile.close();
	functions.clear();
	variables.clear();
	unparsed.clear();
}

/**		Reads through source file line by line looking for variables, commented functions, and functions.
 * 		
 * 		@return - true if file was successfully opened
 */
int ReadCpp::read(){
	if(!inFile)
		return 0;

	string line;
	string sectionSplit = "//--------------------------  ";
	while(getline(inFile, line)){

		if(findVariable(line));
		else if(findComment(line));
		else if(findFunction(line));
		else if(line.compare("") && line.find("#") == string::npos && line.find(sectionSplit) == string::npos)
			unparsed.push_back(line);
	}

return 1;
}


/**		
 * 		@return - true if the assigment opperator is detected and consolidates variable onto a single line
 */
bool ReadCpp::findVariable(string line){
	if(line.find("=") == string::npos)
		return false;

	string currentLine;
	while(line.find(";") == string::npos){
			getline(inFile, currentLine);
			line += currentLine;
	}
	
	variables.push_back(line);


return true;
}


/**		finds all comment lines and concatenates them together, then calls parse function to add
 * 		function body and declaration lines.
 * 		
 * 		@return - false if comment start symbol is not detected.
 */
bool ReadCpp::findComment(string line){
	string searchLine = StringManipulation::removeSurroundedText("\"", "\"", line);
	if(searchLine.find("/**") == string::npos)
		return false;

		line += "\n";
		string currentLine =line;
	while(searchLine.find("*/") == string::npos){
		getline(inFile, currentLine);
		searchLine = StringManipulation::removeSurroundedText("\"", "\"", line);
		line += currentLine + "\n";		
	}


	parseFunction(&line);

	Source s(line);
	functions.push_back(s);
	
return line.compare("");
}

/**		If a line is sent here it assumes there is a function body to be parsed and it creates a source to be
 * 		added to the vector functions from a concatination of the lines that make up the function 
 * 		delclaration and body.
 */
bool ReadCpp::parseFunction(string * line){
	string currentLine;
	int openBrackets  = StringManipulation::countChars(*line, '{');
	int closedBrackets = StringManipulation::countChars(*line, '}');
	bool foundFunction = false;
	while(openBrackets != closedBrackets || !foundFunction){
		getline(inFile, currentLine);
		openBrackets  += StringManipulation::countChars(currentLine, '{');
		closedBrackets += StringManipulation::countChars(currentLine, '}');
		*line += currentLine + "\n";
		if(!foundFunction && line->find("{") != string::npos)
			foundFunction = true;
	}	
	return foundFunction;
}


/**		
 * 		@return - true if a function can be found
 */
bool ReadCpp::findFunction(string line){
	size_t dColon = line.find("::");
	if(dColon == string::npos)
		return false;
	string funcName = line.substr(dColon);
	size_t openParen = funcName.find("(");
	size_t space = funcName.find(" ");
	if(openParen < space && openParen != string::npos){
		parseFunction(&line);
		Source s(line);
		functions.push_back(s);
		return true;
	}	
	
return false;
}

vector<Source> ReadCpp::getFunctions(){
	return functions;
}

vector<string> ReadCpp::getUnparsed(){
	return unparsed;
}

vector<string> ReadCpp::getVariables(){
	return variables;
}
