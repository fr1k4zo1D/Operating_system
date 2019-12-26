#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FOR_ALL 0777
#define size_of_time 25
#define size_of_pid 5
#define FIFO_file "FIFO" 

main()
{
	unlink(FIFO_file); 
	int fifo = mkfifo (FIFO_file, FOR_ALL);
	if(fifo < 0)
	{
		printf("Fifo cannot be created \n");
		return 0;
	}
	pid_t pid;
	switch(pid = fork())
	{
		case 0:
        {
	    	int fifo_read = open(FIFO_file, O_RDONLY);
	    	if (fifo_read == -1)
			{
	    		printf("Фифио не может открыть файл на чтение \n");
	    		break;
			}
			char *buf = (char*) calloc (size_of_time, sizeof(char));
	    	read(fifo_read, buf, size_of_pid);
	    	printf("CHILD: Пид бати = %s\n", buf);
	    	read(fifo_read, buf, size_of_time);
	    	printf("CHILD: Время у бати = %s\n", buf); 
	    	close(fifo_read);
			sleep(1);
	    	time_t child_time = time(NULL);
	    	printf("CHILD: Мое время = %s\n", ctime(&child_time));	    
	    	break;
		}

		default:
		{
	    	int fifo_write = open(FIFO_file, O_WRONLY);
	    	if(fifo_write == -1)
			{
				printf("Фифо не может открыть файл на запись \n");
	    		break;
			}
			time_t parent_time = time(NULL);
	    	pid_t  parent_pid = getpid();
	    	char buff[size_of_time];
	    	sprintf(buff, "%d", parent_pid);
			printf("PARENT: Мое время = %s\n",ctime(&parent_time));
	    	printf("PARENT: Мой пид = %d\n", parent_pid);
	    	write(fifo_write, &buff, strlen(buff));
	    	write(fifo_write, ctime(&parent_time), size_of_time*2);
	    	close(fifo_write);
	    	break;
	    
       } 
	} 
   
	return 0;
}
