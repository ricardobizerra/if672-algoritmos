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

// find

struct return_bst_find {
    node *node_aux;
    int search_depth;

    return_bst_find(node *node_aux, int search_depth): node_aux(node_aux), search_depth(search_depth) {}
};

return_bst_find* bst_find(node *root, int v, int search_depth = 0) {
    if (root == NULL) return new return_bst_find(NULL, search_depth);
    else if (v == root->value) return new return_bst_find(root, search_depth);
    else {
        search_depth++;
        if (v < root->value) return bst_find(root->left, v, search_depth);
        else return bst_find(root->right, v, search_depth);
    }
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
            if (r != NULL) {
                r->parent = root->parent;
                r->depth = root->depth;
            }
            free(root);
            bst_delmin_return *retorno = new bst_delmin_return(r, v);
            return retorno;
        } else {
            bst_delmin_return *aux = bst_delete_min(root->left);
            root->left = aux->node_return;
            if (root->left != NULL) root->left->parent = root;
            bst_delmin_return *retorno = new bst_delmin_return(root, aux->value);
            return retorno;
        }
    }
    
    else return NULL;
}

node* bst_delete(node *root, int v) {
    if (root == NULL) return NULL;

    else if (v < root->value) {
        root->left = bst_delete(root->left, v);
        if (root->left != NULL) root->left->parent = root;
        return root;
    } else if (v > root->value) {
        root->right = bst_delete(root->right, v);
        if (root->right != NULL) root->right->parent = root;
        return root;
    } else {
        if (root->left == NULL) {
            node *r = root->right;
            if (r != NULL) {
                r->parent = root->parent;
                r->depth = root->depth;
            }
            free(root);
            return r;
        } else if (root->right == NULL) {
            node *l = root->left;
            if (l != NULL) {
                l->parent = root->parent;
                l->depth = root->depth;
            }
            free(root);
            return l;
        } else {
            bst_delmin_return *aux = bst_delete_min(root->right);
            root->right = aux->node_return;
            if (root->right != NULL) root->right->parent = root;
            root->value = aux->value;
            return root;
        }
    }
}

// rotate left

void rotate_left(node *&root, node *&node_to_rotate) {
    node *R = node_to_rotate->right;
    node_to_rotate->right = R->left;

    if (node_to_rotate->right != NULL) {
        node_to_rotate->right->parent = node_to_rotate;
        node_to_rotate->right->depth = node_to_rotate->depth + 1;
    }

    R->parent = node_to_rotate->parent;
    R->depth = node_to_rotate->depth;

    if (node_to_rotate->parent == NULL) root = R;
    else if (node_to_rotate == node_to_rotate->parent->left) node_to_rotate->parent->left = R;
    else node_to_rotate->parent->right = R;

    R->left = node_to_rotate;
    node_to_rotate->parent = R;
    node_to_rotate->depth = R->depth + 1;
}


// rotate right

void rotate_right(node *&root, node *&node_to_rotate) {
    node *L = node_to_rotate->left;
    node_to_rotate->left = L->right;

    if (node_to_rotate->left != NULL) {
        node_to_rotate->left->parent = node_to_rotate;
        node_to_rotate->left->depth = node_to_rotate->depth + 1;
    }

    L->parent = node_to_rotate->parent;
    L->depth = node_to_rotate->depth;

    if (node_to_rotate->parent == NULL) root = L;
    else if (node_to_rotate == node_to_rotate->parent->left) node_to_rotate->parent->left = L;
    else node_to_rotate->parent->right = L;

    L->right = node_to_rotate;
    node_to_rotate->parent = L;
    node_to_rotate->depth = L->depth + 1;
}

// splay function

node* splay(node *root, node *node_inserido, int x) {
    node *parent_x = node_inserido->parent;

    if (parent_x == NULL) return root;

    if (parent_x->left != NULL and parent_x->left->value == x) rotate_right(root, parent_x);
    else if (parent_x->right != NULL and parent_x->right->value == x) rotate_left(root, parent_x);
    
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
        return_bst_find *retorno = bst_find(root, number);

        if (cmd == "INS") {
            if (retorno->node_aux != NULL) cout << retorno->search_depth << endl;
            else {
                if (root == NULL) root = new node(number);
                else bst_insert(root, number);
                cout << bst_find(root, number)->node_aux->depth << endl;
            }
            root = splay(root, bst_find(root, number)->node_aux, number);
        } 
        
        else {

            if (cmd == "FND") {
                if (retorno->node_aux != NULL) {
                    cout << retorno->search_depth << endl;
                    root = splay(root, bst_find(root, number)->node_aux, number);
                }
                else {
                    cout << bst_find(root, number)->search_depth << endl;
                }
            }

            else if (cmd == "DEL") {
                if (retorno->node_aux != NULL) {
                    cout << retorno->search_depth << endl;
                    node *parent_deleted = retorno->node_aux->parent;
                    bst_delete(root, number);
                    if (parent_deleted != NULL) root = splay(root, bst_find(root, parent_deleted->value)->node_aux, parent_deleted->value);
                }
                else {
                    cout << bst_find(root, number)->search_depth << endl;
                }
            }
        }

        cin >> cmd;
    }

    return 0;
}