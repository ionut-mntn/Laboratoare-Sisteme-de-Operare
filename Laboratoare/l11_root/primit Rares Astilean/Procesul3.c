#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
	char text[500];  
	char* myfifo = "myfifo";
	int fd_text3;  // pipe prin care voi citi textul scris in FIFO
	
	// Deschidem myfifo
	if ((fd_text3 = open(myfifo, O_RDONLY)) < 0) {
		printf("error while opening pipe");
		exit(1);
	}
	
	// Citim informatiile scrie in myfifo
	int result = read(fd_text3, text, 500);
	if (result < 0)
		printf("ERROR WHILE READING FROM THE FILE\n");
	printf("\nAu fost cititi %d bytes din file\n", result);
	printf("\nTextul citit din named pipe:\n%s\n", text);
	
	// Scriem intr-un fisier pentru a il putea prelucra cu ajutorul lui grep
	FILE *fp_replace_text;
	fp_replace_text = fopen("replace_text.txt", "w");
	fprintf(fp_replace_text, "%s", text);
	fclose(fp_replace_text);

	// Scriptul shell contine si cat "numefisier" care afiseaza rezultatul final
	printf("Textul final este:\n");
	system("chmod 777 output.sh");  // Adaugam drepturi de executare asupra scriptului
	system("./output.sh replace_text.txt");  // Apelam fopen si ruleaza scripul shell cu grep

	// Distrugem legaturile cu FIFO(stergem FIFO)
	unlink(myfifo);
	return 0;
}
