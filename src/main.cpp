#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "Utils/StringManipulation.h"
#include "Server/EpollServer.h"
//#include "Server/WorkQueue.cpp"


//bool run;



void * processClient(void * argv);


//MultThreadServ mts(processClient);


/*void handler(int signal){
	if(signal == SIGINT){
		//run = mts.run =false;
	}
}*/


int main()
{
	//signal(SIGINT, handler);
	//signal(SIGPIPE, SIG_IGN);
	
	//mts = MultThreadServ(processClient);
	char p[10] = "11699";
	EpollServer es(p, processClient);

	return 0;
}


void * processClient(void * argv) {
    //int client_fd = (intptr_t) arg;
	//struct thread_info * info = (struct thread_info *)argv;
    pthread_detach(pthread_self()); // no join() required
	int fd = *(int *)argv;
	WorkItem<struct epoll_event*> * wi = (WorkItem<struct epoll_event*>*)argv;
	struct epoll_event * ee = wi->getItem();
	//FILE* fp = fdopen(ee->data.fd, "r");
	fd = ee->data.fd;

	char * buffer = new char[512];
	//size_t count;
    // Continue reading input from the client and print to stdout

	while(1){
		int len = read(fd, buffer, sizeof(buffer) - 1);
		//getdelim(&buffer, &count, TODO parse individual cmds
		//ssize_t len = getline(&buffer, &count, fp);
		if(len == 0 || len == -1){

			break;
		}
		buffer[len] = 0;

		printf("%s", buffer);
		//send(fd, buffer, len, 0);
	}
	//free(buffer);
	close(fd);	
    
    return NULL;
}
