/**
 * \file client.c
 * \brief Contient les fonctions pour le reseau coté client
 * \author Proudy Vincent
 * \date 09 févrirer 2024
 * \version 1.0
 * 
*/

#include "client.h"

/**
 * @brief Envoie les structures des joueurs au serveur.
 * 
 * @param to Socket vers laquelle envoyer les structures.
 * @param player1 Structure représentant le joueur 1.
 * @param player2 Structure représentant le joueur 2.
 */
void envoyer_structure( int to, player_t player1, player_t player2 )
{
	send(to, &player1, sizeof(player1),0);
	send(to, &player2, sizeof(player2),0);
}

/**
 * @brief Reçoit les structures des joueurs depuis le serveur.
 * 
 * @param to Socket depuis laquelle recevoir les structures.
 * @param player1 Pointeur vers la structure représentant le joueur 1.
 * @param player2 Pointeur vers la structure représentant le joueur 2.
 */
void recevoir_structure( int to, player_t * player1, player_t * player2 )
{
	recv(to,player1,sizeof(*player1),0);
	recv(to,player2,sizeof(*player2),0);
}

/**
 * @brief Initialise la connexion au serveur.
 * 
 * @param serveurname Nom ou adresse IP du serveur.
 * @return Retourne 1 si l'initialisation est réussie, sinon 0.
 */
int init_reseau_client(char serveurname[MAX_IP])
{
	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(serveurname);

	if ( (long)hostAddr != (long)-1 )
	{
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	} 
	else 
	{
		serveur_info = gethostbyname(serveurname);
	  	if (serveur_info == NULL)
		 {
			printf("Impossible de récupérer les infos du serveur\n");
			return(0);
	  	}
	  	bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
	}

	serveur_addr.sin_port = htons(PORT);
	serveur_addr.sin_family = AF_INET;
	if ((to_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Impossible de créer la socket client\n");
        return 0;
    }


    /* rendre la socket non bloquante */
    if (fcntl(to_server_socket, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl");
        close(to_server_socket);
        return 0;
    }

	int connexion = connect(to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr));

    /* tentative de connexion */
    if (connexion < 0) {
        if (errno != EINPROGRESS) {
            printf("Impossible de se connecter au serveur\n");
            close(to_server_socket);
            return 0;
    }
        printf("Connexion en cours...\n");

        fd_set write_fds;
        FD_ZERO(&write_fds);
        FD_SET(to_server_socket, &write_fds);

        struct timeval timeout;
        timeout.tv_sec = 3; // 10 secondes
        timeout.tv_usec = 0;

        int select_ret = select(to_server_socket + 1, NULL, &write_fds, NULL, &timeout);
        if (select_ret == -1) {
            perror("select");
            close(to_server_socket);
            return 0;
        } else if (select_ret == 0) {
            printf("Timeout lors de la connexion\n");
            close(to_server_socket);
            return 0;
        }

        int optval;
        socklen_t optlen = sizeof(optval);
        if (getsockopt(to_server_socket, SOL_SOCKET, SO_ERROR, &optval, &optlen) == -1) {
            perror("getsockopt");
            close(to_server_socket);
            return 0;
        }

        if (optval != 0) {
            printf("Erreur lors de la connexion: %s\n", strerror(optval));
            close(to_server_socket);
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Ferme la connexion au serveur.
 * 
 * @param socket Pointeur vers la socket à fermer.
 */
void client_fermeture(int * socket)
{
	shutdown(*socket,2);
	close(*socket);
}
