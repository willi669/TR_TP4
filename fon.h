#include <stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>

void adr_socket( char *service, char *serveur, int typesock,
		 struct sockaddr_in **p_adr_serv);