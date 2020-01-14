#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>

int count(char * string, char l)
{
    int i = 0, cmp = 0;
    while (string[i])
        cmp += string[i++] == l ? 1 : 0;
    return cmp;
}

char lettre(char * string)
{
    int i = 0, nb = 0, newNb = 0;
    char let = ' ';
    while (string[i])
    {
        newNb = count(string, string[i]);
        if (nb < newNb)
        {
            nb = newNb;
            let = string[i];
        }
        i++;
    }
    return let;
}

int main(int argc, char** argv)
{
    int s_ecoute, scom, i, j, cmp;
    unsigned long lg_app;
    struct sockaddr_in adr;
    struct sockaddr_storage recep;
    char buffer[1500], renvoi[1500], host[1024], service[20];

    s_ecoute = socket(AF_INET, SOCK_STREAM, 0);
    printf("Création du socket\n");

    adr.sin_family = AF_INET;
    adr.sin_port = htons(atoi(argc > 1 ? argv[1] : "8125"));
    adr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s_ecoute, (struct sockaddr*)&adr, sizeof(struct sockaddr_in)) != 0)
    {
        printf("Problème de bind sur v4\n");
        exit(1);
    }

    if (listen(s_ecoute, 5) != 0)
    {
        printf("Pb d'écoute\n");
        exit(1);
    }

    printf("En attente de connexion...\n");

    while(1)
    {
        scom = accept(s_ecoute, (struct sockaddr*)&recep, &lg_app);
        getnameinfo((struct sockaddr*)&recep, sizeof(recep), host, sizeof(host), service, sizeof(service), 0);
        printf("Recu de %s venant du port %s\n", host, service);

        while(1)
        {
            recv(scom, buffer, sizeof(buffer), 0);
            printf("recu: %s\n", buffer);

            bzero(renvoi, sizeof(renvoi));
            if (atoi(buffer) == 1)
            {
                bzero(buffer, sizeof(buffer));
                sprintf(renvoi, "OK, ecrivez une phrase pour compter le nombre de mots:");
                send(scom, renvoi, strlen(renvoi), 0);
                printf("envoye: %s\n", renvoi);

                recv(scom, buffer, sizeof(buffer), 0);

                bzero(renvoi, sizeof(renvoi));
                sprintf(renvoi, "Votre phrase a %d mots", count(buffer, ' ') + 1);
                send(scom, renvoi, strlen(renvoi), 0);
                printf("envoye: %s\n", renvoi);
            }
            else if (atoi(buffer) == 2)
            {
                bzero(buffer, sizeof(buffer));
                sprintf(renvoi, "OK, ecrivez une phrase pour voir la lettre la plus utilisee:");
                send(scom, renvoi, strlen(renvoi), 0);
                printf("envoye: %s\n", renvoi);

                recv(scom, buffer, sizeof(buffer), 0);

                bzero(renvoi, sizeof(renvoi));
                sprintf(renvoi, "La lettre la plus utilisee est \"%c\"", lettre(buffer));
                send(scom, renvoi, strlen(renvoi), 0);
                printf("envoye: %s\n", renvoi);
            }
            else if (strcmp(buffer, "fin") == 0)
            {
                break;
            }
            else
            {
                sprintf(renvoi, "Aucune option correspondante");
                send(scom, renvoi, strlen(renvoi), 0);
                printf("envoye: %s\n", renvoi);
            }
        }
        close(scom);
    }
    close(s_ecoute);
}