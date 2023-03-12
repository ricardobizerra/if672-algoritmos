#include <iostream>
using namespace std;

struct node {
    int value;
    node *left;
    node *right;
    node(int value): value(value), left(NULL), right(NULL) {}
};

node* bst_insert(node *root, int v) {
    if (root == NULL) {
        node *new_node = new node(v);
        return new_node;
    }

    else if (v < root->value) {
        root->left = bst_insert(root->left, v);
        return root;
    }

    else {
        root->right = bst_insert(root->right, v);
        return root;
    }
}

int main() {
    // binary search tree de exemplo
    node *root = new node(3);
    node *leftChild = new node(2);
    node *rightChild = new node(4);
    node *leftGrandchild = new node(1);
    node *rightGrandchild = new node(5);

    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leftGrandchild;
    rightChild->right = rightGrandchild;

    // retorna ponteiro para "nova" raiz após inserção
    node *insert = bst_insert(root, 6);
    cout << insert->value << endl;

    return 0;
}