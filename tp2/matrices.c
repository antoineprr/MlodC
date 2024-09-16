#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 5


void matrix_mult(int64_t matriceResultat[][SIZE],int64_t matrice1[][SIZE],int64_t matrice2[][SIZE]){
    int64_t somme;
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            somme = 0;
            for (int k=0;k<SIZE;k++){
                somme+=matrice1[i][k]*matrice2[k][j];
            }
            matriceResultat[i][j]=somme;
        }
    }
}

void matrix_print(int64_t matriceResultat[][SIZE]){
    for (int i=0;i<SIZE;i++){
        for (int j=0; j<SIZE;j++){
            printf("%li  ", matriceResultat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    //matrices en ligne * colonne
    int64_t matrice1[][SIZE]={{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matrice2[][SIZE]={{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];
    matrix_mult(matriceResultat,matrice1,matrice2);
    matrix_print(matriceResultat);
    return EXIT_SUCCESS;
}