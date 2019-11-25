#include<stdio.h>
#include<unistd.h>
#include <stdarg.h>
#include <string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>

#include "fon.h"

void adr_socket ( char *service, char *nom, int typesock,
		  struct sockaddr_in **p_adr_serv)
{
    struct addrinfo hints; /* info à passer a getaddrinfo */
    struct addrinfo *res; /* permet de recuperer les adresses a l aide de getaddrinfo */
    char ipstr[INET6_ADDRSTRLEN], ipver;
    int s;
    void *addr;

	
#ifdef DEBUG
	printf("\n%s ADR_SOCKET (debut) .........\n",aff_debug);
#endif


	/* RENSEIGNEMENT ADRESSES SOCKET  ------------------------------*/

	/* Mise a zero de la structure d'adresse socket */
    memset(&hints, 0, sizeof(struct addrinfo));

	/* Definition du domaine ( famille ) 	*/
    /*hints.ai_family = AF_UNSPEC; */   /* Allow IPv4 or IPv6 */
    hints.ai_family = AF_INET; /* on force  IPV4 */
    hints.ai_socktype = typesock; /* SOCK_DGRAM (UDP) ou SOCK_STREAM (TCP) */
    hints.ai_protocol = 0;          /* Any protocol */

	/* ------ RENSEIGNE @IP -----------------------------------------*/
        if (nom==NULL) /* Cas d'un serveur */
          hints.ai_flags = AI_PASSIVE;
        else
            hints.ai_flags = 0;

	s = getaddrinfo(nom, service, &hints, &res);
    if (s != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    *p_adr_serv=(struct sockaddr_in *)res->ai_addr;
    
#ifdef DEBUG
    if (res->ai_family == AF_INET) { // IPv4
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = '4';
    }
    else { // IPv6
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = '6';
    }
    
    // Conversion de l'adresse IP en une chaîne de caractères
    inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
    
	printf("%s adresse IPv%c : %s OK..........\n",aff_debug,ipver,ipstr);

#endif

	

#ifdef DEBUG
	printf("%s port : %d OK .........\n", aff_debug, ntohs((*p_adr_serv)->sin_port)); /*Modif PS */
	printf("%s ADR_SOCKET (fin) .........\n",aff_debug); 
#endif

/*Pas terrible les structures pointees par res ne sont pas liberees */
}