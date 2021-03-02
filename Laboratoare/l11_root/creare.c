#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

#define FISNAME "fifo_lab11"
//#define FISNAME "my_fifo"

extern int errno;

//#include "header.h"

int main()
{
	if((mkfifo(FISNAME, 0666))&&(errno!=EEXIST)) /* daca s-a facut FIFO ul
//	if((mkfifo(FISNAME, 0666))&&(errno!=EEXIST)) /* daca s-a facut FIFO ul
	dar ( si = && ) errno e DIFERIT ( ! ! DE ("File exists")*/
	{
		printf("eroare la fifo\n");
		exit(0);
	}

	printf("S-a creat fifo\n");
	return 0;
}
