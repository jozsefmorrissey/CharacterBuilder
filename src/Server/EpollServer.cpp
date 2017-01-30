#include "EpollServer.h"


//--------------------------  Private  --------------------------//


/**		Prevents socket from blocking.
 *		
 *		@sfd - socket
 *		@return - 0 on success.
 */
int EpollServer::makeSocketNonBlocking(int sfd){
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}


/**		A static function for worker threads to access processInput function
 *		
 *		EServ - The EpollServer that dispached the thread.
 *		@return - Threads will not return from this function.
 */
void * EpollServer::work(void * EServ){
	EpollServer * m_EServ = (EpollServer*)EServ;
    for (int i = 0;; i++) {
        printf("thread %lu, loop %d - waiting for item...\n", (long unsigned int)pthread_self(), i);
        void * item = (void*)m_EServ->w_queue.remove();
        m_EServ->processInput(item);

    }	

	return NULL;
}


/**		Creates and binds main connection socket.
 *		
 *		@return - socket
 */
int EpollServer::createBind(){
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
  hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  hints.ai_flags = AI_PASSIVE;     /* All interfaces */

  s = getaddrinfo (NULL, port, &hints, &result);
  if (s != 0)
    {
      fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      return -1;
    }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    {
      sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      if (sfd == -1)
        continue;

      s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
      if (s == 0)
        {
          /* We managed to bind successfully! */
          break;
        }

      close (sfd);
    }

  if (rp == NULL)
    {
      fprintf (stderr, "Could not bind\n");
      return -1;
    }

  freeaddrinfo (result);

  return sfd;
}



//--------------------------  Public  --------------------------//


/**		Dispaches worker threads and creates server.
 *		
 *		@p - port
 *		@pI - Input prcessing function.  
 */
EpollServer::EpollServer(char * p, void * (*pI)(void *)){
	strcpy(this->port, p);//TODO: for some reason p is being erased. 
									//somthing todo with WorkQueue
	strcpy(this->port, "11699");

	processInput = pI;

	for(int i = 0; i < DEFAULT_THREAD_COUNT; i++){
		pthread_create(&threads[i], NULL, work, this);
	}
	
	sfd = createBind ();	
	startServer();
	eventHandler();
}



EpollServer::~EpollServer(){
	free (events);
	close (sfd);
}


/**		Three events are possible with epoll: error, new client, recieved input 
 */
void EpollServer::eventHandler(){
	while (1){
		int n, i;

		n = epoll_wait (efd, events, MAXEVENTS, -1);
		for (i = 0; i < n; i++){
			if ((events[i].events & EPOLLERR) ||
				(events[i].events & EPOLLHUP) ||
				(!(events[i].events & EPOLLIN))){
				errorHandler(i);
			}

			else if (sfd == events[i].data.fd){
				newConnection();
			}
			
			else{
				newInput(i);
			}
		}
	}
}


/**		Starts listining to main socket, creates epoll handler.
 *		
 *		@return - 0 on success
 */
int EpollServer::startServer(){

	if (sfd == -1)
		abort ();

	s = makeSocketNonBlocking (sfd);
	if (s == -1)
		abort ();

	s = listen (sfd, SOMAXCONN);
	if (s == -1){
		perror ("listen");
		abort ();
	}

	efd = epoll_create1 (0);
	if (efd == -1){
		perror ("epoll_create");
		abort ();
	}
	
	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);
	if (s == -1){
		perror ("epoll_ctl");
		abort ();
	}

	/* Buffer where events are returned */
	events = (epoll_event*)calloc (MAXEVENTS, sizeof event);

	return 0;
}


/**		Created for ease of error processing.
 *		
 *		@index - Index of the event causing the error.
 *		@return - Can be modified to acct for fatal errors.
 */
int EpollServer::errorHandler(int index){
	fprintf (stderr, "epoll error\n");
	close (events[index].data.fd);
	return 0;
}


/**		Called when there are one or more new clients.
 *		
 *		@return - TODO: comment on return value
 */
int EpollServer::newConnection(){
	while (1){
		struct sockaddr in_addr;
		socklen_t in_len;
		int infd;
		char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

		in_len = sizeof in_addr;
		infd = accept (sfd, &in_addr, &in_len);
		if (infd == -1){
			if ((errno == EAGAIN) || (errno == EWOULDBLOCK)){
              /* We have processed all incoming
                 connections. */
			break;
			}
			else{
				perror ("accept");
				break;
			}
		}

		s = getnameinfo (&in_addr, in_len,
						hbuf, sizeof hbuf,
						sbuf, sizeof sbuf,
						NI_NUMERICHOST | NI_NUMERICSERV);
		if (s == 0){
			printf("Accepted connection on descriptor %d "
			"(host=%s, port=%s)\n", infd, hbuf, sbuf);
		}

		/* Make the incoming socket non-blocking and add it to the
			list of fds to monitor. */
		s = makeSocketNonBlocking (infd);
		if (s == -1)
			abort ();

		event.data.fd = infd;
		event.events = EPOLLIN | EPOLLET;
		s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
		if (s == -1)
        {
			perror ("epoll_ctl");
			abort ();
		}
	}
	return 0;
}


/**		Simply add epoll_event item to the queue.
 *		
 *		@index - The index of the event.
 *		@return - TODO: comment on return value
 */
int EpollServer::newInput(int index){
	WorkItem<struct epoll_event*>* e = new WorkItem<struct epoll_event*>(&events[index], 0);
	w_queue.add(e);

	return 0;
}

