#include <stdio.h>
#include <curses.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


#define PORT_DEFAUT "9999"
#define SERVEUR_DEFAUT "127.0.0.1"

void client(char *serveur, char *port, char *pseudo);

int main (int argc, char **argv){

    char *serveur = SERVEUR_DEFAUT;
    char *port = PORT_DEFAUT;

    switch (argc){
        case 1 :
            printf("Serveur par defaut: %s\n",serveur);
		    printf("Port par defaut: %s\n",port);
            break;
        case 2 :
            serveur = argv[1];
            printf("Serveur de connection : %s\n",serveur);
            printf("Port par defaut: %s\n",port);
            break;
        case 3 :
            serveur = argv[1];
            port = argv[2];
            printf("Serveur de connection : %s\n",serveur);
            printf("Port de connection : %s\n",port);
            break;
        default :
            printf("Erreur usage : il faut fournir un numéro de serveur et de port\n");
            exit(1);
    }

    char *pseudo;

    printf("\n Entrez votre pseudo de 6 caractères : ");
    scanf("%s",&pseudo);

    while (strlen(pseudo) != 6){
        printf("\n Entrez votre pseudo de 6 caractères : ");
        scanf("%s",&pseudo);
    }

    client(serveur,port,pseudo);
}


/*********************************************************************/


void vider_string(char string[20]){
	for (int i = 0; i<20; i++){
		string[i] = ' ';
	}
}

void client (char *serveur, char *port, char *pseudo){

    int id_socket;
    char message[20];

    struct sockaddr_in adr_socket_in, adr_socket_out;

    id_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    adr_socket(port, serveur, SOCK_STREAM, &adr_socket_out);

    bind(id_socket, &adr_socket_in, sizeof(adr_socket_in));
    
    connect(id_socket, &adr_socket_out);


}