#include <iostream>
using namespace std;

struct node {
    int value;
    int depth; // profundidade
    node *left;
    node *right;
    node *parent; // nó superior

    node(int value,  int depth = 0, node *parent = NULL): value(value), depth(depth), left(NULL), right(NULL), parent(parent) {}
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
    return 0;
}