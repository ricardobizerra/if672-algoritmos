#include <iostream>
using namespace std;

struct node {
    int value;
    int bf; // fator de balanceamento
    int depth; // profundidade
    node *left;
    node *right;
    node *parent; // nó superior

    node(int value,  int depth = 0, node *parent = NULL): value(value), bf(0), depth(depth), left(NULL), right(NULL), parent(parent) {}
};

// find

node* bst_find(node *root, int v) {
    if (root == NULL) return NULL;
    else if (v == root->value) return root;
    else if (v < root->value) return bst_find(root->left, v);
    else return bst_find(root->right, v);
}

// insertion

node* bst_insert(node *root, int v, node *parent = NULL, int depth = 0) {
    if (root == NULL) {
        node *new_node = new node(v, depth, parent);
        return new_node;
    }

    else {

        depth++;

        if (v < root->value) {
            root->left = bst_insert(root->left, v, root, depth);
            return root;
        }

        else {
            root->right = bst_insert(root->right, v, root, depth);
            return root;
        }
    }
}

// deletion

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
            free(root);
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
            free(root);
            return r;
        }

        else if (root->right == NULL) {
            node *r = root->left;
            free(root);
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

// rotate left

node* rotate_left(node *root) {
    node *R = root->right;
    node *RL = root->right->left;
    R->left = root;
    R->left->right = RL;
    root->right = RL;
    if (root->parent != NULL) root->parent->right = R;

    if (RL != NULL) RL->parent = root;
    R->parent = root->parent;
    root->parent = R;

    return R;
}

// rotate right

node* rotate_right(node *root) {
    node *L = root->left;
    node *LR = root->left->right;
    L->right = root;
    L->right->left = LR;
    root->left = LR;
    if (root->parent != NULL) root->parent->left = L;

    if (LR != NULL) LR->parent = root;
    L->parent = root->parent;
    root->parent = L;

    return L;
}

// splay function

node* splay(node *root, node *node_inserido, int x) {
    node *parent_x = node_inserido->parent;

    if (parent_x == NULL) return root;

    if (parent_x->left != NULL and parent_x->left->value == x) {
        node_inserido = rotate_right(parent_x);
    }
    else if (parent_x->right != NULL and parent_x->right->value == x) {
        node_inserido = rotate_left(parent_x);
    }
    
    if (node_inserido->left == root or node_inserido->right == root) root = node_inserido;
    if (node_inserido == root) return root;

    return splay(root, node_inserido, x);
}

// main function

int main(){
    string cmd;
    int number = 0;

    int previous_number;
    node *root = NULL;
    
    cin >> cmd;
    bool programa_encerrado = false;

    while (cmd != "END") {

        cin >> number;
        node *retorno = bst_find(root, number);

        if (cmd == "INS") {
            if (retorno != NULL) cout << retorno->depth << endl;
            else {
                if (root == NULL) root = new node(number);
                else bst_insert(root, number);
                cout << bst_find(root, number)->depth << endl;
                root = splay(root, bst_find(root, number), number);
            }
        } 
        
        else {
            cout << retorno->depth << endl;

            if (cmd == "FND") splay(root, bst_find(root, number), number);

            else if (cmd == "DEL") {
                node *parent_deleted = retorno->parent;
                bst_delete(retorno, number);
                splay(root, bst_find(root, parent_deleted->value), parent_deleted->value);
            }
        }

        cin >> cmd;
    }

    return 0;
}
