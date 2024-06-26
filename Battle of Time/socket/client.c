/**
 * \file client.c
 * \brief Contient les fonctions pour le reseau coté client
 * \author Proudy Vincent
 * \date 09 avril 2024
 * \version 1.0
 * 
*/

#include "client.h"

/**
 * \fn void envoyer( int to, int * action, int * action2 )
 * \brief Envoie des données via le socket spécifié.
 *
 * \param to Le socket destinataire.
 * \param action Pointeur vers la première action à envoyer.
 * \param action2 Pointeur vers la deuxième action à envoyer.
 */
void envoyer( int to, int * action, int * action2 )
{
	send(to, action, sizeof(*action),0);
    send(to, action2, sizeof(*action2),0);
}

/**
 * \fn void recevoir( int to, int * action, int * action2 )
 * \brief Réception des données depuis le socket spécifié.
 *
 * \param to Le socket destinataire.
 * \param action Pointeur vers la première action à recevoir.
 * \param action2 Pointeur vers la deuxième action à recevoir.
 */
void recevoir( int to, int * action, int * action2 )
{
	recv(to, action, sizeof(*action),0);
    recv(to, action2, sizeof(*action2),0);
}

/**
 * \fn int init_reseau_client(char serveurname[MAX_IP])
 * \brief Initialise la connexion au serveur.
 * 
 * \param serveurname Nom ou adresse IP du serveur.
 * \return Retourne 1 si l'initialisation est réussie, sinon 0.
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
 * \fn void client_fermeture(int * socket)
 * \brief Ferme la connexion au serveur.
 * 
 * \param socket Pointeur vers la socket à fermer.
 */
void client_fermeture(int * socket)
{
	shutdown(*socket,2);
	close(*socket);
}
