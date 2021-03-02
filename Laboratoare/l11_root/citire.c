#include <string.h>
#include <unistd.h>
#include <fcntl.h> // file control
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
//#include "header.h"

#define FISNAME "fifo_lab11"
//#define FISNAME "my_fifo"

int main(){
  int fd, n;
  char s[105];

//printf("trece\n");
fd = open(FISNAME, O_RDONLY);
//fd = open(FISNAME, O_RDWR);
//printf("trece\n");

//  if(fd=open(FISNAME, O_RDONLY)){	// read only
//  if(fd=open(FISNAME, O_RDONLY | O_NONBLOCK)){	// read only
//  if(fd=open(FISNAME, O_RDWR)){	// read only
    if(fd < 0)
  {
//	printf("trece\n");
//  if( fd < 0){
    printf("eroare la deschidere fifo\n");
    exit(1);

  }
//printf("trece_2\n");
// if((n=write(fd,s,14)) < 0){
  //if((n=read(fd,s,14)) < 0){
//  if(n=read(s,14,fd) < 0){
//  if((n=fgets(fd,s,14)) < 0){
  n = read(fd, s, 100);
  if(n < 0){
//  {
    printf("eroare la citire din fifo\n");
    exit(1);
  }

//printf("trece_3\n");
  s[n+1]='\0';
  printf("S-a citit din fifo %d octeti, reprezentand string ul urmator:\n%s\n", n, s);
  close(fd);
//printf("trece\n");
	return 0;
}
