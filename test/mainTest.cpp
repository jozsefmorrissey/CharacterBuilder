#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "Utils/ErrorTest.h"
#include "FileCreator/DeclarationTEST.h"
#include "FileCreator/SourceTEST.h"

static void testsCompleted(int failCount);
static int errorTests();
static int declarationTests();
static int sourceTests();

int main(){
	int failCount = 0;
	failCount += errorTests();
	failCount += declarationTests();
	failCount += sourceTests();

	string tester = "\n\t helloWorld \t\n";
	StringManipulation::trimWhiteSpace(&tester);
	cout << tester;
	
	testsCompleted(failCount);
    return 0;
}


void testsCompleted(int failCount){
    printf("All Tests Completed : %i tests failed\n", failCount);
}


int errorTests (){
	int failCount = 0;
	failCount += ErrorTest::testConstructors();
	failCount += ErrorTest::testNeg_1_err();
	failCount += ErrorTest::testNon_0_err();
	failCount += ErrorTest::testGettersSetters();
	return failCount;
}


int declarationTests(){
	int failCount = 0;
	failCount += DeclarationTEST::constructionTEST();
	failCount += DeclarationTEST::getFunctionTEST();
	failCount += DeclarationTEST::getFunctionBodyTEST();
	failCount += DeclarationTEST::getCommentTEST();
	failCount += DeclarationTEST::badInputTEST();
	return failCount;
}


int sourceTests(){
	int failCount = 0;
	failCount += SourceTEST::constructionTEST();
	failCount += SourceTEST::getFunctionTEST();
	failCount += SourceTEST::getCommentTEST();
	failCount += SourceTEST::getFunctionBodyTEST();

	return failCount;
}
