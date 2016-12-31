
#include "Error.h"

Error::Error() : fatal(0), exitCode(1){}

Error::Error(bool fat) : fatal(fat), exitCode(1){}

Error::Error(bool fat, int code) : fatal(fat), exitCode(code){}


void Error::killP(){
    if  (fatal)
        exit(exitCode);
}

int Error::negative_1_error(int error, const char * msg, int line_number, const char * functionName){
	int retVal = 0;    
    if(error == -1)
	    retVal += print_error(msg, functionName, line_number);
    
    killP();
	return retVal;
}

int Error::non_zero_error(int error, const char * msg, int line_number, const char * functionName){
	int retVal = 0;    
	if(error)
	    retVal += print_error(msg, functionName, line_number);
    
    killP();
	return retVal;
}


int Error::print_error(const char * msg, const char * function, int line_number){
	std::string functionName = StringManipulation::cleanFunctionID(function);

    std::string isfatal = "";
    if (fatal)
        isfatal = "Fatal ";
    std::cout << GREEN << isfatal << "Warning " << RESET << " :: " << msg << " @ " <<  functionName << " : "<< line_number << "\n";
	return 1;
}
