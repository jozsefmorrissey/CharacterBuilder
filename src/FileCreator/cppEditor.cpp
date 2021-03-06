#include <string>
#include <algorithm>
#include "ReadCpp.h"
#include "ReadH.h"
#include "unistd.h"


using namespace std;

string fileName;
string filePath;
string testPath;
string tempTestFile;

void changeFilePath(string input, string* filePath);
void changeFileName(string input, string* fileName);
vector<Declaration> create(ReadH* rh);
string sectionSpliter(string section);
bool addUnparsed(string* fileText, vector<string> strs);
string merge(ReadCpp* rc, ReadH* rh);
void printSource(string text, string fileName);
string mergeLoop(vector<Source> * vecS, vector<Declaration> vecD, string message);
void updateTests(vector<Declaration> funcs);
void createTestHeader(vector<Declaration> funcs, string fn);
vector<Declaration> compareExistingHeader();
void appendTestFiles(vector<Declaration> newFuncs);

int main(){
	char path[256] = "";
	getcwd(path, 255);

	string homeDir = path;
	homeDir += "/";
	filePath = "src/FileCreator/test/";
	testPath = filePath;
	testPath = testPath.replace(testPath.find("src/"), 3, "test");
	fileName = "SourceTEST";	
	tempTestFile = "tempTest.h";

	string userInput;
	while(true){
		cout << "\nHome Dir:\t" << homeDir;
		cout << "\nFile Path:\t" <<filePath;
		cout << "\nRoot File Name: \t" << fileName << "\n";
		string complete = homeDir + filePath + fileName;
		getline(cin,userInput);
		if(userInput.find("fp ")!= string::npos)
			changeFilePath(userInput, &filePath);
		if(userInput.find("fn") != string::npos)
			changeFileName(userInput, &fileName);
		if(userInput.find("c") == 0 && fileName != ""){
			ReadH rh(complete + ".h");
			bool validClass = rh.getClassName().compare("");
			while(validClass){
			vector<Declaration> pubDecs = create(&rh);
			updateTests(pubDecs);			
			validClass = rh.continueReading();
			}
		}
	}

	return 0;
}


vector<Declaration> create(ReadH * rh){
	string srcFileName = filePath + rh->getClassName();
	ReadCpp rc(srcFileName + ".cpp");
	Error err;

	if(!rh->fileFound()){
		cout << "\n\n\t\tWARNING: Header File Not Found\n\n";
		return 	rh->getPublicFunctions();
	}
	
	string text = merge(&rc,rh);
	if(text.compare(""))
		printSource(text, srcFileName);	
	
	return 	rh->getPublicFunctions();
}


void updateTests(vector<Declaration> funcs){
	if(funcs.size() == 0) 
		return;

	createTestHeader(funcs, tempTestFile);
	vector<Declaration> newFuncs = compareExistingHeader();
	appendTestFiles(newFuncs);

	string rmTempFile = "rm " + tempTestFile;
	system(rmTempFile.c_str());
}


void appendTestFiles(vector<Declaration> newFuncs){
	string testFileName = testPath+ fileName + "TEST";
	string testFileNameH = testFileName + ".h";
	ifstream existingFile(testFileNameH.c_str());
	if(!existingFile.good()){
		string mkCmd = "mkdir " + filePath;
		string cpCmd = "cp " + tempTestFile + " " +  testFileNameH;
		string cmd = mkCmd + " & " + cpCmd;
		cout << cmd << "\n";
		system(cmd.c_str());
	}
	else{
		string fileText = "";
		string currLine;
		while(getline(existingFile, currLine)){
			if(currLine.find("};") != string::npos){
				for(vector<Declaration>::iterator dec = newFuncs.begin(); dec != newFuncs.end(); dec++)
					fileText += "\t\t" + dec->getDeclaration() + "\n";
			}
			fileText += currLine + "\n";
		} 
		ofstream outfile(testFileNameH.c_str());
		outfile << fileText;
		outfile.close();
	}

	ReadH rh(testFileName + ".h");
	string temp = filePath;
	filePath = 	testPath;
	create(&rh);
	filePath = temp;
}


vector<Declaration> compareExistingHeader(){
	string testFileName = testPath+ fileName + "TEST";
	string testFileNameH = testFileName + ".h";
	vector<Declaration> newFuncs;
	ifstream existingFile(testFileNameH.c_str());
	if(!existingFile.good()){
		return newFuncs;
	}
	else{
		ReadH existingH(testFileNameH);
		ReadH tempH(tempTestFile);
		
		vector<Declaration> existFuncs = existingH.getPublicFunctions();
		newFuncs = tempH.getPublicFunctions();
	
		for(vector<Declaration>::iterator eFit = existFuncs.begin(); eFit != existFuncs.end(); eFit++){
			for(vector<Declaration>::iterator nFit = newFuncs.begin(); nFit != newFuncs.end(); nFit++){
				if(eFit->compare(*nFit)){
					nFit = newFuncs.erase(nFit);
					nFit--;
				}
			}
		}
	}

	return newFuncs;
}


