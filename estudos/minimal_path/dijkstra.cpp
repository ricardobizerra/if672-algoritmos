#include <iostream>
using namespace std;

struct node {
    int node_value;
    int weight;
    node *next;

    node(int node_value, int weight): node_value(node_value), weight(weight), next(NULL) {}
};

// uso de lista de adjacência para representar grafo
struct adj_list {
    bool origin_node;
    node *head;
    node *tail;

    adj_list(bool origin_node = false): origin_node(origin_node), head(NULL), tail(NULL) {} // adj_list vazia, no início

    // enfileirar
    void enqueue(int node_value, int weight){
        node *new_node = new node(node_value, weight);

        if (tail == NULL) {
            // fila vazia
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    // tamanho da fila
    int tamanho_fila() {
        int retorno = 0;
        node *cur = this->head;
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
};

struct min_heap {
    int* heap_array;
    int heap_size;

    min_heap(int capacity): heap_size(0) {
        heap_array = new int[capacity];
    }

    void bubble_up(int index) {
        int parent_index = (index-1)/2;
        while (index > 0 && heap_array[parent_index] > heap_array[index]) {
            swap(heap_array[parent_index], heap_array[index]);
            index = parent_index;
            parent_index = (index-1)/2;
        }
    }

    void heap_insert(int value) {
        heap_array[heap_size] = value;
        bubble_up(heap_size);
        heap_size++;
    }

    void heapify(int index) {
        int left_child_index = 2*index + 1;
        int right_child_index = 2*index + 2;
        int smallest = index;

        if (left_child_index < heap_size && heap_array[left_child_index] < heap_array[smallest]) {
            smallest = left_child_index;
        }
        if (right_child_index < heap_size && heap_array[right_child_index] < heap_array[smallest]) {
            smallest = right_child_index;
        }

        if (smallest != index) {
            swap(heap_array[index], heap_array[smallest]);
            heapify(smallest);
        }
    }

    int heap_extract() {
        int min_val = heap_array[0];
        heap_size--;
        heap_array[0] = heap_array[heap_size];
        heapify(0);
        return min_val;
    }

    void heap_update(int old_value, int new_value) {
        int index = -1;
        for (int i = 0; i < heap_size; i++) {
            if (heap_array[i] == old_value) {
                index = i;
                break;
            }
        }
        if (index > -1) {
            heap_array[index] = new_value;
            if (new_value < old_value) {
                bubble_up(index);
            } else {
                heapify(index);
            }
        }
    }
};

// dijkstra
struct dijkstra_return {
    int* d;
    int* f;

    dijkstra_return(int* d, int* f): d(d), f(f) {}
};

dijkstra_return* dijkstra(adj_list *grafo[], int s, int tamanho_grafo) {
    grafo[s]->origin_node = true;

    int *d = new int[tamanho_grafo];
    int *f = new int[tamanho_grafo];

    for (int i=0; i<tamanho_grafo; i++) {
        d[i] = 1000000000;
        f[i] = -1;
    }

    d[s] = 0;
    f[s] = s;

    min_heap *h = new min_heap(tamanho_grafo);
    
    for (int i=0; i<tamanho_grafo; i++) {
        h->heap_insert(i);
    }

    for (int i=0; i<tamanho_grafo; i++) {
        int u = h->heap_extract();
        
        node *e = grafo[u]->head;

        while (e != NULL) {
            if (d[e->node_value] > d[u] + e->weight) {
                int old_value = d[e->node_value];
                d[e->node_value] = d[u] + e->weight;
                f[e->node_value] = u;
                h->heap_update(old_value, d[e->node_value]);
            }
            e = e->next;
        }
        
    }

    return new dijkstra_return(d, f);
}

int main() {
    int number = 5;
    adj_list *grafo[number];

    for (int i=0; i < number; i++) {
        grafo[i] = NULL;
        grafo[i] = new adj_list();
    }

    // grafo de exemplo
    grafo[0]->enqueue(1, 2);
    grafo[0]->enqueue(2, 3);
    grafo[1]->enqueue(3, 4);
    grafo[2]->enqueue(1, 1);
    grafo[2]->enqueue(4, 2);
    grafo[3]->enqueue(4, 5);
    grafo[4]->enqueue(0, 2);
    grafo[4]->enqueue(3, 3);

    // execução do algoritmo de dijkstra
    dijkstra_return *retorno = dijkstra(grafo, 0, number);
    
    cout << "d: ";
    for (int i=0; i<number; i++) {
        cout << retorno->d[i] << " ";
    }
    cout << endl;

    cout << "f: ";
    for (int i=0; i<number; i++) {
        cout << retorno->f[i] << " ";
    }
    cout << endl;

    return 0;
}