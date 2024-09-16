#include <stdio.h>
#include <stdlib.h>

enum MoisE {
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
typedef enum MoisE Mois;


struct DateS {
    unsigned int jour;
    Mois mois;
    unsigned int annee;
};
typedef struct DateS Date;

//autre methode :
// typedef struct {
//     unsigned int jour;
//     Mois mois;
//     unsigned int annee;
// } Date;

void initialiseDate(Date *d){
    unsigned int j, m, a;
    printf("jour : ");
    scanf("%u", &j);
    d->jour = j;
    printf("mois : ");
    scanf("%u", &m);
    d->mois = m;
    printf("annee : ");
    scanf("%u", &a);
    d->annee = a;
}

void afficheDate(Date *d){
    if (d->jour<10)
        printf("0%u/",d->jour);
    else
        printf("%u/",d->jour);
    if (d->jour<10)
        printf("0%u/",d->mois);
    else
        printf("%u/",d->mois);

    printf("%u\n",d->annee);
}

Date creerDateParCopie(void){
    Date d;
    unsigned int j, m, a;
    printf("jour : ");
    scanf("%u", &j);
    d.jour = j;
    printf("mois : ");
    scanf("%u", &m);
    d.mois = m;
    printf("annee : ");
    scanf("%u", &a);
    d.annee = a;
    return d;
}

Date * newDate(){
    Date *date;
    date = (Date *) malloc(sizeof(Date));
    unsigned int j, m, a;
    printf("jour : ");
    scanf("%u", &j);
    date->jour = j;
    printf("mois : ");
    scanf("%u", &m);
    date->mois = m;
    printf("annee : ");
    scanf("%u", &a);
    date->annee = a;
    return date;
}

int estBissextile(unsigned int annee){
    if(annee % 4 == 0)
    {
        if( annee % 100 == 0)
        {
            if ( annee % 400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    return 0;
}

unsigned int nbreJours(Mois mois, unsigned int annee){
    int petit[4] = {4,6,9,11};
    if(mois==fervrier){
        if (estBissextile(annee))
            return 29;
        return 28;
    }
    for(int i=0;i<sizeof(petit)/sizeof(int);i++){
        if(petit[i]==mois)
            return 30;
    }
    return 31;
}

int dateValide(Date uneDate){
    if (uneDate.jour>nbreJours(uneDate.mois, uneDate.annee)||(uneDate.mois>12))
        return 0;
    return 1;
}

unsigned int jourDansAnnee(Date uneDate){
    unsigned int sum = 0;
    if (!dateValide(uneDate)){
        printf("Date invalide\n");
        return 0;
    }
    for (int i=1; i<uneDate.mois; i++){
        sum+=nbreJours(i,uneDate.annee);
    }
    return sum+uneDate.jour;

}

int main(void){

    // Date d;
    // printf("V1 :\n");
    // initialiseDate(&d);
    // afficheDate(&d);

    // Date d2;
    // printf("V2 :\n");
    // d2 = creerDateParCopie();
    // afficheDate(&d2);

    Date *date;
    printf("V3 :\n");
    date = newDate();
    // if (dateValide(date->jour,date->mois,date->annee))
    //     afficheDate(date);
    // else
    //     printf("Date invalide");
    

    printf("%d", jourDansAnnee(*date));
    free(date);
}