#include <iostream>
using namespace std;

struct input_new {
	int i;
	int s;

	input_new(int i, int s): i(i), s(s) {};
};

struct input_qry {
	u_int32_t c;
	int j;

	input_qry(u_int32_t c, int j): c(c), j(j) {};
};

struct node {
	int timestamp;
	u_int32_t client;
	node *next;

	node(int timestamp, u_int32_t client): timestamp(timestamp), client(client), next(NULL) {};
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

	void enqueue(int timestamp, u_int32_t client){
		node *new_node = new node(timestamp, client);
		adicionar(new_node);
	}
};

struct hash_table {
	int m; // tamanho da tabela
	int num_elementos; // número de elementos, no início é 0
	float l_max; // fator de carga máximo
	array **table; // table de arrays de nodes

	hash_table(int m, float l_max): m(m), num_elementos(0), l_max(l_max) {
		table = new array *[m]();
	};

	~hash_table() {
		for (int i = 0; i < m; i++) {
			delete table[i];
		}
		delete[] table;
	}

	// h(T) = T mod m
	int node_key(int timestamp) {
		return (timestamp % m);
	}

	void insercao(int timestamp, u_int32_t client, input_new &retorno, array &elementos) {
	    int return_i = -1;
		int return_s = -1;
		
		float l = static_cast<float>(num_elementos) / m; // fator de carga atual

		// verificação, antes da inserção, da necessidade de rehashing
		if (l > l_max) {
			rehashing(elementos);
		}

		node *novo_node = new node(timestamp, client);

		int valor_hash_node = node_key(novo_node->timestamp);

		if (!table[valor_hash_node]) {
			array *novo_array = new array();
			table[valor_hash_node] = novo_array;
		}
		num_elementos++;

		table[valor_hash_node]->enqueue(novo_node->timestamp, novo_node->client);

		return_i = valor_hash_node;
		return_s = table[valor_hash_node]->tamanho_array;
		
		retorno.i = return_i;
		retorno.s = return_s;
	}

	void rehashing(array &elementos) {
		int novo_tamanho = (2 * m) + 1;

		array **nova_table = new array *[novo_tamanho];

		for (int index = 0; index < (elementos.tamanho_array); index++) {
			node *cur = elementos.array_elementos[index];
			int novo_valor_hash_node = (cur->timestamp) % novo_tamanho;

			if (!nova_table[novo_valor_hash_node]) {
				array *novo_array = new array();
				nova_table[novo_valor_hash_node] = novo_array;
			}

			nova_table[novo_valor_hash_node]->enqueue(cur->timestamp, cur->client);
		}

		table = nova_table;
		m = novo_tamanho;
	}

	void busca_elemento(int timestamp, input_qry &retorno) {
		int return_c = -1;
		int return_j = -1;
        int valor_hash_node = node_key(timestamp);
        array *cur = table[valor_hash_node];
        if (cur == NULL) {
    	    return;
        } else {
    		/*for (int i=0; i < cur->tamanho_array; i++) {
    			if (cur->array_elementos[i]->timestamp == timestamp) {
    				return_c = cur->array_elementos[i]->client;
    				return_j = i;
    				break;
    			}
    		}*/
            
			int l = 0;
			int r = cur->tamanho_array - 1;

			while (l <= r) {
				int m = (l + r) / 2;

				node *ponteiro = cur->array_elementos[m];

				if (ponteiro->timestamp == timestamp) {
					return_c = ponteiro->client;
					return_j = m;
					break;
				} else if (ponteiro->timestamp < timestamp) {
					l = m + 1;
				} else {
					r = m - 1;
				}

				if (l >= cur->tamanho_array || r < 0 || l > r) {
					break;
				}				
			}
        }

		retorno.c = return_c;
		retorno.j = return_j;
    }
};

int main() {

	// input dos parâmetros da timestamp
	int m;
	float l_max;

	cin >> m >> l_max;

	hash_table table_timestamps(m, l_max);

	string cmd;
	cin >> cmd;

	// inicializando outros inputs do NEW e QRY
	string client_input;
    u_int32_t client;
    int timestamp;
    int timestamp_qry;

	// array ordenado de registro dos elementos que serão inseridos
	array elementos(1);

	while (cmd != "END") {

		if (cmd == "NEW") {

			cin >> timestamp;

			cin >> client_input;
			client = stoul(client_input);

			input_new retorno_new(-1, -1);
			table_timestamps.insercao(timestamp, client, retorno_new, elementos);
			elementos.enqueue(timestamp, client);

			cout << retorno_new.i << " " << retorno_new.s << endl;

		} else if (cmd == "QRY") {

			cin >> timestamp_qry;

			input_qry retorno_qry(-1, -1);
			table_timestamps.busca_elemento(timestamp_qry, retorno_qry);

			if (retorno_qry.j != -1) cout << retorno_qry.c << " " << retorno_qry.j << endl;
			else cout << "-1 -1" << endl;

		}

		cin >> cmd;

	}

	return 0;

}