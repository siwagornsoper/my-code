#include <stdio.h>
#include <stdlib.h>

struct Node{
    int item;
    char color; /*1 is black, 0 is red*/
    struct Node *p;
    struct Node *right;
    struct Node *left;
};

struct Tree{
    struct Node *root;
    struct Node *NIL;
};

struct Tree newTree(){
    struct Tree tree;
    
    tree.NIL = malloc(sizeof(struct Node));
    tree.NIL->color = 1;
    tree.NIL->p = NULL;
    tree.NIL->left = NULL;
    tree.NIL->right = NULL;

    tree.root = tree.NIL;

    return tree;
}

int treeEmpty(struct Tree *tree){
    if(tree->root == tree->NIL)
        return 1;
    else
        return 0;
}

struct Node *treeSearch(struct Tree *tree, int num){
    struct Node *i;

    i = tree->root;

    while(i != tree->NIL){
        if(i->item > num)
            i = i->left;
        else if(i->item < num)
            i = i->right;
        else
            return i;
    }

    return tree->NIL;
}

void leftRotation(struct Tree *tree, struct Node *node){
    struct Node *child;

    child = node->right;
    
    if(node->p == tree->NIL){
        tree->root = child;
        child->p = tree->NIL;
    }
    else{
        /*if the node is a right child*/
        if(node->p->right != tree->NIL && node->p->right == node){
            node->p->right = child;
            child->p = node->p;
        }
        else{/*the node is a left child*/
            node->p->left = child;
            child->p = node->p;
        } 
    }

    node->right = child->left;
    if(node->right != tree->NIL)
        node->right->p = node;
    node->p = child;
    child->left = node;
}



void rightRotation(struct Tree *tree, struct Node *node){
    struct Node *child;

    child = node->left;

    if(node->p == tree->NIL){
        child->p = tree->NIL;
        tree->root = child;
    }
    else{
        child->p = node->p;
        if(node->p->right != tree->NIL && node->p->right == node){
            node->p->right = child;
        }
        else
            node->p->left = child;
    }

    node->left = child->right;
    if(child->right != tree->NIL){
        child->right->p = node;
    }

    node->p = child;
    child->right = node;
}

void treeFixUp(struct Tree *tree, struct Node *z){
    while(z->p->color == 0){

        if(z->p->p->left == z->p){ /*if z's parent is a left child*/
            struct Node *y = z->p->p->right; /*z's uncle*/
            
            if(y->color == 0){ /*uncle is red*/
                y->color = 1;
                z->p->color = 1;
                z->p->p->color = 0;
                
                z = z->p->p;
            }
            else{ /*uncle is black*/
                if(z->p->right == z){ /*z is a right child*/
                    leftRotation(tree, z->p);

                    z = z->left; /*the former parent becomes z*/
                }
                
                z->p->color = 1;
                z->p->p->color = 0;

                rightRotation(tree, z->p->p);
            }
        }
        else{ /*z's parent is a right child*/
            struct Node *y = z->p->p->left; /*z's uncle*/
            
            if(y->color == 0){ /*uncle is red*/
                y->color = 1;
                z->p->color = 1;
                z->p->p->color = 0;
                
                z = z->p->p;
            }
            else{ /*uncle is black*/
                if(z->p->left == z){ /*z is a left child*/
                    rightRotation(tree, z->p);

                    z = z->right; /*the former parent becomes z*/
                }
                
                z->p->color = 1;
                z->p->p->color = 0;

                leftRotation(tree, z->p->p);
            }
        }
    }
    tree->root->color = 1;
}

void treeInsert(struct Tree *tree, int num){
    struct Node *newNode;
    struct Node *i;
    struct Node *parent;

    newNode = malloc(sizeof(struct Node));
    newNode->item = num;
    newNode->right = tree->NIL;
    newNode->left = tree->NIL;

    i = tree->root;
    parent = tree->NIL;

    while(i != tree->NIL){
        parent = i;

        if(i->item > num){
            i = i->left;
        }
        else{
            i = i->right;
        }
    }

    newNode->p = parent;

    if(parent == tree->NIL){
        tree->root = newNode;
    }
    else if(parent->item > num)
        parent->left = newNode;
    else
        parent->right = newNode;

    newNode->color = 0;

    treeFixUp(tree, newNode);
}


/*remove remains unimplemented*/


void printAscendingHelper(struct Tree *tree, struct Node *node){
    if(node == tree->NIL)
        return;

    printAscendingHelper(tree, node->left);
    printf("%i ", node->item);
    printAscendingHelper(tree, node->right);
}

void printAscending(struct Tree *tree){
    printAscendingHelper(tree, tree->root);
    printf("\n");
}

int main(){
    struct Tree tree;

    tree = newTree();

    treeInsert(&tree, 4);
    treeInsert(&tree, 5);
    treeInsert(&tree, 6);
    treeInsert(&tree, 7);
    treeInsert(&tree, 8);
    treeInsert(&tree, 9);
    treeInsert(&tree, 10);
    treeInsert(&tree, 11);
    treeInsert(&tree, 12);
    treeInsert(&tree, 13);
    treeInsert(&tree, 14);

    printAscending(&tree);

    return 0;
}