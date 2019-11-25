#include <stdio.h>
#include <curses.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080


int main(int argc, char* argv[]){
    

    struct sockaddr_in information_server;
    struct sockaddr_in information_client;
    int serveur = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    int nbConnexionsMax = SOMAXCONN;
    char bufferRecep[200];
    int verifListen = 0;
    int verifBind=0;
    int verifAccept = 0;
    
    information_server.sin_family = AF_INET;
    information_server.sin_addr.s_addr = htonl(INADDR_ANY);
    information_server.sin_port = htons(PORT);

    int tailleStruct = sizeof(information_server);
    if (serveur  == -1){
        printf("Erreur creation socket");
        return -1;
    }
    printf("Socket créée ... \n");
    verifBind = bind(serveur,(struct sockaddr_in *)&information_server,sizeof(information_server));
    if(verifBind =! 0){
        printf("Le bind ne s'est pas bien déroulé");
        exit(0);
    }
    printf("Le bind marche ...\n");
    verifListen = listen(serveur,SOMAXCONN);
    if(verifListen != 0) {
        printf("Le listen n'a pas marché");
        exit(0);
    }
    printf("Le listen fonctionne ... \n");
    verifAccept = accept(serveur,(struct sockaddr_in *) &information_server, sizeof(information_server));
    if(verifAccept < 0){
        printf("Le accept n'a pas pu aboutir");
        exit(0);
    }
    printf("Le Accepte marche ... \n");
}
