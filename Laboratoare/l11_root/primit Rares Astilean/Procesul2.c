#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
	char text[500];  // Textul pe care il vom transmite prin FIFO de la procesul 2 procesului 3 pentru a il prelucra
	char* myfifo = "myfifo";
	int fd_text2;  // pipe prin care voi citi textul scris in FIFO
	
	// Scoatem informatiile primite de primul proces prin FIFO
	if ((fd_text2 = open(myfifo, O_RDONLY)) < 0) {
		printf("error while opening pipe");
		exit(1);
	}

	// Citim si verificam daca s-a citit corect din fisier
    	int result = read(fd_text2, text, 500);
	if (result < 0)
		printf("ERROR WHILE READING FROM THE FILE\n");
	close(fd_text2);
	printf("\nAu fost cititi %d bytes din file\n", result);
	printf("\nTextul citit din FIFO:\n%s\n", text);
	
	// Scriem informatiile intr-un fisier pentru a il putea prelucra cu ajutorul lui sed
	FILE *fp_replace_text;
	fp_replace_text = fopen("replace_text.txt", "w");
	fprintf(fp_replace_text, "%s", text);
	fclose(fp_replace_text);
	
	system("chmod 777 replace.sh");  // Adaugam drepturi de executare asupra scriptului
	system("./replace.sh replace_text.txt");  // Apelam fopen si ruleaza scripul shell cu sed 
	
	// Citim din fisierul prelucrat si transmitem datele mai departe procesului 3 prin FIFO
	fp_replace_text = fopen("replace_text.txt", "r");
	fread(text, 500, 1, fp_replace_text);
	fclose(fp_replace_text);

	printf("\nTextul citit din replace_text.txt dupa prima modificare(replace aeiou cu 12345):\n%s\n", text);	
	if ((fd_text2 = open(myfifo, O_WRONLY)) < 0) {
		printf("error while opening pipe");
		exit(1);
	}
	int result2 = write(fd_text2, text, strlen(text) + 1);
	printf("\nWrote %d bytes to myfifo\n", result2);
	close(fd_text2);
	
	return 0;
}

