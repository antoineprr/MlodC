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

void triIndice(int *indices, Gagnant **w, int nbr){
	int i,j,c;
	for(j=1;j<nbr;j++){ 
		for(i=0;i<nbr-1;i++){
			if ( w[indices[i]]->annee > w[indices[i+1]]->annee ) {
					c = indices[i];
					indices[i] = indices[i+1];
					indices[i+1] = c;
			}  
		}
	} 
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
}

int getIndiceFromAnnee(int uneAnnee, Gagnant **w){
	int nbr = numberOfWinners;
	for (int i=0; i<nbr; i++){
		if (w[i]->annee==uneAnnee){
			return i;
		}
	}
	return -1;
}

void infosAnnee(int uneAnnee, Gagnant **w){
	int indice = getIndiceFromAnnee(uneAnnee, w);
	if (indice!=-1){
		printf("L'année %d, le(s) gagnant(s) ont été : %s\n", uneAnnee, w[indice]->nom);
		printf("Nature des travaux : %s\n", w[indice]->nature);
	}
	else{
		printf("Année non référencée.");
	}
}

void sortTuringWinnersByYear(Gagnant **w, FILE *f, int linesNbr){
	int indices[linesNbr];
	for (int j=0; j<linesNbr; j++){
		indices[j]=j;
	}
	triIndice(indices, w, linesNbr);
	for (int i=0; i<linesNbr; i++){
		printWinner(w[indices[i]],f);
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MAIN
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char** argv)
{	
    char *filename = (char *)malloc(256 * sizeof(char)); 
    char *outputFilename = (char *)malloc(256 * sizeof(char)); 

    strcpy(filename, "turingWinners.csv");
    strcpy(outputFilename, "out.csv");
	
	for (int i=0; i<argc-1; i++){
		if (strcmp(argv[i], "-o") == 0 && argc>i){
			outputFilename = realloc(outputFilename, (strlen(argv[i+1]) + 1) * sizeof(char));
			strcpy(outputFilename, argv[i+1]);
			if(argc>i+1){
				rename("turingWinners.csv", argv[i+2]);
				filename = realloc(filename, (strlen(argv[i+2]) + 1) * sizeof(char));
				strcpy(filename, argv[i+2]);
			}
		}
		if (strcmp(argv[i], "-info") == 0 && argc>i+1) {
			filename = realloc(filename, (strlen(argv[i+2]) + 1) * sizeof(char));
			strcpy(filename, argv[i+2]);
		}
	}

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
	
	if(argc>2){
		if (strcmp(argv[1], "--info") == 0) {
			int uneAnnee = atoi(argv[2]);
			infosAnnee(uneAnnee, w);
		}
		else if (strcmp(argv[1], "--sort") == 0) {
			sortTuringWinnersByYear(w, fOut, nbr);
		}
		else {
			printWinners(w, fOut, nbr);
		}
	}

	for (int i=0; i<nbr; i++){
		free(w[i]->nom); 
		free(w[i]->nature);
		free(w[i]);
	}
	free(w);
	
	fclose(fIn);
	fclose(fOut);

    free(filename);
    free(outputFilename);

	return EXIT_SUCCESS;
}


