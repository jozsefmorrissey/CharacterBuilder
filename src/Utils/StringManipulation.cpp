#include "StringManipulation.h"


//--------------------------  Public  --------------------------//


/**		TODO: comment on function use
 *		
 *		@line - 
 *		@return - TODO: comment on return value
 */
char * StringManipulation::removeLeadingCommentSymbols(char * line){	char * last;
	while (last != line){
		last = line;
		line = removeFromFront(line, "/");
		line = removeFromFront(line, "*");
	}
	return line;
}


/**		TODO: comment on function use
 *		
 *		@line - 
 *		@target - 
 *		@return - TODO: comment on return value
 */
char * StringManipulation::removeFromFront(char * line, const char * target){	if(strstr(line, target) == line)
		line = line + strlen(target);
	return line;
}


/**		TODO: comment on function use
 *		
 *		@line - 
 *		@return - TODO: comment on return value
 */
char * StringManipulation::removeLeadingWhiteSpace(char * line){	char * last;
	while (last != line){
		last = line;
		line = removeFromFront(line, " ");
		line = removeFromFront(line, "\t");
		line = removeFromFront(line,"\n");
	}
	return line;
}


/**		TODO: comment on function use
 *		
 *		@haystack - 
 *		@needle - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::countChars(char * haystack, char needle){	int count = 0;
	for(size_t index = 0; index < strlen(haystack); index++){
		if(haystack[index] == needle)
			count++;
	}
	return count;
}


/**		TODO: comment on function use
 *		
 *		@haystack - 
 *		@needle - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::countChars(string haystack, char needle){	int count = 0;
	for(size_t index = 0; index < haystack.size(); index++){
		if(haystack.at(index) == needle)
			count++;
	}
	return count;
}


/**		TODO: comment on function use
 *		
 *		@s - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::trimWhiteSpace(string * s){	int prevCount = -1;	
	int count = 0;
	while (prevCount != count){
		prevCount = count;
		count += removeFromFront(s, ' ');
		count += removeFromFront(s, '\t');
		count += removeFromFront(s,'\n');
		count += removeFromRear(s, ' ');
		count += removeFromRear(s, '\t');
		count += removeFromRear(s,'\n');
	}
	return count;
}


/**		TODO: comment on function use
 *		
 *		@s - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::removeWhiteSpace(string s){	return removeCharacters(s, " \n\t");
}


/**		TODO: comment on function use
 *		
 *		@s - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::removeLeadingWhiteSpace(string * s){	int prevCount = -1;	
	int count = 0;
	while (prevCount != count){
		prevCount = count;
		count += removeFromFront(s, ' ');
		count += removeFromFront(s, '\t');
		count += removeFromFront(s,'\n');
	}
	return count;
}


/**		TODO: comment on function use
 *		
 *		@s - 
 *		@target - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::removeFromRear(string * s, char target){	size_t start = s->size();
	size_t end = s->size() - 1;
	size_t rmCount = 0;

	while(start != end){
		start = end;
		if(0 > (ssize_t)end){
			*s = "";
			return end;
		}
		if(s->at(end) == target){
			end--;
			rmCount++;
		}
	}	
	*s = s->substr(0, end+1);
	return rmCount;
}


/**		TODO: comment on function use
 *		
 *		@s - 
 *		@target - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::removeFromFront(string * s, char target){	int start = -1;
	int end = 0;

	while(start != end){
		start = end;
		if((int)s->size() <= end){
			*s = "";
			return end;
		}
		if(s->at(end) == target)
			end++;
	}	
	*s = s->substr(end);
	return end;
}


/**		TODO: comment on function use
 *		
 *		@haystack - 
 *		@needles - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::removeCharacters(string haystack, string needles){	string cleanStr = "";
	bool addChar;
	
	for(size_t hIndex = 0; hIndex < haystack.size(); hIndex++){
		addChar = true;
		for(size_t nIndex = 0; nIndex < needles.size(); nIndex++){
			if(haystack.at(hIndex) == needles.at(nIndex))
				addChar = false;
		}
		if(addChar)
			cleanStr += haystack.at(hIndex);
	}
	return cleanStr;
}


/**
 *		This function cleans up the funtion ID given by __PRETTY_FUNCTION__
 *		leaving only the CLASS::FUNTIONNAME
 *
 *   	@param fuction - __PRETTY_FUNCTION__
 *		@returnCLASS::FUNTIONNAME
*/
string StringManipulation::cleanFunctionID(const char * function){
	string functionName = function;

	int firstComma = functionName.find(",");
	functionName = functionName.substr(0, firstComma);

	int lastSpace = functionName.find_last_of(" ");
	int openParen = functionName.find("(");
	return functionName .substr(lastSpace +1, openParen - lastSpace - 1);
}


