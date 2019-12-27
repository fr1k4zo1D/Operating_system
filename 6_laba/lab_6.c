#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define END_OF_RECORD 11

pthread_mutex_t mutex;

int data[1024];
int size = 0;

void *writing_threadFunc(void *arg)
{
	printf("Writing thread %u\n", (unsigned int)pthread_self());
	while(1)
	{
		pthread_mutex_lock(&mutex);

		if(size ==  END_OF_RECORD)
		{
			pthread_mutex_unlock(&mutex);
			break;
		}

		size++;
		data[size] = size;
		pthread_mutex_unlock(&mutex);

		sleep(1);
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
		pthread_mutex_lock(&mutex);

		if(flag == 1)
		{
			pthread_mutex_unlock(&mutex);
			break;
		}
		
		printf("Reading thread %u\n", (unsigned int)pthread_self());
		int i;
		for(i = 0; i<size; i++)
		{
			printf("%d\n", data[i]);
		}

		if(size ==  END_OF_RECORD)
		{
			flag = 1;
		}

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	printf("Reading thread: Exit   %u\n", (unsigned int)pthread_self());
	pthread_exit(0);
}

int main()
{
	pthread_t read[10];
	pthread_t write;
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
		pthread_join(read[i], NULL);
	}

	printf("End of record \n");	
	pthread_mutex_destroy(&mutex);

	return 0;
}
