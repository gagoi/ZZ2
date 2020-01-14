#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>

void main(int argc, char *argv[])
{
    char buffer[200],texte[200];
    int port, rc, sock,i,c;
    struct sockaddr_in addr;
    struct hostent *entree;

    if (argc != 3)
    {
        printf("usage : clientv4 nom_serveur port\n");
        exit(1);
    }

    addr.sin_port=htons(atoi(argv[2]));
    addr.sin_family=AF_INET;
    entree=(struct hostent *)gethostbyname(argv[1]);

    bcopy((char *)entree->h_addr,(char *)&addr.sin_addr,entree->h_length);

    sock= socket(AF_INET,SOCK_STREAM,0);

    if (connect(sock, (struct sockaddr *)&addr,sizeof(struct sockaddr_in)) < 0)
    {
        printf("probleme connexion\n");
        exit(1);
    }

    printf("connexion passe\n");
    while (1)
    {
        printf("1 - compter le nombre de mots\n");
        printf("2 - lettre la plus utilisee\n");
        printf("fin - quitter\n");

        bzero(texte,sizeof(texte));
        bzero(buffer,sizeof(buffer));

        i = 0;
        printf("Choix : ");
        fflush(stdout);
        while((c=getchar()) != '\n')
            texte[i++]=c;

        send(sock,texte,strlen(texte)+1,0);
        if (strcmp("fin",texte) == 0)
            break;

        recv(sock,buffer,sizeof(buffer),0);
        printf("\n%s\n",buffer);

        if (strcmp("Aucune option correspondante", buffer) != 0)
        {
            bzero(buffer,sizeof(buffer));
            bzero(texte,sizeof(texte));
            i = 0;
            while((c=getchar()) != '\n')
                texte[i++]=c;
            send(sock,texte,strlen(texte)+1,0);
            recv(sock,buffer,sizeof(buffer),0);
            printf("Reponse: %s\n\n", buffer);
        }
    }
    close(sock);
}