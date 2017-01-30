#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <mutex>


using namespace std;  



class MultThreadServ{
	//mutex thread_mutex;
//	pthread_mutex_t lock;
	public:
		#define MAX_THREAD (500)
		#define RUNNING (0)
		#define UNUSED (1)
		#define JOIN_KEEPER (2)
			
		struct thread_info{
			MultThreadServ * currServ;
			pthread_t thread;
			pthread_t keeper;
			int fd;
			int status;
		};
	
		bool run;

		MultThreadServ(void * (*pC)(void*)){
		    /*if (pthread_mutex_init(&lock, NULL) != 0)
				{
					printf("\n mutex init failed\n");
					return;
				}*/
			procConn = pC;
			for(int i = 0; i < MAX_THREAD; i++)
				threads[i].status = UNUSED;
			this->getAddr();	
			this->openSocket();
			this->bindSocket();
			this->listenSocket();
			this->acceptConnection();
		    //pthread_mutex_destroy(&lock);
		}

		int * findClientFd();
		void * getInAddr(struct sockaddr * sa);
		int getAddr();
		int openSocket();
		int bindSocket();
		int listenSocket();
		int acceptConnection();
		void * find();
		int joinThreads();

		static void * waitThread(void * argv);
		int startNewThread(int new_conn_fd);
		int closeConnection();


	private:
	

	
	
		void * (*procConn)(void *);
		struct addrinfo * myAddrInfo;
		int lSocket, status;
		struct thread_info threads[MAX_THREAD];
	

		void signalHandler(int signal);
		

};
