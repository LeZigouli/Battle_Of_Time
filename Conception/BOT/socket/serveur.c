#include "serveur.h"

int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        perror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }
     
    return 1;
}

void view_ip()
{
  char s[256];
  struct hostent *host;
  struct in_addr **adr;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
          printf("IP : %s\n", inet_ntoa(**adr));
}

void init_reseau_serveur()
{
    bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(PORT);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
    char ip[100];
     
    hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s\n" , hostname , ip);
    view_ip();

	/* creation de socket */
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}

	/* bind serveur - socket */
	bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
	/* ecoute sur la socket */
	listen(ma_socket,5);
	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);
	
    /* on attend que le client se connecte */
	client_socket = accept(ma_socket,
                         (struct sockaddr *)&client_address,
                         &mon_address_longueur);
}

char* get_ip_serveur()
{
    struct ifaddrs *addr, *intf;
    char * hostname = malloc(sizeof(char)*MAX_STR);

    int family, s;
    
    if (getifaddrs(&intf) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
    for (addr = intf; addr != NULL; addr = addr->ifa_next) {
        family = addr->ifa_addr->sa_family;
        //AF_INET est la famille d'adresses pour IPv4
        if (family == AF_INET) {
          //getnameinfo permet la résolution de noms.
          s = getnameinfo(addr->ifa_addr, 
                          sizeof(struct sockaddr_in),
                          hostname, 
                          MAX_STR, 
                          NULL, 
                          0, 
                          NI_NUMERICHOST);

          if( strcmp(hostname,"127.0.0.1") != 0 )
          {
            return hostname;
          }
        }
    }
    return hostname;
}
 
void serveur_fermeture(int * socket)
{
    shutdown(*socket,2);
	close(*socket);
}