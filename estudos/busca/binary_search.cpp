#include <iostream>
using namespace std;

struct node {
    int element;
    int client;
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

int binary_search(array *array, int valor_procurado) {
    int n = tamanho_array(array);

    int l = 0;
    int r = n - 1;

    do {
        int m = (l + r) / 2;

        if (valor_procurado == elemento_vetor(array, m)->element) return m;

        else if (valor_procurado < elemento_vetor(array, m)->element) r = m - 1;

        else l = m + 1;

    } while (l <= r);

    return -1;
}

int main() {
    array *array_exemplo = new array();
    array_exemplo->head = new node(1);
    array_exemplo->head->next = new node(2);
    array_exemplo->head->next->next = new node(3);
    array_exemplo->head->next->next->next = new node(4);
    array_exemplo->head->next->next->next->next = new node(5);
    array_exemplo->head->next->next->next->next->next = new node(6);
    array_exemplo->head->next->next->next->next->next->next = new node(7);
    array_exemplo->head->next->next->next->next->next->next->next = new node(8);
    array_exemplo->tail = array_exemplo->head->next->next->next->next->next->next->next;

    cout << binary_search(array_exemplo, 7);

    return 0;
}