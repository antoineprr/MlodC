#include <stdio.h>

enum Mois {
    janvier=1,
    fervrier,
    mars,
    avril,
    mai,
    juin,
    juillet,
    aout,
    septembre,
    octobre,
    novembre,
    decembre,
};


struct Date {
    int jour,
    enum Mois mois;
    int annee;
};

void initialiseDate(Date *d){
    printf("jour : ");
    scanf("%d", &j);
    d->jour = j;
    printf("mois : ");
    scanf("%d", &m);
    d->mois = m;
    printf("annee : ");
    scanf("%d", &a);
    d->annee = a;
}

void afficheDate(Date *d){
    print
}


int main(void){
    Date d;
    initialiseDate(&d);
    afficheDate(&d);
}