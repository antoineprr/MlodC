// gcc -W -Wall linkedListOfMusic.c mySpitofy.c -o mySpitofy
// gcc -W -Wall -Wno-unused-parameter linkedListOfMusic.c mySpitofy.c -o mySpitofy

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListOfMusic.h"

bool equalsElement(Element e1, Element e2){
    return (strcmp(e1->name, e2->name)==0 
        && strcmp(e1->artist, e2->artist)==0 
        && strcmp(e1->album, e2->album)==0 
        && strcmp(e1->genre, e2->genre)==0
        && e1->disc_number == e2->disc_number
        && e1->track_number == e2->track_number
        && e1->year == e2->year);
}

Element creerMusique(char* name, char* artist, char* album, char* genre, int disc_number, int track_number, int year){
    Element e;
    e = malloc(sizeof(Music));
    e->name=name;
    e->artist=artist;
    e->album=album;
    e->genre=genre;
    e->disc_number=disc_number;
    e->track_number=track_number;
    e->year=year;
    return e;
}

void afficheElement(Element e){
    printf("%s,%s,%s,%s,%i,%i,%i\n",
        e->name,e->artist,e->album,
        e->genre,e->disc_number,e->track_number,
        e->year);
}

void detruireElement(Element e){
    free(e);
}

Element parseurMusic(char* line){

}

int main(void){
	Liste l, p;
     
    FILE* file = fopen("music.csv", "r");

    char line[1024];
    fgets(line, sizeof(line), file); //premiere ligne

    
    fgets(line, sizeof(line), file);
    printf("%s\n", line);
    //Element musicTestParseur = parseurMusic(line);
    
	// l = NULL;
	// printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");

    // Element musicTest = creerMusique("Them Bones","Alice In Chains","Dirt","Alternative",1,1,1992);
    // Element musicTest2 = creerMusique("Dam That River","Alice In Chains","Dirt","Alternative",1,2,1992);

    // l=creer(musicTest2);
    // l=ajoutTete(musicTest, l);
    // afficheListe_r(l);

    // detruire_r(l);
    return 0;
}