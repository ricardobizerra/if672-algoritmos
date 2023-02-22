#include <iostream>
using namespace std;

struct node {
    int timestamp;
    u_int32_t client;
    node *next;

    node(int timestamp, u_int32_t client): timestamp(timestamp), client(client), next(NULL) {}
};

struct array {
    node **array_elementos;
    int tamanho_array;
    int capacidade;

    array(int capacidade = 1): array_elementos(new node*[capacidade]), tamanho_array(0), capacidade(capacidade) {}

    // desestruturação
    ~array() {
        for (int i = 0; i < tamanho_array; i++) {
            delete array_elementos[i];
        }
        delete[] array_elementos;
    }

    // redimensiona array, caso sua capacidade máxima seja atingida
    void redimensionar(int aumento_capacidade) {
        node **novo_array_elementos = new node*[aumento_capacidade];

        for (int i = 0; i < tamanho_array; i++) {
            novo_array_elementos[i] = array_elementos[i];
        }

        delete[] array_elementos;

        array_elementos = novo_array_elementos;
        capacidade = aumento_capacidade;
    }

    void adicionar(node *new_node) {
        if (tamanho_array >= capacidade) {
            redimensionar(capacidade * 2);
        }

        array_elementos[tamanho_array] = new_node;
        tamanho_array++;
    }
};

struct return_search {
    u_int32_t client;
    int position;

    return_search(u_int32_t client, int position): client(client), position(position) {}
};

void binary_search(array &arr, int valor_procurado, return_search &retorno) {
    int client = -1;
    int posicao = -1;

    int n = arr.tamanho_array;

    int l = 0;
    int r = n - 1;

    while (l <= r) {
        int m = (l + r) / 2;

        node *cur = arr.array_elementos[m];

        if (cur->timestamp == valor_procurado) {
            client = cur->client;
            posicao = m;
            break;
        } else if (cur->timestamp < valor_procurado) {
            l = m + 1;
        } else {
            r = m - 1;
        }

        if (l >= n || r < 0 || l > r) {
            break;
        }
    }

    retorno.client = client;
    retorno.position = posicao;
}

void enqueue(array &arr, int timestamp, u_int32_t client){
    node *new_node = new node(timestamp, client);
    arr.adicionar(new_node);
}

int main(){
    string cmd;

    string client_input;
    u_int32_t client;

    int timestamp;

    int timestamp_qry;
    
    cin >> cmd;

    array conexoes_recebidas;
    bool programa_encerrado = false;

    while (programa_encerrado == false) {

        if (cmd == "END") {
            programa_encerrado = true;

        } else {

            if (cmd == "NEW") {

                cin >> timestamp;

                cin >> client_input;
                client = stoul(client_input);

                enqueue(conexoes_recebidas, timestamp, client);

            } else if (cmd == "QRY") {

                cin >> timestamp_qry;

                return_search retorno_qry(-1, -1);
                binary_search(conexoes_recebidas, timestamp_qry, retorno_qry);
                
                if (retorno_qry.position == -1) cout << -1 << " " << retorno_qry.position << endl;

                else cout << retorno_qry.client << " " << retorno_qry.position << endl;

            }

            cin >> cmd;

        }
    }

    return 0;
}