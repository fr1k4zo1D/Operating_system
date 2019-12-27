#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define END_OF_RECORD 11

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

int data[100];
int size = 0;

void *writing_threadFunc(void *arg)
{
	printf("Writing thread %u\n", (unsigned int)pthread_self());
	while(1)
	{
		pthread_rwlock_wrlock(&lock);

		if(size ==  END_OF_RECORD)
		{
			pthread_rwlock_unlock(&lock);
			break;
		}
		printf("Writing thread: Recorded the value -- %d\n", size);
		size++;
		data[size] = size;
		pthread_rwlock_unlock(&lock);

		sleep(3);
	}

	printf("Writing thread: Exit \n");
	printf("\n");
	pthread_exit(0);
}


void *reading_threadFunc(void *arg)
{
	int flag = 0;
	while(1)
	{
		pthread_rwlock_rdlock(&lock);

		if(flag == 1)
		{
			pthread_rwlock_unlock(&lock);
			break;
		}
		
		//printf("Reading thread %u\n", (unsigned int)pthread_self());
		int j;
		for(j = 0; j<size; j++)
		{
			printf(" %d, Reading thread:  %u\n", data[j], (unsigned int)pthread_self());
			//printf("Reading thread %u\n", (unsigned int)pthread_self());
			//printf("%d\n", data[j]);
		}

		if(size ==  END_OF_RECORD)
		{
			flag = 1;
		}

		pthread_rwlock_unlock(&lock);
		sleep(1);
	}

	printf("Reading thread: Exit   %u\n", (unsigned int)pthread_self());
	pthread_exit(0);
}

int main()
{
	pthread_t read[10];
	pthread_t write;
	pthread_rwlock_init(&lock, NULL);

	pthread_create(&write, NULL, writing_threadFunc, NULL);
	int i;
	for(i = 0; i<10; i++)
	{
		pthread_create(&read[i], NULL, reading_threadFunc, NULL);
	}
	pthread_join(write, NULL);
	//sleep(2);
	for(i = 0; i<10; i++)
	{
		pthread_join(read[0], NULL);
	}

	printf("End of record \n");
	
	pthread_rwlock_destroy(&lock);

	return 0;
}
