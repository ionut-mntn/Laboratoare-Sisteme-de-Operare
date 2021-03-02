#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {
	char text[500];  // Textul pe care il vom transmite prin FIFO de la procesul 1 procesului 2 pentru a il prelucra
	char aux[100];  // Reprezinta cate un rand, randul va fi adaugat la variabila text
	char* myfifo = "myfifo";  // Path-ul unde va fi creat FIFO (in acest caz in fisierul de unde se ruleaza programul)
	int fd_text;  // pipe prin care voi prelucra FIFO

	// Citirea sirului de caractere
	printf("\nIntroduceti sirul de caractere (pentru a opri citirea se va introduce un rand nou care va contine doar 0):\n");
	// Se citeste cate o propozitie pana la \n, dupa care adaug propozitia la textul final format din cel putin o propozitie
	while(scanf("%[^\n]%*c", aux) == 1) {
		if(strcmp(aux, "0") == 0)  // Daca s-a introdus 0 se sfarseste citirea de la tastatura
			break;
		strcat(aux, "\n");
		strcat(text, aux);
    	}
	strcat(text, "\0");
	
	// Creeam verificam daca s-a creat corect FIFO
	int returnValue = mkfifo(myfifo, 0666);
    	if(returnValue < 0) {
		printf("mkfifo() failed\nerrno = %d\n", errno);
		if(errno == EEXIST) 
			printf("That file already exists.\n");
	}
	printf("\nmyfifo created");
	
	// Deschidem pipe-ul pentru a putea prelucra FIFO file-ul
	if((fd_text = open(myfifo, O_WRONLY)) < 0) {
		printf("error while opening pipef for FIFO");
		exit(0);
	} 
	printf("fd_text (the file descript for the FIFO) opened\n");
	
	// Scriem si testam daca s-a scris corect 
	int result = write(fd_text, text, strlen(text) + 1);
	if(result == 0) {
		printf("Writing went wrong");
	}
	printf("\nwrote %d to myfifo\n", result);
    	close(fd_text);
	return 0;
}
