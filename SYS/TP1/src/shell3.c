#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {


	pid_t pid, pid1;
	
    char buffer1[1024];
    char buffer2[1024];

	char *params1[512];
	char *params2[512];


	char *arg = NULL;

	int i = 0;
	int j;
	int fd[2];

    printf("cmd1-> ");
    fgets(buffer1, sizeof buffer1, stdin);
    buffer1[strcspn(buffer1, "\n")] = 0;

    arg = strtok (buffer1, " ");

    while (arg != NULL)
    {
        params1[i++] = arg;
        arg = strtok (NULL, " ");
    }

    params1[i++] = NULL;


    if (strcmp(buffer1, "exit") == 0) {
        exit(0);
    }
    
    i = 0;
    
    printf("cmd2-> ");
    fgets(buffer2, sizeof buffer2, stdin);
    buffer2[strcspn(buffer2, "\n")] = 0;

    arg = strtok (buffer2, " ");

    while (arg != NULL)
    {
        params2[i++] = arg;
        arg = strtok (NULL, " ");
    }

    params2[i++] = NULL;




	while(strcmp(buffer1, "exit") != 0 && strcmp(buffer2, "exit") != 0){

		
		if(pipe(fd) < 0) exit(1);
		
		pid = fork();

		if(pid < 0) {
			perror("Erreur fork");
			exit(1);
		}

		if(pid == 0) { // 1er fils
			dup2(fd[1], 1);

			close(fd[0]);
			close(fd[1]);

			execvp(params1[0], params1);
            perror("erreur exec");
            exit(1);
		}
		else { // pere
            pid1 = fork();
            
            if (pid1 < 0 ) {
                perror("erreur fork");
                exit(1);
            }

			else if(pid1 == 0) { // 2e fils
				dup2(fd[0], 0);
				
				close(fd[0]);
				close(fd[1]);
				
				execvp(params2[0], params2);
                perror("erreur exec");
                exit(1);
			}
		}

		close(fd[0]);
		close(fd[1]);
		for(j = 0; j <= 1; j++){
			wait(NULL);
		}
            printf("cmd1-> ");
    fgets(buffer1, sizeof buffer1, stdin);
    buffer1[strcspn(buffer1, "\n")] = 0;

    arg = strtok (buffer1, " ");

    while (arg != NULL)
    {
        params1[i++] = arg;
        arg = strtok (NULL, " ");
    }

    params1[i++] = NULL;

   if (strcmp(buffer1, "exit") == 0) {
        exit(0);
    }
    
    i = 0;
    
    printf("cmd2-> ");
    fgets(buffer2, sizeof buffer2, stdin);
    buffer2[strcspn(buffer2, "\n")] = 0;

    arg = strtok (buffer2, " ");

    while (arg != NULL)
    {
        params2[i++] = arg;
        arg = strtok (NULL, " ");
    }

    params2[i++] = NULL;
	}
	exit(0);
		
}
