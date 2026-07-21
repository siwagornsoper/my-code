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

struct Node *treeSearch(struct Tree *tree, int num){
    struct Node *i;

    i = tree->root;

    while(i != NULL){
        if(i->item > num)
            i = i->left;
        else if(i->item < num)
            i = i->right;
        else
            return i;
    }

    return NULL;
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

struct Node *treeFindMin(struct Node *node){
    struct Node *min;
    
    while(node != NULL){
        min = node;
        node = node->left;
    }

    return min;
}

void treeTransplant(struct Tree *tree, struct Node *node, struct Node *transplant){
    if(transplant != NULL){
        transplant->p = node->p;
    }
    
    if(node->p == NULL){
        tree->root = transplant;
    }
    else if(node->p->right == node){
        node->p->right = transplant;
    }
    else{
        node->p->left = transplant;
    }
}

void treeRemove(struct Tree *tree, int num){
    struct Node *remove;
    
    remove = treeSearch(tree, num);

    if(remove == NULL)
        return;

    if(remove->left == NULL){
        treeTransplant(tree, remove, remove->right);
    }
    else if(remove->right == NULL){
        treeTransplant(tree, remove, remove->left);
    }
    else{
        struct Node *successor;

        successor = treeFindMin(remove);

        if(successor != remove->right){
            treeTransplant(tree, successor, successor->right);
            successor->right = remove->right;
            remove->right->p = successor;
        }
        
        treeTransplant(tree, remove, successor);
        successor->left = remove->left;
        remove->left->p = successor;
    }
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
    treeRemove(&tree, 5);
    treeRemove(&tree, 4);
    treeRemove(&tree, 6);

    printAscending(&tree);
}