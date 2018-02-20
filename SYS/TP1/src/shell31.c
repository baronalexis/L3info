#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




void input(char * disp, char * params[512]) {


    int i = 0;

    char buffer[1024];
   	char *arg = NULL;


    printf("%s", disp);
    fgets(buffer, sizeof buffer, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    arg = strtok (buffer, " ");

    while (arg != NULL)
    {
        params[i++] = arg;
        arg = strtok (NULL, " ");
    }

    params[i++] = NULL;


}


int main() {

	pid_t pid, pid1;
    

	char *params1[512];
	char *params2[512];



	int j;
	int fd[2];

    input("cmd1 >", params1);

    input("cmd2 >", params2);




	while(strcmp(params1[0], "exit") != 0 && strcmp(params2[0], "exit") != 0){

		printf("%s", params1[0]);
        printf("%s", params2[0]);

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
    input("cmd1 >", params1);
    input("cmd2 >", params2);
	}
	exit(0);
		
}
