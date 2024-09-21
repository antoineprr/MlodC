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

	// remplissage du nom
	short tailleNom = getTailleNomFromBuffer(buffer);
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
    char currentYear[5];  
    sprintf(currentYear, "%d", p->annee);  
    fwrite(currentYear, sizeof(char), 4, f); 
}


short tailleOfNom(Gagnant *p){
	short cpt = 0;
	while(p->nom[cpt]!='\0'){
		cpt++;
	}
	return cpt;
}

short tailleOfNature(Gagnant *p){
	short cpt = 0;
	while(p->nature[cpt]!='\0'){
		cpt++;
	}
	return cpt;
}


void printNom(Gagnant *p, FILE *f){
	short nameHeight = tailleOfNom(p);
	char buffer[nameHeight];
	for (int j=0; j<nameHeight; j++){
		buffer[j]=p->nom[j];
	}
	fwrite(buffer, nameHeight*sizeof(char), 1, f);
}

void printNature(Gagnant *p, FILE *f){
	short topicHeight = tailleOfNature(p);
	char buffer[topicHeight];
	for (int j=0; j<topicHeight; j++){
		buffer[j]=p->nature[j];
	}
	fwrite(buffer, topicHeight*sizeof(char), 1, f);
}

void printWinner(Gagnant *p, FILE *f){
	printAnnee(p, f);
	putc(';', f);

	printNom(p, f);
	putc(';', f);

	printNature(p, f);
	putc('\n', f);
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
	return nbr-1;
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

void printWinners(Gagnant **w, FILE *f, int linesNbr){
	for (int i=0; i<linesNbr; i++){
		printWinner(w[i],f);
	}
	return w;
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
	printWinners(w, fOut, nbr);
	

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
