#include <iostream>
using namespace std;

struct node {
    int value;
    int depth; // profundidade
    node *next;
    node *parent; // nó superior

    node(int value, int depth = 0): value(value), depth(depth), next(NULL), parent(this) {}
};

node* find(node *node_find) {
    if (node_find->parent == node_find) return node_find;
    else return find(node_find->parent);
}

node* find_pathcompression(node *x) {
    if (x->parent != x) x->parent = find_pathcompression(x->parent);
    return x->parent;
}

void merge(node *x, node *y) {
    node *root_x = find_pathcompression(x);
    node *root_y = find_pathcompression(y);
    if (root_x != root_y) {
        if (root_x->depth < root_y->depth) swap(root_x, root_y);
        root_y->parent = root_x;
        if (root_x->depth == root_y->depth) root_x->depth++;
    }
}

int connected(node *x, node *y) {
    if (find_pathcompression(x) == find_pathcompression(y)) return 1;
    else return 0;
}

int main() {

    int k;
    cin >> k;

    for (int aux1=0; aux1 < k; aux1++) {
        int n, m, q;
        cin >> n >> m >> q;

        node **lab_nodes = new node*[n*n];
        bool *paredes_removidas = new bool[2*n*n - 2*n];

        for (int i=0; i < n*n; i++) {
            lab_nodes[i] = new node(i);
        }

        for (int i=0; i < (2*n*n - 2*n); i++) {
            paredes_removidas[i] = false;
        }

        for (int aux2=0; aux2 < m; aux2++) {
            int parede;
            cin >> parede;

            paredes_removidas[parede] = true;
        }

        for (int aux3=0; aux3 < n; aux3++) {
            for (int aux4=0; aux4 < n; aux4++) {
                int celula = aux3 * n + aux4;

                if (aux3 > 0 and paredes_removidas[2 * celula - n - aux3 - aux4]) merge(lab_nodes[celula], lab_nodes[celula - n]);

                if (aux4 > 0 and paredes_removidas[celula + (n-1)*aux3 - 1]) merge(lab_nodes[celula], lab_nodes[celula - 1]);
            }
        }

        for (int aux5=0; aux5 < q; aux5++) {
            int a, b;
            cin >> a >> b;

            cout << aux1 << "." << aux5 << " " << connected(lab_nodes[a], lab_nodes[b]) << endl;
        }

        cout << endl;
    }

    return 0;
}