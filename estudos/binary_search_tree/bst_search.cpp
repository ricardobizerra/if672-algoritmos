#include <iostream>
using namespace std;

struct node {
    int value;
    node *left;
    node *right;
    node(int value): value(value), left(NULL), right(NULL) {}
};

node* bst_search(node *root, int v) {
    if (root == NULL) return NULL;
    else if (v == root->value) return root;
    else if (v < root->value) return bst_search(root->left, v);
    else return bst_search(root->right, v);
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

    // retorna ponteiro para nó com valor 4, se existir, ou NULL
    node *search = bst_search(root, 4);
    cout << search->value << endl;

    return 0;
}