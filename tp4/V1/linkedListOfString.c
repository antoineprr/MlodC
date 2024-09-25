// gcc -W -Wall -std=c99 linkedList.c linkedListOfString.c -o linkedListOfString
// gcc -W -Wall -Wno-unused-parameter -std=c99 linkedList.c linkedListOfString.c -o linkedListOfString

#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
    Liste l;
	l = malloc(sizeof(Cellule));
	l->val=calloc(sizeof((char*)v), sizeof(char));
    l->val = v;
	l->suiv=NULL;
	return l;
}

bool equalsElement(Element e1, Element e2){
    return strcmp((char*)e1, (char*)e2);
}

void afficheElement(Element e){
    printf("%s", (char*)e);
}

void detruireElement(Element e){
    free(e);
}


int main(void){
	Liste l, p;

	l = NULL;
	printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");

	l = ajoutTete("abc",l);
	l = ajoutTete("def",l);
	l = ajoutTete("ghu",l);

	afficheListe_i(l);
	ajoutFin_i("Hello",l);
	afficheListe_i(l);

	ajoutFin_r(" ! ",l);
	afficheListe_i(l);

	p = cherche_i(" aaa ",l);
	printf("cherche_i(aaa) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

    printf("%s\n",l->val);
    printf("%s\n",l->suiv->val);
    
    printf("%i\n", equalsElement(l->val, l->suiv->val));

	p = cherche_i("abc",l);
	if(estVide(p))
		printf("cherche_i(abc) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(abc) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}
    return 0;
	p = cherche_r(200,l);
	printf("cherche_r(200) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_r(99,l);
	if(estVide(p))
		printf("cherche_r(99) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_r(99) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	printf("retirePremier_i(1)   : ");
	l = retirePremier_i(1,l);
	afficheListe_r(l);

	printf("retirePremier_i(1)   : ");
	l = retirePremier_i(1,l);
	afficheListe_r(l);

	printf("retirePremier_i(100) : ");
	l = retirePremier_i(100,l);
	afficheListe_r(l);

	printf("retirePremier_r(4)   : ");
	l = retirePremier_r(4,l);
	afficheListe_r(l);

	printf("retirePremier_r(4)   : ");
	l = retirePremier_r(4,l);
	afficheListe_r(l);

	printf("retirePremier_r(99)  : ");
	l = retirePremier_r(99,l);
	afficheListe_r(l);

	afficheEnvers_r(l);

	detruire_r(l);

	return EXIT_SUCCESS;
}