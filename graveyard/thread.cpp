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
#include <thread>

void * nap(void * argv) {
	if(argv != NULL)
		printf("little buddy here\n");
	sleep(5);
 	printf("thread is up\n");
}

	pthread_mutex_t lock;
int main()
{

		    if (pthread_mutex_init(&lock, NULL) != 0)
				{
					printf("\n mutex init failed\n");
					return 0;
				}
	std::thread ttt(nap, &lock);		
	pthread_t t;
	pthread_create(&t, NULL, nap, NULL);
	pthread_join(t, NULL);

    pthread_mutex_lock(&lock);
	pthread_mutex_unlock(&lock);

	printf("thread is joined\n");
	return 0;
}


