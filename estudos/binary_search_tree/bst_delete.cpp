#include <iostream>
using namespace std;

struct node {
    int value;
    node *left;
    node *right;
    node(int value): value(value), left(NULL), right(NULL) {}
};

struct bst_delmin_return {
    node *node_return;
    int value;
    bst_delmin_return(node *node_return, int value): node_return(node_return), value(value) {}
};

bst_delmin_return* bst_delete_min(node *root) {
    if (root != NULL) {
        if (root->left == NULL) {
            int v = root->value;
            node *r = root->right;
            delete(root);
            bst_delmin_return *retorno = new bst_delmin_return(r, v);
            return retorno;
        }

        else {
            bst_delmin_return *aux = bst_delete_min(root->left);
            root->left = aux->node_return;
            int v = aux->value;
            bst_delmin_return *retorno = new bst_delmin_return(root, v);
            return retorno;
        }
    } 
    
    else return NULL;
}

node* bst_delete(node *root, int v) {
    if (root == NULL) return NULL;

    else if (v < root->value) {
        root->left = bst_delete(root->left, v);
        return root;
    }

    else if (v > root->value) {
        root->right = bst_delete(root->right, v);
        return root;
    }

    else {
        if (root->left == NULL) {
            node *r = root->right;
            delete(root);
            return r;
        }

        else if (root->right == NULL) {
            node *r = root->left;
            delete(root);
            return r;
        }

        else {
            bst_delmin_return *aux = bst_delete_min(root->right);
            root->right = aux->node_return;
            root->value = aux->value;

            return root;
        }
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

    // retorna ponteiro para "nova" raiz após deleção
    node *deleted = bst_delete(root, 6);
    cout << deleted->value << endl;

    return 0;
}