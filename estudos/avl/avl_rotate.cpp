#include <iostream>
using namespace std;

struct node {
    int value;
    int bf;
    node *left;
    node *right;

    node(int value): value(value), bf(0), left(NULL), right(NULL) {}    
};

node* avl_rotate_left(node *root) {
    node *R = root->right;
    node *RL = root->right->left;
    R->left = root;
    root->right = RL;

    if (R->bf >= 0) root->bf = root->bf - 1 - R->bf;
    else root->bf = root->bf - 1;

    if (root->bf < 0) R->bf = R->bf - 1 + root->bf;
    else R->bf = R->bf - 1;

    return R;
}

node* avl_rotate_right(node *root) {
    node *L = root->left;
    node *LR = root->left->right;
    L->right = root;
    root->left = LR;

    if (L->bf <= 0) root->bf = root->bf - 1 - L->bf;
    else root->bf = root->bf - 1;

    if (root->bf > 0) L->bf = L->bf - 1 + root->bf;
    else L->bf = L->bf - 1;

    return L;
}

struct return_avl_insert {
    node *node_return;
    int num_bool;

    return_avl_insert(node *node_return, int num_bool): node_return(node_return), num_bool(num_bool) {}
};

return_avl_insert* avl_insert(node *root, int v) {
    return_avl_insert *retorno;
    int hc;

    if (root == NULL) {
        node *n = new node(v);
        return new return_avl_insert(n, 1);
    }

    else if (root->value == v) return new return_avl_insert(root, 0); // não insere repetidos

    else if (root->value > v) {
        return_avl_insert *aux = avl_insert(root->left, v);
        root->left = aux->node_return;
        hc = aux->num_bool;

        root->bf = root->bf - hc;
    }

    else {
        return_avl_insert *aux = avl_insert(root->right, v);
        root->right = aux->node_return;
        hc = aux->num_bool;

        root->bf = root->bf + hc;
    }

    if (!hc) retorno = new return_avl_insert(root, 0);

    else if (root->bf == 0) retorno = new return_avl_insert(root, 0);

    else if (root->bf == 1 or root->bf == -1) retorno = new return_avl_insert(root, 1);

    else if (root->bf == -2) {
        if (root->left->bf == 1) root->left = avl_rotate_left(root->left);
        retorno = new return_avl_insert(avl_rotate_right(root), 0);
    }

    else if (root->bf == 2) {
        if (root->right->bf == -1) root->right = avl_rotate_right(root->right);
        retorno = new return_avl_insert(avl_rotate_left(root), 0);
    }

    return retorno;
}

int main() {
    // avl de exemplo
    node *root = new node(9);
    node *rootLeft = new node(5);
    node *rootRight = new node(15);
    node *rootLeftLeft = new node(3);
    node *rootLeftRight = new node(7);
    node *rootRightLeft = new node(11);
    node *rootRightRight = new node(18);
    node *rootRightLeftRight = new node(13);

    root->left = rootLeft;
    root->right = rootRight;
    rootLeft->left = rootLeftLeft;
    rootLeft->right = rootLeftRight;
    rootRight->left = rootRightLeft;
    rootRight->right = rootRightRight;
    rootRightLeft->right = rootRightLeftRight;

    // inserção do valor 12 na avl
    return_avl_insert *retorno1 = avl_insert(root, 12);
    return_avl_insert *retorno = avl_insert(retorno1->node_return, 14);
    cout << retorno->node_return->value << endl;

    return 0;
}