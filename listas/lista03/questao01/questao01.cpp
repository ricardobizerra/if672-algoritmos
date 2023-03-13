#include <iostream>
using namespace std;

struct node {
    int value;
    int bf;
    node *left;
    node *right;

    node(int value): value(value), bf(0), left(NULL), right(NULL) {}
};

struct bst {
    node *root;

    bst(): root(NULL) {}
};

// find

struct return_bst_find {
    node *aux;
    int prof;

    return_bst_find(node *aux, int prof): aux(aux), prof(prof) {}
};

return_bst_find* bst_find(node *root, int v, int prof = 0) {
    if (root == NULL) return nullptr;
    else if (v == root->value) return new return_bst_find(root, prof);
    else if (v < root->value) return bst_find(root->left, v, prof + 1);
    else return bst_find(root->right, v, prof + 1);
}

// insertion

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
    
    else return nullptr;
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

// rotate left

node* rotate_left(node *root) {
    node *R = root->right;
    node *RL = root->right->left;
    R->left = root;
    root->right = RL;

    return R;
}

// rotate right

node* rotate_right(node *root) {
    node *L = root->left;
    node *LR = root->left->right;
    L->right = root;
    root->left = LR;

    return L;
}

// splay function

node* bst_find_parent(node* root, node* child) {
    if (root == NULL or root == child) return NULL;

    if (root->left == child or root->right == child) return root;

    if (child->value < root->value) return bst_find_parent(root->left, child);
    else return bst_find_parent(root->right, child);
}

node* splay(node *root, node *root_auxiliar, int previous_x, int x) {
    if (previous_x != 0) {
        node *parent_x = bst_find(root, previous_x)->aux;

        if (parent_x == NULL or root_auxiliar == NULL) return root_auxiliar;

        else {
            if (parent_x->left != NULL and parent_x->left->value == x) root_auxiliar = rotate_right(parent_x);
            else if (parent_x->right != NULL and parent_x->right->value == x) root_auxiliar = rotate_left(parent_x);

            splay(root, root_auxiliar, previous_x, x);
        }
        return root_auxiliar;
    }
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

        previous_number = number;
        cin >> number;
        return_bst_find *retorno = bst_find(root, number);

        if (cmd == "INS") {
            if (retorno != NULL) cout << retorno->prof << endl;
            else {
                if (root == NULL) root = new node(number);
                else bst_insert(root, number);
                cout << bst_find(root, number)->prof << endl;
                root = splay(root, root, previous_number, number);
            }
        } 
        
        else {
            cout << retorno->prof << endl;

            if (cmd == "FND") splay(root, root, previous_number, number);

            else if (cmd == "DEL") {
                node *parent_deleted = bst_find_parent(root, retorno->aux);
                bst_delete(retorno->aux, number);
                splay(root, root, previous_number, parent_deleted->value);
            }
        }

        cin >> cmd;
    }

    return 0;
}