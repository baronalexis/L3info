#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/sem.h>

#define TAILLE 1024



void ecrire_tableau(int *compteur, char *tableau) {
  char message[64], *msg=message;
  snprintf(message, 64, "Je suis le processus %d!\n", getpid());

  while ((*compteur<TAILLE)&&(*msg)) {
    tableau[*compteur] = *msg;
    msg++;
    usleep(100000);
    (*compteur)++;
  }
}


int main(void) 
{ 
    key_t key; 
    int semid; 

    struct sembuf up	= {0, 1, 0};
	struct sembuf down	= {0, -1, 0};

    int id, *compteur;
    char *tableau;

    if ((key = ftok("tp3.c", 'J')) == -1) { 
        perror("ftok"); 
        exit(1); 
    }
	
    semid = semget(key, 1, 0600);

	if (semid < 0) { 
		semid = semget(key, 1, 0600|IPC_CREAT);
		if (semid < 0) { perror("Error semget"); exit(1); }
		semop(semid, &up, 1);
	}


    id = shmget((key_t)1234, TAILLE + sizeof(int),0600|IPC_CREAT);
    if (id < 0) { perror("Error shmget"); exit(1); }

    compteur = (int*) shmat(id,0,0);
    if (compteur == NULL) { perror("Error shmat"); exit(1); }
    tableau = (char *)(compteur + 1);

    if (semop(semid, &down, 1) == -1) { 
        perror("Error semop"); 
        exit(1); 
    } 
    
    ecrire_tableau(compteur, tableau);

    if (semop(semid, &up, 1) == -1) { 
        perror("Error semop"); 
        exit(1); 
    }

    printf("%s\n", tableau);

    if (shmdt(compteur)<0) { perror("Error shmdt"); exit(1); }



    return 0; 
} 