/**		TODO: comment on function use
 *		
 *		@v - 
 *		@s - 
 *		@delimeter - 
 *		@return - TODO: comment on return value
 */
int StringManipulation::tokenize(vector<string> * v, string s, char delimeter){	if(s.size() == 0)
		return 0;
	size_t start = 0;
	size_t end = 0;
	for( ; end < s.size(); end++){
		if(s.at(end) == delimeter){
			if(end == start)
				start++;
			else{
				v->insert(v->end(), s.substr(start, end - start));
				start = end + 1;
			}
		}
	}
	v->insert(v->end(), s.substr(start, end - start));
	return end;
}


/**		TODO: comment on function use
 *		
 *		@vecS - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::vectorToLine(vector<string> vecS){	string retVal = "";
	for(vector<string>::iterator it = vecS.begin(); it != vecS.end(); ++it){
		retVal +="\n" + *it + "\n";
	}
	return retVal;
}


/**		TODO: comment on function use
 *		
 *		@str1 - 
 *		@str2 - 
 */
void StringManipulation::inlineCharCompare(string str1, string str2){	if(str1.size() != str2.size())
		cout << "\nStrings are not the same length - " << str1.size() << ":" << str2.size()<< "\n";

	size_t lim = str1.size()> str2.size() ? str2.size() : str1.size();
	for(size_t index = 0; index < lim; index++)
		cout << "<" << str1.at(index) << str2.at(index) << "> ";
	cout << "\n";
}


/**		TODO: comment on function use
 *		
 *		@str - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::reverse(string str){	string rev = "";
	for(int index = str.size() - 1; index > -1; index--)
			rev += str.at(index);
	return rev;
}


/**		TODO: comment on function use
 *		
 *		@start - 
 *		@end - 
 *		@str - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::removeSurroundedText(char start, char end, string str){	string s = "";
	s += start;
	string e = "";
	e += end;
	return removeSurroundedText(s, e, str);
}


/**		TODO: comment on function use
 *		
 *		@start - 
 *		@end - 
 *		@str - 
 *		@return - TODO: comment on return value
 */
string StringManipulation::removeSurroundedText(string start, string end, string str){	string clean = "";
	size_t s = 1;
	size_t e = 1;
	while(s != string::npos && e != string::npos){
		size_t gap = 0;

		s = str.find(start);
		while(s != string::npos && (s != 0 && str.at(s + gap - 1) == '\\')){
			gap += s + 1;
			s = str.substr(gap).find(start);
		}

		gap ++;
		e = str.substr(s + gap).find(end);		
		while(e != string::npos && (e != 0 && str.at(s + e + gap - 1) == '\\')){
			gap += e + 1;
			e = str.substr(s + gap).find(end);
		}
		
		if(e != string::npos && s != string::npos){
			clean += str.substr(0, s);
			if(e + s + end.size() + gap < str.size())
				str = str.substr(s + e + gap + end.size());
			else
				str = "";
		}
	}
	clean += str;
	return clean;
}

