#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#define TAM 5

// STRUCTS

struct _no { // similar to Type in ts
    int x;
    char y;
    int z;
};

struct retorno {
    int valor;
    int num;
};

retorno criar() {

    retorno *ponteiro;
    retorno var;

    ponteiro->valor = 10;
    ponteiro->num = 30;
    (*ponteiro).num = 30;
    (*ponteiro).valor = 10;

    var.num = 30;
    var.valor = 10;

    return *ponteiro; // possible way to return 2+ values in one function
}

// * is used to appoint
void modifica_array(int **arr, int valor) {
    for(int i=0; i < TAM; i++){
        *(*(arr) + i * sizeof(int)) = valor; // attributing value to x[i]
    }
}

int main() {
    int *x;
    int valor = 2;
    x = (int *) malloc(TAM * sizeof(int));

    modifica_array(&x, valor);

    for (int i = 0; i < TAM; i++) {
        std::cout << x[i] << std::endl;
    }

    return 0;
}

// [ ./a < in.txt > saida.txt ] <== way to indicate input and output
// an extension should be used to compare this files