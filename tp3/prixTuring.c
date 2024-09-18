/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring

 Tests
 diff out.csv turingWinners.csv

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

typedef struct {
	int annee;
	char nom[64];
	char nature[252];
} Gagnant ;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char** argv)
{
	char filename[] = "turingWinners.csv";
	char outputFilename[] = "out.csv";

    // TODO

	FILE* fIn;
	FILE* fOut;
	
	fIn = fopen(filename,"r");

	if(fIn==NULL) {
		printf ("Code de l'erreur : %d\n", errno);

		if (errno == ENOENT)
			printf ("Le fichier n'existe pas !\n");

		else
			printf ("Erreur inconnue\n");
		
		return EXIT_FAILURE;
	}

	fOut = fopen(outputFilename, "w");

	char buffer[5];
	char test ; 
	int cpt;

	for (int i=0; i<4; i++){
		fgets(buffer, 5, fIn);
		test = fgetc(fIn);
		cpt=0;
		while((test!="\n")&(cpt<100)){
			test = fgetc(fIn);
			printf("%d\n",cpt);
			printf("%c\n", test);
			cpt++;
		}
		fwrite(&buffer, sizeof(buffer), 1, fOut);
	}

	fclose(fIn);
	fclose(fOut);

	return EXIT_SUCCESS;
}
