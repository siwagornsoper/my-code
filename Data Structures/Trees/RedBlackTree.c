#include <stdio.h>
#include <stdlib.h>

struct Node{
    int item;

    struct Node *p;
    struct Node *right;
    struct Node *left;
};

struct Tree{
    struct Node *root;
};

struct Tree newTree(){
    struct Tree tree;
    tree.root = NULL;

    return tree;
}

int treeEmpty(struct Tree *tree){
    if(tree->root == NULL)
        return 1;
    else
        return 0;
}

void treeInsert(struct Tree *tree, int num){
    struct Node *newNode;
    struct Node *i;
    struct Node *parent;

    newNode = malloc(sizeof(struct Node));
    newNode->item = num;
    newNode->right = NULL;
    newNode->left = NULL;

    i = tree->root;
    parent = NULL;

    while(i != NULL){
        parent = i;

        if(i->item > num){
            i = i->left;
        }
        else{
            i = i->right;
        }
    }

    newNode->p = parent;

    if(parent == NULL){
        tree->root = newNode;
    }
    else if(parent->item > num)
        parent->left = newNode;
    else
        parent->right = newNode;
}

void printAscendingHelper(struct Node *node){
    if(node == NULL)
        return;

    printAscendingHelper(node->left);
    printf("%i ", node->item);
    printAscendingHelper(node->right);
}

void printAscending(struct Tree *tree){
    printAscendingHelper(tree->root);
    printf("\n");
}

int main(){
    struct Tree tree;

    tree = newTree();

    treeInsert(&tree, 5);
    treeInsert(&tree, 6);
    treeInsert(&tree, 4);

    printAscending(&tree);
}