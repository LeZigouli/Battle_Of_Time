/**
 * \file client.h
 * \brief Contient les élements utilisé par le client.c
 * \author Proudy Vincent
 * \date 09 févrirer 2024
 * 
*/

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
#include <fcntl.h>

#define PORT 30000
#define MAX_IP 20
#define QUITTER "QUITTER"

/**
 * @brief Nom du serveur.
 */
char serveurname[MAX_IP];

/**
 * @brief Structure d'adresse du serveur.
 */
struct sockaddr_in serveur_addr;

/**
 * @brief Informations sur le serveur.
 */
struct hostent *serveur_info;

/**
 * @brief Adresse IP du serveur.
 */
long hostAddr;

/**
 * @brief Buffer pour les données.
 */
char buffer[512];

/**
 * @brief Socket du client vers le serveur.
 */
int to_server_socket;

int init_reseau_client(char serveurname[MAX_IP]);
void envoyer_structure( int to, player_t player1, player_t player2 );
void recevoir_structure( int to, player_t * player1, player_t * player2 );
void client_fermeture(int * socket);

#endif