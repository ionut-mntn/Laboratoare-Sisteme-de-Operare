#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // pentru `unlink`
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <fcntl.h> // "file control"

#define FISNAME "fifo_lab11"
//#define FISNAME "my_fifo"

int main(){
  if(unlink(FISNAME) < 0){
    printf("eroare la stergere fifo\n");
    exit(0);
  }
  printf("S-a sters fifo\n");
}
