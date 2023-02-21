#include <iostream>
using namespace std;

struct node {
    int element;
    node *next;
    node(int element): element(element), next(NULL) {}
};

struct array {
    node *head;
    node *tail;

    array(): head(NULL), tail(NULL) {}

};

int tamanho_array(array *arr) {
    int retorno = 0;
    node *cur = arr->head;
    if (cur == NULL) {
        return retorno;
    } else {
        while (cur != NULL) {
            retorno++;
            cur = cur->next;
        }
        return retorno;
    }
}

node* elemento_vetor(array *vetor, int posicao) {
    node *cur = vetor->head;
    int posicao_busca = 0;

    while (cur != NULL && posicao_busca != posicao) {
        cur = cur->next;
        posicao_busca++;
    }

    return cur;
}

void permuta(array *vetor, int a, int b) {

    node *cur_a = elemento_vetor(vetor, a);
    node *cur_b = elemento_vetor(vetor, b);

    if (cur_a != NULL && cur_b != NULL) {
        int temporario = cur_a->element;
        cur_a->element = cur_b->element;
        cur_b->element = temporario;
    }
}

int partition(array *vetor, int l, int r) {
    int j = (l + r) / 2;
    permuta(vetor, j, l);

    int i = l;
    j = r;

    while (i < j) {
        while (i < r && elemento_vetor(vetor, i)->element <= elemento_vetor(vetor, l)->element) i++;
        while (j >= l && elemento_vetor(vetor, j)->element > elemento_vetor(vetor, l)->element) j--;

        if (i < j) permuta(vetor, i, j);
    }

    permuta(vetor, l, j);

    return j;
}


void quicksort_auxiliar(array *vetor, int l, int r) {
    if (l >= r) return;

    int p;
    p = partition(vetor, l, r);

    quicksort_auxiliar(vetor, l, p-1);
    quicksort_auxiliar(vetor, p+1, r);
}

void quicksort(array *vetor_para_ordenar) {
    quicksort_auxiliar(vetor_para_ordenar, 0, tamanho_array(vetor_para_ordenar)-1);
}

void printa_array(array *arr){
    node *cur = arr->head;
    while (cur != NULL) {
        cout << cur->element;
        if (cur != arr->tail) {
            cout << " ";
        } else {
            cout << endl;
        }
        cur = cur->next;
    }
}


int main() {
    array *array_desordenado = new array();
    array_desordenado->head = new node(5);
    array_desordenado->head->next = new node(3);
    array_desordenado->head->next->next = new node(8);
    array_desordenado->head->next->next->next = new node(1);
    array_desordenado->head->next->next->next->next = new node(6);
    array_desordenado->head->next->next->next->next->next = new node(2);
    array_desordenado->head->next->next->next->next->next->next = new node(7);
    array_desordenado->head->next->next->next->next->next->next->next = new node(4);
    array_desordenado->tail = array_desordenado->head->next->next->next->next->next->next->next;

    printa_array(array_desordenado);

    quicksort(array_desordenado);

    printa_array(array_desordenado);

    return 0;
}