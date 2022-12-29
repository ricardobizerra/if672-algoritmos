#include <iostream>
using namespace std;

struct node_fila {
    string carta_fila;
    node_fila *next;
    node_fila(string carta_fila): carta_fila(carta_fila), next(NULL) {}
};

struct fila {
    node_fila *head;
    node_fila *tail;

    fila(): head(NULL), tail(NULL) {}

};

void enqueue(fila *arr, string carta_fila){
    node_fila *new_node = new node_fila(carta_fila);

    if (arr->tail == NULL) {
        arr->head = new_node;
        arr->tail = new_node;
    } else {
        arr->tail->next = new_node;
        arr->tail = new_node;
    }
}

void printa_fila(fila *arr){
    cout << "[";
    node_fila *cur = arr->head;
    if (cur == NULL) {
        cout << "";
    } else {
        while (cur != NULL){
            if(cur != arr->tail) cout << cur->carta_fila << ",";
            else cout << cur->carta_fila;
            cur = cur->next;
        }
    }
    cout << "]" << endl;
}

int main()
{
    int number;
    cin >> number;

    fila *array_ponteiros[number];

    for (int i=0; i < number; i++) {
        array_ponteiros[i] = NULL;
    }

    for (int i=0; i < number; i++) {
        array_ponteiros[i] = new fila();
    }

    string cmd, carta;
    cin >> cmd;

    bool programa_encerrado = false;

    while (programa_encerrado == false) {

        if (cmd == "END") {
            programa_encerrado = true;

        } else if (cmd == "VAL") {

            for (int i=0; i < number; i++) {
                cin >> carta;
                cout << carta << endl;
            }

            cin >> cmd;

        } else if (cmd == "DEA") {

            for (int i=0; i < number; i++) {
                cin >> carta;
                cout << carta << endl;
                enqueue(array_ponteiros[i], carta);
            }

            cin >> cmd;

        }
    }

    for (int i=0; i < number; i++) {
        cout << sizeof(*array_ponteiros[i]) / 8 << endl;
        printa_fila(array_ponteiros[i]);
    }

    return 0;
}

