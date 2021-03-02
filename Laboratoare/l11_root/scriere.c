#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
//#include "header.h"

#define NMAX 105
#define FISNAME "fifo_lab11"
//#define FISNAME "my_fifo"

#include <string.h> // pentru snprintf ?? cred///

int main(int argc, const char * argv[]){
  int fd, n;
  char s[NMAX];

//  fd=open(FISNAME, O_WRONLY); // este autoblocant. asteapta pana cand un alt proces il deschide cu O_RDONLY
                              // putem pune O_RDWR pentru a evita acest lucru
//////

  FILE * aux_pipe;
  char cmd[NMAX];
//  snprintf(cmd, sizeof(cmd), "getent passwd %s | sed 's/,\/\/g | cut -d: -f1,6", argv[1]);
    snprintf(cmd, sizeof(cmd), "getent passwd %s | cut -d: -f1,6", argv[1]);
  aux_pipe = popen(cmd, "r"); // rulez comanda `cmd` intr-un subproces si deschid o cale de comunicare 
//intre procesul parinte si acest subproces; parintele va citi din sub-proces

  fgets(s, NMAX, aux_pipe); // citesc din pipe si retin output ul comenzii `cmd` in variabila `s`

/////

//  fd = open(FISNAME, O_RDWR | O_NONBLOCK);
  fd = open(FISNAME, O_RDWR);
//  fd = open(FISNAME, O_RDONLY);
  if( fd < 0){
    printf("eroare la deschidere fifo\n");
    exit(1);
  }

//  strcpy(s, "scriem in fifo");
  n=strlen(s);
  printf("Se scrie in fifo %d octeti, reprezentand string ul:\n%s\n", n, s);

  if(write(fd,s,n) != n) // daca nu s-au putut scrie toate cele n caractere (n bytes) (functia 
//write returneaza numarul de bytes cititi... / scrisi )
  {
    printf("eroare la scriere in fifo\n");
    exit(1);
  }
//  printf("S-a scris in fifo %d octeti, reprezentand string ul:\n%s\n", n, s);
  close(fd);
}
