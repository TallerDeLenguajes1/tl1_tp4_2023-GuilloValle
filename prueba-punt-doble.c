#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


void cambiarValor(int** puntero);


int main(){

    int* puntero;
    int a = 2;
    puntero = &a;

    cambiarValor(&puntero);

    return 0;
}

void cambiarValor(int** puntero){

    printf("%d\n\n",puntero);
    printf("%d\n\n",*puntero);
    printf("%d\n\n",**puntero);
   
}