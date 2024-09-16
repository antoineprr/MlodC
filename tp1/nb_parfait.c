#include <stdio.h>
//a corriger

void main(void) {
    int n;
    printf("Entrer un nombre : ")
    scanf("%d", &n);
    int sum;
    for(int i=2; i<=n; i++){
        sum = 0;
        for(int j=2;j<i;j++){
            if(i%j==0){
                sum+=j;
            }
        }
        if (i==sum){
            printf("%d est un nombre parfait\n", i);
        }
    }
}
