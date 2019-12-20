#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


main()
{
   unlink("FIFO"); 
   int fifo = mkfifo ("FIFO", 0777);
   if(fifo < 0)
	printf("Fifo cannot be created \n");
   pid_t pid;
   switch(pid = fork())
   {
	case 0:
        {
	    int fifo_read = open("FIFO", O_RDONLY);
	    if (fifo_read == -1)
	    	printf("Фифио не может открыть файл на чтение \n");
	    char *buf = (char*) calloc (25, sizeof(char));
	    read(fifo_read, buf, 5);
	    printf("CHILD: Пид бати = %s\n", buf);
	    read(fifo_read, buf, 25);
	    printf("CHILD: Время у бати = %s\n", buf); 
	    close(fifo_read);
	    time_t child_time = time(0);
	    printf("CHILD: Мое время = %s\n", ctime(&child_time));
	    
	    break;
	}

	default:
	{
	    
	    int fifo_write = open("FIFO", O_WRONLY);
	    if(fifo_write == -1)
		printf("Фифо не может открыть файл на запись \n");
	    time_t parent_time = time(0);
	    pid_t  parent_pid = getpid();
	    char buff[25];
	    sprintf(buff, "%d", parent_pid);
		printf("PARENT: Мое время = %s\n",ctime(&parent_time));
	    printf("PARENT: Мой пид = %d\n", parent_pid);
	    write(fifo_write, &buff, strlen(buff));
	    write(fifo_write, ctime(&parent_time), 50);
	    close(fifo_write);
	    break;
	    
       } 
    } 
   
    return 0;
}
