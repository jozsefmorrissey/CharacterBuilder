#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>


#include "StringManipulation.h"
#include "../../defVars/terminalTextColors"

class Error
{
	private:
		bool fatal;
		int exitCode;

		int print_error(const char * msg, const char * function, int line_number);  
		void killP();

	public:
		Error();
		Error(bool fat);
		Error(bool fat, int code);
		int negative_1_error(int error, const char * msg, int line_number,  const char * functionName);
		int non_zero_error(int error, const char * msg, int line_number,  const char * functionName);

		bool getFatal(){return this->fatal;}
		int getExitCode(){return this->exitCode;}
	
		void setFatal(bool f){fatal = f;}
		void setExitCode(int eC){exitCode = eC;}
};

#endif //ERROR_H
