#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <sys/shm.h>

#define TAILLE 1024

int main(void) 
{ 
    key_t key; 
    int semid;
	int id, del;

    union semun {
        int val;
        struct semid_ds *buf;
        ushort *array;
    } arg;


  	id = shmget((key_t)1234,TAILLE+sizeof(int),0600|IPC_CREAT);
	if (id < 0) { perror("Error shmget"); exit(1); }

	del = shmctl(id, IPC_RMID, NULL);
	if (del < 0) { perror("Error shmctl"); exit(1); }


    if ((key = ftok("tp3.c", 'J')) == -1) { 
        perror("ftok"); 
        exit(1); 
    } 
    if ((semid = semget(key, 1, 0)) == -1) { 
        perror("semget"); 
        exit(1); 
    }

    if (semctl(semid, 0, IPC_RMID, arg) == -1) { 
        perror("semctl"); 
        exit(1); 
    } 
    return 0; 
} 