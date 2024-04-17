/**
 * \file serveur.h
 * \brief Contient les élements utilisé par le serveur.c
 * \author Proudy Vincent
 * \date 09 févrirer 2024
 * 
 * 
*/

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

/**
 * @brief Socket du serveur.
 */
int ma_socket;


/**
 * @brief Socket du client.
 */
int client_socket;

/**
 * @brief Adresse du serveur et Adresse du client
 */
struct sockaddr_in mon_address;

/**
 * @brief Adresse du client
 */
struct sockaddr_in client_address;

/**
 * @brief Longueur de l'adresse du serveur.
 */
unsigned int mon_address_longueur;

/**
 * @brief Taille des données à lire/écrire.
 */
unsigned int lg;

int hostname_to_ip(char * hostname , char* ip);
void view_ip();
int init_reseau_serveur();
char* get_ip_serveur();
void serveur_fermeture(int * socket);
#endif