#include "DeclarationTEST.h"



/**		
 * 		Verifyes the Decomposition and reconstruction of a header
 */
int DeclarationTEST::constructionTEST(){
	Declaration dec = Declaration("static char * removeFromFront(char [][] line, const char * target);", "StringManipulation");
	if(dec.getDeclaration().compare("static char * removeFromFront(char [][] line, const char * target);"))
		return 1;
	if(dec.getClassName().compare("StringManipulation") || dec.getFunctionName().compare("removeFromFront"))
		return 1;

	dec = Declaration("char * removeFromFront(const char * target);", "StringManipulation");
	if(dec.getDeclaration().compare("char * removeFromFront(const char * target);"))
		return 1;
	if(dec.getClassName().compare("StringManipulation") || dec.getFunctionName().compare("removeFromFront"))
		return 1;

	dec = Declaration("\t \n virtual char * removeFromFront(int[] args, const char * target);", "StringManipulation");
	if(dec.getDeclaration().compare("virtual char * removeFromFront(int[] args, const char * target);"))
		return 1;
	if(dec.getClassName().compare("StringManipulation") || dec.getFunctionName().compare("removeFromFront"))
		return 1;

 	dec = Declaration("StringManipulation(char [][] line, const char * target);", "StringManipulation");
	if(dec.getDeclaration().compare("StringManipulation(char [][] line, const char * target);"))
		return 1;

return 0;
}


/**		
 * 		Tests the consolidation of getComment() buildFunctionName and GetFuncitonBody
 *	 		Since get comment and build body are tested thoughly and variables like static and 
 * 		virtual do not come into play a single test with multiple varibles will suffice.
 */
int DeclarationTEST::getFunctionTEST(){

	Declaration dec = Declaration("static char * removeFromFront(char [][] line, const char * target, vector happyThoughts);", "StringManipulation");
	Error err = Error();

	string function = "\n/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@line - \n *\t\t@target - \n *\t\t@happyThoughts - \n *\t\t@return - TODO: comment on return value\n */\nchar * StringManipulation::removeFromFront(char [][] line, const char * target, vector happyThoughts){\n\t//TODO: Implement\n\treturn NULL;\n}\n";
	if(dec.getFunction().compare(function)){
		err.non_zero_error(1, "Function Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("static char * removeFromFront(char [][] line, const char * target, vector happyThoughts);", "StringManipulation");
	function = "\n/**\t\t\n *\t\tTODO: comment on function use\n */\nint StringManipulationTEST::removeFromFrontTEST(){\n\t//TODO: Implement\n\treturn 0;\n}\n";
	if(dec.getTestFunction().compare(function)){
		err.non_zero_error(1, "Test Function Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}



return 0;
}



/**		
 * 		Verifies that function bodies templates are being implemented correctly
 */
int DeclarationTEST::getFunctionBodyTEST(){
	Declaration dec = Declaration("static char * removeFromFront(char [][] line, const char * target);", "StringManipulation");
	
	string funcBody ="{\n\t//TODO: Implement\n\treturn NULL;\n}\n";
	Error err = Error();
	if(dec.getFunctionBody().compare(funcBody)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}	

	dec = Declaration("char removeFromFront(char [][] line, const char * target);", "StringManipulation");
	
	funcBody ="{\n\t//TODO: Implement\n\treturn 0;\n}\n";
	if(dec.getFunctionBody().compare(funcBody)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}	

	dec = Declaration("int removeFromFront(char [][] line, const char * target);", "StringManipulation");
	
	funcBody ="{\n\t//TODO: Implement\n\treturn 0;\n}\n";
	if(dec.getFunctionBody().compare(funcBody)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}	

return 0;
}


/**		TODO: comment on function use
 * 		
 * 		@return - TODO: comment on return value
 */
int DeclarationTEST::getCommentTEST(){
	Declaration dec = Declaration("static char * removeFromFront(char [][] line, const char * target);", "StringManipulation");
	Error err = Error();

	string comment = "\n/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@line - \n *\t\t@target - \n *\t\t@return - TODO: comment on return value\n */\n";
	if(dec.getComment().compare(comment)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("static char * removeFromFront(vector * stats, char [][] line, const char * target);", "StringManipulation");
	comment = "\n/**\t\tTODO: comment on function use\n *\t\t\n *\t\t@stats - \n *\t\t@line - \n *\t\t@target - \n *\t\t@return - TODO: comment on return value\n */\n";
	if(dec.getComment().compare(comment)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("void removeFromFront();", "StringManipulation");
	comment = "\n/**\t\tTODO: comment on function use\n *\t\t\n */\n";
	if(dec.getComment().compare(comment)){
		err.non_zero_error(1, "Function Body Not Formed Properly", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

return 0;
}

int DeclarationTEST::badInputTEST(){
	Error err = Error();
	Declaration dec = Declaration("#define(384)", "garbageClass");
	if(dec.functionValid()){
		err.non_zero_error(1, "Bad Input not detected", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("#include <garbage.h>", "garbageClass");
	if(dec.functionValid()){
		err.non_zero_error(1, "Bad Input not detected", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("public:", "garbageClass");
	if(dec.functionValid()){
		err.non_zero_error(1, "Bad Input not detected", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}

	dec = Declaration("lkjdfjslk)iwoijf(", "garbageClass");
	if(dec.functionValid()){
		err.non_zero_error(1, "Bad Input not detected", __LINE__, __PRETTY_FUNCTION__);
		return 1;	
	}


	return 0;
}
