#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned long long TypeEntier;

TypeEntier factorielle(TypeEntier n){
    TypeEntier prod = 1;
    for(int i=1; i<=n; i++){
        prod*=i;
    }
    return prod;
}

int main(void){
    int n=15;
    TypeEntier factoNombre;
    for (int i=1;i<=n;i++){
        factoNombre = factorielle(i);
        printf("%llu \n",factoNombre);
    }
    
    return EXIT_SUCCESS;
}