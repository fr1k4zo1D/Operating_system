#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>

void print_perms(mode_t perms)
{
	if(perms & S_IFREG)
		printf("-");
	else if(perms & S_IFLNK)
		printf("l");
	else if(perms & S_IFDIR)
		printf("d");
	else if(perms & S_IFCHR)
		printf("c");
	else if(perms & S_IFBLK)
		printf("b");
	else if(perms & S_IFIFO)
		printf("p");
	else if(perms & S_IFSOCK)
		printf("s");

	printf( (perms & S_IRUSR) ? "r" : "-");
	printf( (perms & S_IWUSR) ? "w" : "-");
	printf( (perms & S_IXUSR) ? "x" : "-");
	printf( (perms & S_IRGRP) ? "r" : "-");
	printf( (perms & S_IWGRP) ? "w" : "-");
	printf( (perms & S_IXGRP) ? "x" : "-");
	printf( (perms & S_IROTH) ? "r" : "-");
	printf( (perms & S_IWOTH) ? "w" : "-");
	printf( (perms & S_IXOTH) ? "x" : "-");

}

int main()
{
	DIR* dptr ;
	struct dirent* ds;
	struct stat buf;
	struct passwd *pwd;
	struct group *grp;
	struct tm *tm;
	char datestring[256];
	dptr = opendir("./");
	while((ds = readdir(dptr)) != NULL )
	{
	//	printf("%s \n" ,ds->d_name);
//		name = ds->d_name;
		stat(ds->d_name,&buf);
		print_perms(buf.st_mode);
		printf("%2d", buf.st_nlink);
		if((pwd = getpwuid(buf.st_uid))!=NULL)
			printf(" %-9.9s " , pwd->pw_name);
		else
			printf(" %-8d " , buf.st_uid);
		if((grp = getgrgid(buf.st_gid))!=NULL)
			printf("%-9.9s" , grp->gr_name);
		else
			printf("%-8d" , buf.st_gid);
		
		printf("%5jd", (intmax_t)buf.st_size);
		
		tm = localtime(&buf.st_mtime);
		strftime(datestring, sizeof(datestring),nl_langinfo(D_T_FMT),tm);

		printf(" %s " , datestring );
	
	//	printf()
	//
	printf("%s \n" ,ds->d_name);
	}
	closedir(dptr);
}
