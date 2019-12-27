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

#define shmem_file "shared_memory"

int main()
{
	key_t key = ftok(shmem_file, 65);
	int shmid = shmget(key, 50, 0666);
	if(shmid == -1)
	{
		perror("Shared memoty cannot be created \n");
		return 0;
	}

	char *addr = shmat(shmid, NULL, 0);
	if (addr == (char*)-1)
	{
		perror("Shmat error \n");
		return 0;
	}

	printf("Reading process: :%d, %d\n", key, shmid);

	while(1)
	{
		printf("Reading process: Time -- %s", addr);
		sleep(1);
	}
	
	shmdt(shmem_file);
	shmctl(shmid, IPC_RMID, 0);
	return 0;
}
