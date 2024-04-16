#ifndef _CLIENT_H__
#define _CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include "../lib/player.h"
#include "../lib/common.h"
#include <stdbool.h>
#include <regex.h>
#define PORT 30000
#define MAX_IP 10
#define QUITTER "QUITTER"

char serveurname[MAX_IP];

struct sockaddr_in serveur_addr;
struct hostent *serveur_info;
long hostAddr;
char buffer[512];
int to_server_socket;

int init_reseau_client(char serveurname[MAX_IP]);
void envoyer_structure( int to, player_t player1, player_t player2 );
void recevoir_structure( int to, player_t * player1, player_t * player2 );
void client_fermeture(int * socket);

#endif