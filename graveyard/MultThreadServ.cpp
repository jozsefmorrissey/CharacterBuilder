#include "MultThreadServ.h"



//--------------------------  Private  --------------------------//




//--------------------------  Public  --------------------------//


/**		TODO: comment on function use
 *		
 *		@sa - 
 *		@return - TODO: comment on return value
 */
void * MultThreadServ::getInAddr(struct sockaddr * sa){
	if(sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr); 
	}
	
	return &(((struct sockaddr_in6 *)sa)->sin6_addr); 
}


/**		TODO: comment on function use
 *		
 *		@return - 0 on success
 */
int MultThreadServ::getAddr(){
	struct addrinfo hints;

	memset(& hints, 0, sizeof hints);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; 
	hints.ai_flags = AI_PASSIVE; 
	
	char portNum[10];
	sprintf(portNum, "%i", PORT); //PORT: Defined in Makefile
	this->status = getaddrinfo(NULL, portNum , &hints, &myAddrInfo);
	if(this->status != 0)
	{
		fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(this->status));
		return 1;
	}
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::openSocket(){
	lSocket = socket(myAddrInfo->ai_family,myAddrInfo->ai_socktype, myAddrInfo->ai_protocol);
	if(lSocket < 0 )
	{
		fprintf(stderr,"socket error: %s\n",gai_strerror(status));
		return 1;
	}
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::bindSocket(){
	int status;
	status = bind(lSocket, myAddrInfo->ai_addr, myAddrInfo->ai_addrlen); 
	if(status < 0)
	{
		fprintf(stderr,"bind: %s\n",gai_strerror(status));
		return 1;
	}


	
	freeaddrinfo(myAddrInfo);
	return 0;
}


/**		TODO: comment on function use
 *		
 */
int MultThreadServ::listenSocket(){

	
	status = listen(lSocket, 10); 
	if(status < 0)
	{
		fprintf(stderr,"listen: %s\n",gai_strerror(status));
		return 2;
	}

	
	return 0;
}





/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::acceptConnection(){

	int new_conn_fd;	
	struct sockaddr_storage client_addr;
	socklen_t addr_size;
	char s[INET6_ADDRSTRLEN]; 
	
	// Calculate the size of the data structure	
	
	addr_size = sizeof client_addr;
	
	printf("I am now accepting connections ...\n");
	
	while(1){
		printf("lSocket:\t%i", lSocket);

		new_conn_fd = accept(lSocket, (struct sockaddr *) & client_addr, &addr_size);	
		if(new_conn_fd < 0)
		{
			fprintf(stderr,"accept: %s\n",gai_strerror(new_conn_fd));
			continue;
		}
		inet_ntop(client_addr.ss_family, getInAddr((struct sockaddr *) &client_addr),s ,sizeof s); 
		printf("Connection made: client_fd=%d\taddr=%s\n", new_conn_fd, s);
		status = send(new_conn_fd,"Welcome", 7,0);
		if(status == -1)
		{
			close(new_conn_fd);
			_exit(4);
		}
	
		startNewThread(new_conn_fd);

	}
	// Close the socket before we finish 
	int yes = 1;
	setsockopt(lSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	close(lSocket);
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::startNewThread(int new_conn_fd){
		struct thread_info * tInfo = (struct thread_info*)find();
		tInfo->fd = new_conn_fd;
		tInfo->currServ = this;
		sigset_t set;
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		pthread_sigmask(SIG_BLOCK, &set, NULL);
		if(pthread_create(&(tInfo->thread), NULL, procConn, &(tInfo->fd)) == 0){
			printf("\ntid: %zu\t\tcreated\n", (size_t)tInfo->thread);
			pthread_create(&(tInfo->keeper), NULL, waitThread, tInfo);
			printf("\ntid: %zu\t\tcreated\n", (size_t)tInfo->keeper);
		}
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	return 0;
}


void * MultThreadServ::find(){
	//thread_mutex.lock();
    //pthread_mutex_lock(&lock);
			for(int i = 0; i < MAX_THREAD; i++){
				if(threads[i].status == UNUSED){
					threads[i].status = RUNNING;
					//thread_mutex.unlock();
				    //pthread_mutex_unlock(&lock);
					return &threads[i];
				}
				
				if(threads[i].status == JOIN_KEEPER){ 			//TODO: verify this
					pthread_join(threads[i].keeper, NULL);		//returns true when thread exits
					threads[i].status = RUNNING;
					//thread_mutex.unlock();
				    //pthread_mutex_unlock(&lock);
					return &threads[i];
				}
			}
		    //pthread_mutex_unlock(&lock);
			//thread_mutex.unlock();
			return NULL;
		}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::joinThreads(){
	int stillRunning = -1;
	while(stillRunning){
		if(stillRunning != -1){
			printf("\n%i threads still running", stillRunning);
			sleep(5);
		}
		stillRunning = 0;
		for(int i = 0; i < MAX_THREAD; i++){
			if(threads[i].status == JOIN_KEEPER)
				pthread_join(threads[i].thread, NULL);
			if(threads[i].status == RUNNING)
				stillRunning += 1;
		}
	}
	return 0;
}


/**		TODO: comment on function use
 *		
 *		@return - TODO: comment on return value
 */
int MultThreadServ::closeConnection(){
	//TODO: Implement
	return 0;
}


void * MultThreadServ::waitThread(void * argv) {

	struct thread_info * tInfo = (struct thread_info *)argv;
	printf("\ntid: %zu\t\ttrying to join\n", (size_t)tInfo->thread);
	while(pthread_join(tInfo->thread, NULL) != 0);
	
	//tInfo->currServ->thread_mutex.lock();
    //pthread_mutex_lock(&tInfo->currServ->lock);
	printf("\ntid: %zu\t\tjoined\n", (size_t)tInfo->thread);
	tInfo->status = JOIN_KEEPER;
	//pthread_mutex_unlock(&tInfo->currServ->lock);
//	tInfo->currServ->thread_mutex.unlock();

    return NULL;
}


