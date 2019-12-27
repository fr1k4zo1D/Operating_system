#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/sem.h>

#define shmem_file "shared_memory"

struct sembuf sem_lock = {0, -1, 0};
struct sembuf sem_unlock = {0, 1, 0};

int main()
{
	key_t key = ftok(shmem_file, 65);
	if(key == -1)
	{
		printf("bad key errno:%d", errno);
		return 0;
	}

	int shmid = shmget(key, 50, 0666);
	if(shmid == -1)
	{
		perror("Shared memoty cannot be created \n");
		return 0;
	}

	int semaphore = semget(4032, 1, 0666);
	if(semaphore == -1)
	{
		perror("Semaphore cannot be created \n");
		return 0;
	}

	char *addr = shmat(shmid, NULL, 0);
	if (addr == (char*)-1)
	{
		perror("Shmat error \n");
		return 0;
	}

	printf("Reading process: %d, %d\n", key, shmid);
	
	while(1)
	{
		semop(semaphore, &sem_lock, 1);
		printf("Reading process: Time -- %s", addr);
		sleep(1);
		semop(semaphore, &sem_unlock,1);
	}

	shmdt(shmem_file);
	shmctl(shmid, IPC_RMID, 0);
	//sem_destroy(&semaphore);
	return 0;
}
