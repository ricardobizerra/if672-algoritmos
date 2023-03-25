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

int main() {
    return 0;
}