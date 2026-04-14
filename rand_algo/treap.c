#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Treap Node
typedef struct Node {
    int key;
    int priority;
    struct Node *left, *right;
} Node;

//Creating a new node
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->priority = rand()%100;  //randomly generated priority
    node->left = node->right = NULL;
    return node;
}

//Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}

//Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

//Insert
Node* insert(Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);

        //Fixing the heap property
        if (root->left->priority < root->priority)
            root = rotateRight(root);
    } 
    else {
        root->right = insert(root->right, key);

        //Fixing the heap property
        if (root->right->priority < root->priority)
            root = rotateLeft(root);
    }

    return root;
}

//Search
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

//Delete
Node* deleteNode(Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } 
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } 
    else {
        //Node found

        //One or no children
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        //Two children: rotate
        if (root->left->priority < root->right->priority) {
            root = rotateRight(root);
            root->right = deleteNode(root->right, key);
        } else {
            root = rotateLeft(root);
            root->left = deleteNode(root->left, key);
        }
    }

    return root;
}

//Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("(Key:%d, Priority:%d)\n", root->key, root->priority);
        inorder(root->right);
    }
}

// Main for testing
int main() {
    srand(time(NULL)); //seed for random number generator

    Node* root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 8);
    root = insert(root, 9);
    root = insert(root, 10);

    printf("Inorder traversal:\n");
    inorder(root);

    printf("\n\nSearching 4\n");
    Node* res = search(root, 4);
    if (res!=NULL)
        printf("Found %d\n", res->key);
    else
        printf("Not found\n");

    printf("\nDeleting 5\n");
    root = deleteNode(root, 5);

    printf("Inorder after deletion:\n");
    inorder(root);

    return 0;
}