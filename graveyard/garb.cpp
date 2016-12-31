
//function pointer and fork
	failCount += testErrorFuncs(&Error::negative_1_error, &e1, -1) ;

	static int testErrorFuncs(int (Error::*func)(int, const char *, int), Error * err, int val);

	int ErrorTest::testErrorFuncs(int (Error::*func)(int, const char *, int), Error * err, int val){
		pid_t pid;
		pid = fork();

		if(pid == 0){
    		freopen("output.txt","w",stdout);
			(err->*func)(val, "error test", __LINE__);
		}

	 	sleep(1);
	
		if(pid == -1)
			printFailureMsg(__PRETTY_FUNCTION__, __LINE__ - 8, "Failed to fork");
		else{
			return parentProccessKill(pid);
		}	

		return 1;
	}	
