#include <dirent.h>
#include <stdio.h>

int main(void)
{
	DIR *dirp;
	struct dirent *dp;
	
	dirp = opendir(".");
	dp = readdir(dirp);
	dp = readdir(dirp);
	dp = readdir(dirp);
	printf("name: %s\n", dp->d_name);
	dp = readdir(dirp);
	printf("name: %s\n", dp->d_name);
	dp = readdir(dirp);
	printf("name: %s\n", dp->d_name);
	dp = readdir(dirp);
	printf("name: %s\n", dp->d_name);
	return (0);
}
