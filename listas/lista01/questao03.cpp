#include <iostream>
using namespace std;

// estrutura que implementa o nó
struct node_struct {
    string carta_fila;
    node_struct *next;
    node_struct(string carta_fila): carta_fila(carta_fila), next(NULL) {}
};

// estrutura da fila
struct fila {
    node_struct *head;
    node_struct *tail;

    fila(): head(NULL), tail(NULL) {} // fila vazia, no início

};

// enfileirar
void enqueue(fila *arr, string carta_fila){
    node_struct *new_node = new node_struct(carta_fila);

    if (arr->head == NULL) {
        // fila vazia
        arr->head = new_node;
        arr->tail = new_node;
    } else {
        arr->tail->next = new_node;
        arr->tail = new_node;
    }
}

// desenfileirar
string dequeue(fila *arr){
    string v = arr->head->carta_fila;

    node_struct *p = arr->head;
    arr->head = p->next;
    free(p);
    
    return v;
}

// printa fila
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

// tamanho da fila
int tamanho_fila(fila *arr) {
    int retorno = 0;
    node_struct *cur = arr->head;
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

// estrutura da pilha
struct pilha {
    node_struct *top;
    node_struct *aux_bottom;

    pilha(): top(NULL), aux_bottom(NULL) {}
};

// empilhar
void stack_push(pilha *arr, string carta_fila) {
    node_struct *new_node = new node_struct(carta_fila);

    if (arr->top == NULL){
        // pilha vazia
        arr->top = new_node;
        arr->top->next = new_node->next;
        arr->aux_bottom = arr->top;
    } else {
        new_node->next = arr->top;
        arr->top = new_node;
        arr->top->next = new_node->next;
    }
    
}

// desempilhar
string stack_pop(pilha *arr) {
    string valor = arr->top->carta_fila;
    
    node_struct *p = arr->top;
    arr->top = p->next;
    free(p);
    
    return valor;
}

// printa pilha
void printa_pilha(pilha *arr){
    node_struct *cur = arr->top;
    if (cur == NULL) {
        cout << "";
    } else {
        while (cur != NULL){
            if(cur != arr->aux_bottom) {
                cout << cur->carta_fila << " ";
            } else {
                cout << cur->carta_fila << endl;
            }
            cur = cur->next;
        }
    }
}


// tamanho da pilha
int tamanho_pilha(pilha *arr) {
    int retorno = 0;
    node_struct *cur = arr->top;
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

// decidir vencedor de uma rodada
int vencedor_rodada(pilha *arr, pilha *pilha_auxiliar, int num_jogadores, fila **arr_fila){
    int jogador_sem_carta = 0;
    bool *cards_dequeued = new bool[num_jogadores];
    
    for (int i=0; i<num_jogadores; i++){
        cards_dequeued[i] = false;
    }
    
    // desenfileira primeira carta de cada jogador e empilha na pilha
    for (int i=0; i < num_jogadores; i++) {
        
        if (tamanho_fila(arr_fila[i]) != 0) {
            cards_dequeued[i] = true;
            string carta_para_empilhar = dequeue(arr_fila[i]);
            stack_push(pilha_auxiliar, carta_para_empilhar);
            if (tamanho_fila(arr_fila[i]) != 0) stack_push(arr, carta_para_empilhar);
        } else {
            cards_dequeued[i] = false;
            jogador_sem_carta++;
        }
        
    }
    
    node_struct *cur = pilha_auxiliar->top;
    int num_jogador = num_jogadores - 1; // id do jogador que está sendo analisado
    
    string naipe_carta_vencedor = "";
    string num_carta_vencedor = "";
    int num_vencedor = 0;
    
    bool empate = false;
    
    for(int i=num_jogador; i>=0; i--) {
        
        if(cards_dequeued[i] == true){
            
            string carta_jogador = cur->carta_fila;
            
            // separa letra e número da carta para comparação
            string naipe_carta = carta_jogador.substr(0,1);
            string num_carta = carta_jogador.substr(1,2);
            
            if (naipe_carta > naipe_carta_vencedor) {
                empate = false;
                naipe_carta_vencedor = naipe_carta;
                num_carta_vencedor = num_carta;
                num_vencedor = i;
                
            } else if (naipe_carta == naipe_carta_vencedor) {
                
                if (num_carta > num_carta_vencedor) {
                    
                    empate = false;
                    naipe_carta_vencedor = naipe_carta;
                    num_carta_vencedor = num_carta;
                    num_vencedor = i;
                    
                } else if (num_carta == num_carta_vencedor) {
                    // condição de empate
                    empate = true;
                    
                }
                
            }
            
            cur = cur->next;
        }
    }
    
    if (empate == false) return num_vencedor;
    else return -1;
}

// transferir pilha para a fila do jogador
void transferir_cartas(fila *arr_fila, pilha *arr_pilha){
    int pilha_tamanho = tamanho_pilha(arr_pilha);
    for(int i=0; i < pilha_tamanho; i++) {
        enqueue(arr_fila, stack_pop(arr_pilha));
    }
}

int main()
{
    int number;
    cin >> number;

    // array de number ponteiros, onde cada ponteiro apontará para uma mão de cartas de um jogador
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
    int comando_dea = 0;
    
    // inicializador da pilha
    pilha *pilha_rodada;
    pilha_rodada = NULL;
    
    pilha *pilha_auxiliar;
    pilha_auxiliar = NULL;

    while (programa_encerrado == false) {

        if (cmd == "END") {
            
            int num_campeao = -1;
            int numero_cartas = -1;
            bool empate_campeao = true;
            
            for(int i=0; i<number; i++){
                int num_analisado = tamanho_fila(array_ponteiros[i]);
                
                if (num_analisado > numero_cartas){
                    empate_campeao = false;
                    numero_cartas = num_analisado;
                    num_campeao = i;
                } else if (num_analisado == numero_cartas){
                    empate_campeao = true;
                }
            }
            
            if (empate_campeao == false) cout << num_campeao << endl;
            else cout << -1 << endl;
            
            programa_encerrado = true;

        } else if (cmd == "DEA") {
            comando_dea++;

            for (int i=0; i < number; i++) {
                if (tamanho_fila(array_ponteiros[i]) != 0 || comando_dea <= 1){
                    string carta;
                    cin >> carta;
                    enqueue(array_ponteiros[i], carta);
                }
            }

            cin >> cmd;

        } else if (cmd == "RND") {
          
            num_rodadas++;
            pilha_rodada = new pilha();
            pilha_auxiliar = new pilha();
            
            int vencedor = -1;
            bool rodada_empatada = false;
            
            do {
                vencedor = vencedor_rodada(pilha_rodada, pilha_auxiliar, number, array_ponteiros);
                
            } while (vencedor == -1);
            
            int pilha_tamanho = tamanho_pilha(pilha_auxiliar);
            
            if (vencedor != -1) {
                transferir_cartas(array_ponteiros[vencedor], pilha_auxiliar);
                cout << num_rodadas << " " << vencedor << " " << pilha_tamanho << endl;
            } else {
                cout << "-1 -1 -1" << endl;
            }
            
            cin >> cmd;
            
        }
    }

    return 0;
}
