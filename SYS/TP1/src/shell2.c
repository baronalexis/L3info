#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main ()
{
    pid_t pid;
    int i = 0;
    int status;
    char buffer[50];
    char *param[50];
    char *p = NULL;

    printf("-> ");
    fgets(buffer, 50, stdin);
    buffer[strcspn(buffer, "\n")] = 0;


    p = strtok (buffer, " ");

    while (p != NULL)
    {
        param[i++] = p;
        p = strtok (NULL, " ");
    }

    param[i++] = NULL;





    while(strcmp(param[0], "exit") != 0) {
        
        pid = fork();

        if(pid < 0) {
            perror("erreur fork");
            exit(1);
        }

        if(pid != 0) { // père
            wait(&status);
            printf("\n-> ");
            fgets(buffer, 50, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            p = strtok (buffer, " ");
            i = 0;
            while (p != NULL)
            {
                param[i++] = p;
                p = strtok (NULL, " ");
            }

            param[i++] = NULL;


        }
        else { // fils
            execvp(param[0], param);
            perror("erreur exec");
            exit(1);
        }
    }
    exit(0);
} 
