#include <iostream>
using namespace std;

struct node_struct {
    string carta_fila;
    node_struct *next;
    node_struct(string carta_fila): carta_fila(carta_fila), next(NULL) {}
};

struct fila {
    node_struct *head;
    node_struct *tail;

    fila(): head(NULL), tail(NULL) {} // fila vazia, no início

};

void enqueue(fila *arr, string carta_fila){
    node_struct *new_node = new node_struct(carta_fila);

    if (arr->tail == NULL) {
        arr->head = new_node;
        arr->tail = new_node;
    } else {
        arr->tail->next = new_node;
        arr->tail = new_node;
    }
}

string dequeue(fila *arr){
    string v = arr->head->carta_fila;

    node_struct *p = arr->head;
    arr->head = p->next;
    free(p);
    
    return v;
}

void printa_fila(fila *arr){
    node_struct *cur = arr->head;
    if (cur == NULL) {
        cout << "";
    } else {
        while (cur != NULL){
            if(cur != arr->tail) cout << cur->carta_fila << " ";
            else cout << cur->carta_fila << endl;
            cur = cur->next;
        }
    }
}

struct pilha {
    node_struct *top;
    node_struct *aux_bottom;

    pilha(): top(NULL), aux_bottom(NULL) {}
};

void stack_push(pilha *arr, string carta_fila) {
    node_struct *new_node = new node_struct(carta_fila);

    if (arr->top == NULL){
        arr->top = new_node;
        arr->top->next = new_node->next;
        arr->aux_bottom = arr->top;
    } else {
        new_node->next = arr->top;
        arr->top = new_node;
        arr->top->next = new_node->next;
    }
    
}

void printa_pilha(pilha *arr){
    node_struct *cur = arr->top;
    if (cur == NULL) {
        cout << "";
    } else {
        while (cur != NULL){
            if(cur != arr->aux_bottom) cout << cur->carta_fila << " ";
            else cout << cur->carta_fila << endl;
            cur = cur->next;
        }
    }
}

int vencedor_rodada(pilha *arr, int num_jogadores){
    node_struct *cur = arr->top;
    int num_jogador = num_jogadores - 1;
    
    string naipe_carta_vencedor = "";
    string num_carta_vencedor = "";
    int num_vencedor = 0;
    bool empate = false;
    
    while (cur != NULL) {
        string carta_jogador = cur->carta_fila;
        
        string naipe_carta = carta_jogador.substr(0,1);
        string num_carta = carta_jogador.substr(1,2);
        
        if (naipe_carta > naipe_carta_vencedor) {
            
            empate = false;
            naipe_carta_vencedor = naipe_carta;
            num_carta_vencedor = num_carta;
            num_vencedor = num_jogador;
            
        } else if (naipe_carta == naipe_carta_vencedor) {
            
            if (num_carta > num_carta_vencedor) {
                
                empate = false;
                naipe_carta_vencedor = naipe_carta;
                num_carta_vencedor = num_carta;
                num_vencedor = num_jogador;
                
            } else if (num_carta == num_carta_vencedor) {
                
                empate = true;
                
            }
            
        }
        
        cur = cur->next;
        num_jogador--;
    }
    
    if (empate == false) return num_vencedor;
    else return -1;
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

    string cmd;
    cin >> cmd;

    bool programa_encerrado = false;
    
    int num_rodadas = -1;
    
    pilha *pilha_rodada;
    pilha_rodada = NULL;

    while (programa_encerrado == false) {

        if (cmd == "END") {
            programa_encerrado = true;

        } else if (cmd == "DEA") {

            for (int i=0; i < number; i++) {
                string carta;
                cin >> carta;
                enqueue(array_ponteiros[i], carta);
            }

            cin >> cmd;

        } else if (cmd == "RND") {
          
            num_rodadas++;
            pilha_rodada = new pilha();
            
            for (int i=0; i < number; i++) {
                string carta_para_empilhar = dequeue(array_ponteiros[i]);
                stack_push(pilha_rodada, carta_para_empilhar);
            }
            
            cout << num_rodadas << " " << vencedor_rodada(pilha_rodada, number) << endl;
            
            cin >> cmd;
            
        } else if (cmd == "PRT") {
            if (pilha_rodada != NULL) printa_pilha(pilha_rodada);

            cin >> cmd;
        }
    }

    return 0;
}
