#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAXCMD 100


void welcomeScreen() {
    printf("=======================================\n");
    printf("#                                     #\n");
    printf("#                Shell 1              #\n");
    printf("#                                     #\n");
    printf("=======================================\n");
    printf("\n");
}


int main ()
{
    pid_t pid;
    int status;
    char *buffer = malloc(MAXCMD);
    char *pwd = NULL;

    welcomeScreen();

    printf("%s-> ", getcwd(pwd, 1024));
    fgets(buffer, MAXCMD, stdin);

    buffer[strcspn(buffer, "\n")] = 0;

    while(strcmp(buffer, "exit") != 0) {
        
        pid = fork();

        if(pid < 0) {
            perror("erreur fork");
            exit(1);
        }

        if(pid != 0) { // père
            wait(&status);
            printf("\n%s-> ", getcwd(pwd, 1024));
            fgets(buffer, 50, stdin);
            buffer[strcspn(buffer, "\n")] = 0;


        }
        else { // fils
            execlp(buffer, buffer, (char*)NULL);
            perror("erreur exec");
            exit(1);
        }
    }
    exit(0);
} 
