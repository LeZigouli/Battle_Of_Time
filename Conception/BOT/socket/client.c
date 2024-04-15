#include "client.h"

void envoyer_structure( int to, player_t player1, player_t player2 )
{
	send(to, &player1, sizeof(player1),0);
	send(to, &player2, sizeof(player2),0);
}

void recevoir_structure( int to, player_t * player1, player_t * player2 )
{
	recv(to,player1,sizeof(*player1),0);
	recv(to,player2,sizeof(*player2),0);
}

void init_reseau_client(char serveurname[MAX_IP])
{
	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(serveurname);

	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	} else {
		serveur_info = gethostbyname(serveurname);
	  	if (serveur_info == NULL) {
			printf("Impossible de récupérer les infos du serveur\n");
			exit(0);
	  	}
	  	bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
	}

	serveur_addr.sin_port = htons(PORT);
	serveur_addr.sin_family = AF_INET;

	/* creation de la socket */
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("Impossible de créer la socket client\n");
	  	exit(0);
	}
	/* requete de connexion */
	if(connect( to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
	  	exit(0);
	}
}

void client_fermeture(int * socket)
{
	shutdown(*socket,2);
	close(*socket);
}
