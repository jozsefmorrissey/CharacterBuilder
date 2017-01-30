#include <sys/types.h>
#include <unistd.h>
#include <thread>


#include "WorkQueue.cpp"


class WorkerThread:public thread{
    WorkQueue<WorkItem<struct epoll_event *>*> * m_queue;
    void * (*processFunc)(void *);
    
    static void * defaultProFunc(void * item){
                printf("thread %lu - got one item addr \"%zu\"\n", 
                  (long unsigned int)getpid(), (size_t)item);
		return NULL;
    }
 
  public:
    WorkerThread(WorkQueue<WorkItem<struct epoll_event *>*> * queue){
    	m_queue = queue;
    	processFunc = &defaultProFunc; 
    }
 
    WorkerThread(WorkQueue<WorkItem<struct epoll_event *>*> * queue, void * (*pF)(void *)){
       	m_queue = queue;
    	processFunc = pF; 
    }
 
    void* run() {
        for (int i = 0;; i++) {
            printf("thread %lu, loop %d - waiting for item...\n", 
                  (long unsigned int)this, i);
            void * item = (void*)m_queue->remove();
            processFunc(item);

        }
        return NULL;
    }
};