void createTestHeader(vector<Declaration> funcs, string fn){
	string header = filePath + fileName + ".h\"\n\n\n";
	string fileText = "#include \"../../" + header + "class " + fileName + "TEST{\n\n\tpublic:\n";
	
	for(vector<Declaration>::iterator dec = funcs.begin(); dec != funcs.end(); dec++){
		fileText += "\t\t" + dec->getTestDeclaration() + "\n";
	}

	fileText += "};";

	ofstream outfile(fn.c_str());
	outfile << fileText;
	outfile.close();
}


void printSource(string text, string fileName){
	string fn= fileName + ".cpp";
	ofstream outfile(fn.c_str());
	outfile << text;
	outfile.close();
}


string merge(ReadCpp* rc, ReadH* rh){
	string fileText = "#include \"";
	fileText += fileName + ".h\"\n";

	if(!addUnparsed(&fileText, rc->getUnparsed()))
		return "";

	if(rc->getVariables().size() > 0){
		fileText += sectionSpliter("Variables");
		fileText += StringManipulation::vectorToLine(rc->getVariables());
	}

	vector<Source> sourceFuncs = rc->getFunctions();	
	fileText += mergeLoop(&sourceFuncs, rh->getPrivateFunctions(), "Private");
	fileText += mergeLoop(&sourceFuncs, rh->getProtectedFunctions(), "Protected");
	fileText += mergeLoop(&sourceFuncs, rh->getPublicFunctions(), "Public");
	
	if(sourceFuncs.size() > 0){
		fileText += sectionSpliter("Not Declared");
		for(vector<Source>::iterator srcs = sourceFuncs.begin(); srcs != sourceFuncs.end(); srcs++){
			fileText += srcs->getFunction();
		}
	}
	return fileText;
}



bool addUnparsed(string* fileText, vector<string> strs){
	if(strs.size() == 0)
		return true; 

	bool needAction = true;
	while(needAction){
		string unParsed =  StringManipulation::vectorToLine(strs);
		cout << "\n\nThese lines were not parsed successfully from the source file:\n" << unParsed << "\nDo you want to:\n\t1:\tAdd Lines to the top of the source file\n\t2:\tOmit lines\n\t3:\tCancel operation\n";
		int userInput;
		cin >> userInput;
		switch(userInput){
			case 1: 
				*fileText = sectionSpliter("Unparsed") + unParsed + *fileText;
				needAction = false;
				break;
			case 2:
				needAction = false;
				break;
			case 3:
				return false;
			default:
				cout << "\n\n\t\t	Input Not Understood\n\n";			
		}
	}
	return true;
}


string mergeLoop(vector<Source> * vecS, vector<Declaration> vecD, string message){
	if(vecD.size() == 0)
		return "";

	string retVal = sectionSpliter(message);
	for(vector<Declaration>::iterator dec = vecD.begin(); dec != vecD.end(); ++dec){
		bool found = false;
		for(vector<Source>::iterator src = vecS->begin(); src != vecS->end(); ++src){
			if(src->compare(*dec)){
				found = true;	
				string func = src->getFunction();
				StringManipulation::trimWhiteSpace(&func);
				retVal += "\n" + func + "\n\n";
				src = vecS->erase(src);
				src--;
			}
		}	
		if(found == false){
			found = true;	
			string func = dec->getFunction();
			StringManipulation::trimWhiteSpace(&func);
			retVal += "\n" + func + "\n\n";
		}
	}
	return retVal;
}

string sectionSpliter(string section){
	string retVal = "\n\n//--------------------------  ";
	retVal = retVal + section + StringManipulation::reverse(retVal);
	return retVal;
}


void changeFileName(string input, string* fileName){
	size_t loc = input.find("fn ");
	*fileName = input.substr(loc + 3);
	*fileName = StringManipulation::removeWhiteSpace(*fileName);
}


void changeFilePath(string input, string* filePath){
	size_t loc = input.find("fp ");
	*filePath = input.substr(loc + 3);
	*filePath = StringManipulation::removeWhiteSpace(*filePath);
	if(filePath->find("/") == 0)
		*filePath = filePath->substr(1);
	if(filePath->rfind("/") != filePath->size() - 1)
		*filePath += "/";

	testPath = *filePath;
	testPath = testPath.replace(testPath.find("src/"), 3, "test");
}



