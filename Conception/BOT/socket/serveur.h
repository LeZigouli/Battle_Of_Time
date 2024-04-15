#ifndef _SERVEUR_H_
#define _SERVEUR_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <ifaddrs.h>
#include "../lib/common.h"
#define PORT 30000

int ma_socket;
int client_socket;
struct sockaddr_in mon_address, client_address;
unsigned int mon_address_longueur, lg;

int hostname_to_ip(char * hostname , char* ip);
void view_ip();
void init_reseau_serveur();
char* get_ip_serveur();
void serveur_fermeture(int * socket);
#endif