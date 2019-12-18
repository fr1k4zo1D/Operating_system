#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

main()
{
    int pipes[2];
    pid_t pid;
    pipe (pipes);
    pid = fork();

    if (pid==0)	 
    {
	time_t buf;
	close(pipes[1]);
	read(pipes[0], &buf, sizeof(time_t));
	printf("CHILD: Время родителя %s", ctime(&buf));
	pid_t parent_pid1;
	read(pipes[0], &parent_pid1, sizeof(pid_t));
	printf("CHILD: Пид родителя -- %d\n", parent_pid1);
	time_t child_time = time(0);	
	close(pipes[0]);
	printf("CHILD: Мое время : %s\n", ctime(&child_time));
	exit(0);
    }

    else
    {
	time_t parent_time = time(0);
	pid_t parent_pid = getpid();
	close(pipes[0]);
	printf("PARENT: Мой пид -- %d\n", parent_pid);
	printf("PARENT: Мое время = %s\n" , ctime(&parent_time));
	write(pipes[1], &parent_time, sizeof(time_t));
	write(pipes[1], &parent_pid, sizeof(pid_t));		
	close(pipes[1]);
    }

return 0;
}
