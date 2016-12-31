#ifndef ERRORTEST_H
#define ERRORTEST_H

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../../defVars/terminalTextColors"
#include "../../src/Utils/Error.h"

class ErrorTest
{

	private:
		static int parentProccessKill(pid_t pid);
		static void printFailureMsg(const char * func, int line, const char * msg);


	public:
		static int testConstructors();
		static int testNeg_1_err();
		static int testNon_0_err();
		static int testPrint_Error(); 
		static 	int testGettersSetters();
};

#endif //ERRORTEST_H
