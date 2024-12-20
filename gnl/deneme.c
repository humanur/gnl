#include "get_next_line_bonus.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd;
	int fd1;

	fd = open("deneme.txt", O_RDONLY);
	fd1 = open("merhaba.txt", O_RDONLY);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd1));
	close(fd);
	close(fd1);
}