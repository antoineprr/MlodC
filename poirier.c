// Antoine Poirier

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


int *repeat(int t1[], int t2[], int n){
    int *ptab;
    int taille = 0;
    for (int i=0; i<n; i++){
        taille+=t1[i];
    }
    ptab = calloc(taille, sizeof(int));
    int cpt = 0;
    for (int j=0; j<n; j++){
        for (int k=0; k<t1[j]; k++){
            ptab[cpt]=t2[j];
            cpt++;
        }
    }
    return ptab;
}


int main(void) {
    int t1[3] = {1,2,4};
    int t2[3] = {10,3,8};
    int n = sizeof(t1)/sizeof(int);

    int taille = 0;
    for (int i=0; i<n; i++){
        taille+=t1[i];
    }

    int *ptab = repeat(t1,t2,n);
    //for (int i=0; i<taille; i++){
    //    printf("%d\n", ptab[i]);
    //}
    free(ptab);
    return 0;
}