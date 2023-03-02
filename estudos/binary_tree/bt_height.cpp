#include <iostream>
using namespace std;

struct node {
    int value;
    node *left;
    node *right;
    node(int value): value(value), left(NULL), right(NULL) {}
};

int height(node *root) {
    if (root == NULL) return 0;

    int l = height(root->left);
    int r = height(root->right);

    return 1 + max(l, r);
}

int main() {
    // binary tree de exemplo
    node *root = new node(1);
    node *leftChild = new node(2);
    node *rightChild = new node(3);
    node *leftGrandchild = new node(4);
    node *rightGrandchild = new node(5);

    root->left = leftChild;
    root->right = rightChild;
    leftChild->left = leftGrandchild;
    rightChild->right = rightGrandchild;

    // cálculo da altura
    int bt_height = height(root);

    cout << bt_height << endl;

    return 0;
}