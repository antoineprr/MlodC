#include <stdio.h>

void echangeContenu(int *p1, int * p2){
    int c = *p1;
    *p1 = *p2;
    *p2 = c;
}

int main(void){
    int a = 10;
    int b = 20;
    echangeContenu(&a, &b);
    printf("a vaut : %i\nb vaut : %i\n", a, b);
    return 0;
}