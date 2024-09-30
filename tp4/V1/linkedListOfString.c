// gcc -W -Wall -std=c99 linkedList.c linkedListOfString.c -o linkedListOfString
// gcc -W -Wall -Wno-unused-parameter -std=c99 linkedList.c linkedListOfString.c -o linkedListOfString

#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool equalsElement(Element e1, Element e2){
    return strcmp((char*)e1, (char*)e2)==0;
}

void afficheElement(Element e){
    printf("%s", (char*)e);
}

void detruireElement(Element e){
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

    char testStr1[4] = "aaa";
	p = cherche_i(testStr1,l);
	printf("cherche_i(aaa) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

    char testStr2[6] = "Hello";
	p = cherche_r(testStr2,l);
	if(estVide(p))
		printf("cherche_i(Hello) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(Hello) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}
    return 0;
	detruire_r(l);

	return EXIT_SUCCESS;
}