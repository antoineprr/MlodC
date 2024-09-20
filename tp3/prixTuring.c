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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DONNEES NECESSAIRES
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct {
	unsigned short annee;
	char *nom;  // \0 at the end MANDATORY
	char *nature;
} Gagnant ;


short getYearFromBuffer(char buffer[]){
	short year;
	sscanf(buffer, "%4hd", &year);
	return year;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FONCTIONS DEMANDEES
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int numberOfWinners(FILE *f){
	int nbr = 1;
	char nextChar;
	fseek(f, 0, 0);
	while(!feof(f)){
		nextChar = getc(f);
		if (nextChar=='\n'){
			nbr++;
		}
	}
	return nbr;
}


Gagnant **readWinners(FILE *f){
	Gagnant **p;
	int n = numberOfWinners(f);
	p = calloc(n, sizeof(Gagnant *));
	fseek(f, 0, 0);
	for (int i=0; i<n; i++){
		Gagnant *w;
		w = malloc(sizeof(*w));
		char buffer[1024];
		fgets(buffer, sizeof(buffer)/sizeof(char),f);
		w->annee = getYearFromBuffer(buffer);
		printf("%d\n",w->annee);
		int cpt = 0;
	}


	return p;
}


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

	int nbr = numberOfWinners(fIn);
	Gagnant **p = readWinners(fIn);

	for (int i=0; i<nbr; i++){
		free(p[i]);
	}
	free(p);


	// char buffer[5];
	// char test ; 
	// int cpt;

	// for (int i=0; i<2; i++){
	// 	fgets(buffer, 5, fIn);
	// 	cpt=0;
	// 	while((test!='\n')&(cpt<150)){
	// 		test = fgetc(fIn);	
	// 		printf("%d : ",cpt);
	// 		printf("%c\n", test);
	// 		cpt++;
	// 	}
	// 	fwrite(&buffer, sizeof(buffer), 1, fOut);
	// }

	fclose(fIn);
	fclose(fOut);

	return EXIT_SUCCESS;
}
