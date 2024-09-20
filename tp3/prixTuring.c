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

short getTailleNomFromBuffer(char buffer[]){
	int taille = 5;
	while(buffer[taille]!=';'){
		taille++;
	}
	return taille-5;
}

short getTailleNatureFromBuffer(char buffer[], short tailleNom){
	int taille = 6+tailleNom;
	while(buffer[taille]!='\n'&& buffer[taille] != '\0'){
		taille++;
	}
	return taille-(6+tailleNom);
}

void printNomOuNature(const char *nom) {
    printf("%s\n", nom);
}


Gagnant *readWinner(FILE *f){
	Gagnant *p = NULL;
	p = malloc(sizeof(*p));
	char buffer[1024];
	fgets(buffer, sizeof(buffer),f);

	// remplissage de l'année
	p->annee = getYearFromBuffer(buffer);
	short tailleNom = getTailleNomFromBuffer(buffer);

	// remplissage du nom
	p->nom = calloc(tailleNom+1, sizeof(char));
	for (int j=0; j<tailleNom; j++){
		p->nom[j]=buffer[5+j];
	}
	p->nom[tailleNom]='\0';

	// remplissage de la nature
	short tailleNature = getTailleNatureFromBuffer(buffer, tailleNom);
	p->nature = calloc(tailleNature+1, sizeof(char));
	for (int j=0; j<tailleNature; j++){
		p->nature[j]=buffer[6+tailleNom+j];
	}
	p->nature[tailleNature]='\0';

	return p;
}

void printAnnee(Gagnant *p, FILE *f){
	char currentYear[4];
	sprintf(currentYear, "%d", p->annee);
	fwrite(currentYear, 4*sizeof(char), 1, f);
}

short tailleOfNom(Gagnant *p){
	short cpt = 0;
	while(p->nom[cpt]!='\0'){
		cpt++;
	}
	return cpt;
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
	Gagnant **w;
	int nbr = numberOfWinners(f);
	fseek(f, 0, 0);
	w = calloc(nbr, sizeof(**w));
	for (int i=0; i<nbr; i++){
		w[i] = readWinner(f);
	}
	return w;
}

void printWinner(Gagnant *p, FILE *f){
	printAnnee(p, f);
	//short tNom = tailleOfNom(p);
	//fwrite(p->nom, tNom, 1, f);
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
	Gagnant **w = readWinners(fIn);
	printWinner(w[5], fOut);

	for (int i=0; i<nbr; i++){
		free(w[i]->nom); 
		free(w[i]->nature);
		free(w[i]);
	}
	free(w);
	
	fclose(fIn);
	fclose(fOut);

	return EXIT_SUCCESS;
}
