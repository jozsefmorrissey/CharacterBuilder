#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

//#include "WorkerThread.cpp"
#include "WorkQueue.cpp"

#define MAXEVENTS 64
#define DEFAULT_THREAD_COUNT (20)
		
using namespace std;  



class EpollServer{
	
	private:

		int sfd, s, efd;
		struct epoll_event event;
		struct epoll_event *events;
		WorkQueue<WorkItem<struct epoll_event*>*> w_queue;
		void * (*processInput)(void*);
		pthread_t threads[DEFAULT_THREAD_COUNT];
		char port[10];
	
		int makeSocketNonBlocking (int sfd);
		int createBind ();
		static void * work(void * EServ);
		void eventHandler();
		int startServer();
		int errorHandler(int index);
		int newConnection();
		int newInput(int index);		
		
	public:
		EpollServer(char * p, void * (*pC)(void*));
		~EpollServer();
		

		
		
};
