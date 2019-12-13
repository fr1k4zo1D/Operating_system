#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	void new_process();
	new_process();
	return 0;
}

void new_process(){
	pid_t pid;
	int rv=0;
	void end_of_process();
	switch(pid=fork()){
		case -1 :
			perror("fork");
			exit(1);
		case 0 :
			atexit(end_of_process);
			printf("CHILD:это процесс потомок\n");
			printf("CHILD: мой PID -- %d\n", getpid());
			printf("CHILD:PID моего родителя -- %d\n", getppid());
			printf("CHILD:Введите мой код возврата:\n");
			scanf("%d",&rv);
			printf("CHILD:Выход! \n");
			exit(rv);
		default:
			atexit(end_of_process);
			printf("PARENT:это процесс родитель\n");
			printf("PARENT: мой PID -- %d\n", getpid());
			printf("PARENT:PID моего потомка -- %d\n", pid);
			printf("PARENT:Жду пока потомок не вызовет exit()...\n");
			wait(NULL);
			printf("PARENT: Код возврата потомка : %d\n",WEXITSTATUS(rv));
			printf("CHILD:Выход!\n");
}}

void end_of_process()
{
	printf("Сработал вызов atexit() \n");
}
