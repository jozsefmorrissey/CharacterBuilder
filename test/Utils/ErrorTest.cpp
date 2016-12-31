#include "ErrorTest.h"

int ErrorTest::testConstructors(){
	int failCount = 0;

	Error e1 = Error();
	if(e1.getFatal() != false or  e1.getExitCode()  != 1){
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ - 2, "1st Constructor Failed to Initialize");
		failCount++;
	}

	e1 = Error(1);
	if(e1.getFatal() != true or e1.getExitCode() != 1){
	 	printFailureMsg(__PRETTY_FUNCTION__, __LINE__ - 2, "2nd Constructor Failed to Initialize");
		failCount++;
	}

			e1 = Error(1, 38);
	if(e1.getFatal() != true or e1.getExitCode() != 38){
	 	printFailureMsg(__PRETTY_FUNCTION__, __LINE__ - 2, "3nd Constructor Failed to Initialize");
		failCount++;
	}

	return failCount;
}


int ErrorTest::testNeg_1_err(){	
	Error e1 = Error();
	if(e1.negative_1_error(-1, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 0)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "Error Not Detected");
	else if(e1.negative_1_error(0, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 1)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "NonError Recognized");
	else if(e1.negative_1_error(-2, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 1)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "NonError Recognized");
	else if(e1.negative_1_error(1, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 1)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "NonError Recognized");
	else 
		return 0;
	return 1;
}

int ErrorTest::testNon_0_err(){
	Error e1 = Error();
	if(e1.non_zero_error(-1, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 0)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "Error Not Detected");
	else if(e1.non_zero_error(0, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 1)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "NonError Recognized");
	else if(e1.non_zero_error(1, "Disregard Error Test", __LINE__, __PRETTY_FUNCTION__) == 10)
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "Error Not Detected");
	else
		return 0;
	return 1;
}

int ErrorTest::testGettersSetters(){
	Error e = Error(true, 0);
	if (e.getFatal() != true || e.getExitCode() != 0){
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "Getter Failed");
		return 1;
	}
	e.setFatal(false);
	e.setExitCode(33);
	if (e.getFatal() != false || e.getExitCode() != 33){
		printFailureMsg(__PRETTY_FUNCTION__, __LINE__ -1, "Setter Failed");
		return 1;
	}
	return 0;
}


void ErrorTest::printFailureMsg(const char * function, int line, const char * msg){
		std::string functionName = StringManipulation::cleanFunctionID(function);

		std::cout << RED << "Error: " << RESET;
		std::cout <<  msg << " - " << functionName;
		std::cout << " - line " << BLUE << line << RESET << "\n";
}


