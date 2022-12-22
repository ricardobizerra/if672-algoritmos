#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
#define TAM 5

/*

14 - Create a function that receives 2 parameters: an array and a value with the same type as the array's type.
This function should fill the array's elements with this value.

15 - Create a function that receives an array as a parameter and print it.  

For the 2 examples, do not use indexes, only pointer arithmetics

*/

void modifica_array(int *arr, int valor){
    for(int i = 0; i < TAM; i++){
        // iterating through each element and changing its element
        *(arr + i) = valor;
    }
}

void print_array(int *arr){
    // prints each array element
    cout << endl << "[";
    for(int i = 0; i < TAM; i++){
        if (i != TAM - 1){
            cout << *(arr + i) << ",";
        } else {
            cout << *(arr + i);
        }
    }
    cout << "]" << endl << endl;
}

int main(){
    int *arr; // appoints to new array of inters
    int valor;

    cin >> valor;

    arr = new int[TAM]; // memory allocation

    modifica_array(arr, valor); // fill values
    print_array(arr); // printing elements

    return 0;
}