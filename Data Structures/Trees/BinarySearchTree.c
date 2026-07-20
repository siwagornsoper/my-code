#include <stdio.h>
#include <stdlib.h>

struct Node{
    int item;

    struct Node *p;
    struct Node *left;
    struct Node *right;
};

struct Tree{
    struct Node *root;
};

struct Tree newTree(void){
    struct Tree tree;
    tree.root = NULL;
    return tree;
}

int treeEmpty(struct Tree *tree){
    if(tree->root == NULL)
        return 1;
    else return 0;
}

void treeInsert(struct Tree *tree, int num){
    struct Node *newNode;
    struct Node *i;
    
    newNode = malloc(sizeof(struct Node));

    newNode->item = num;
    newNode->left = NULL;
    newNode->right = NULL;

    if(treeEmpty(tree)){
        newNode->p = NULL;
        tree->root = newNode;
        
        return;
    }
    i = tree->root;

    while(i != NULL){
        if(i->item > num){
            if(i->left == NULL){
                i->left = newNode;
                newNode->p = i;
                return;
            }
            else{
                i = i->left;
            }
        }
        else{
            if(i->right == NULL){
                i->right = newNode;
                newNode->p = i;
                return;
            }
            else{
                i = i->right;
            }
        }
    }
}

void treeTransplant(struct Tree *tree, struct Node *node, struct Node *transplant){
    if(node->p == NULL){
        tree->root = transplant;
    }
    else if(node->p->left != NULL && node->p->left->item == node->item){
        node->p->left = transplant;
    }
    else{
        node->p->right = transplant;
    }

    if(transplant != NULL)
        transplant->p = node->p;
}

struct Node *treeMin(struct Node *node){
    while(node->left != NULL){
        node = node->left;
    }

    return node;
}

void treeRemove(struct Tree *tree, int num){
    struct Node *remove;

    remove = tree->root;

    while(remove->item != num){
        if(num < remove->item){  
            remove = remove->left;
        }
        else{
            remove = remove->right;
        }
    }

    /*after all that, remove should be the node that needs to be removed*/
    
    if(remove->right == NULL && remove->left == NULL){
        treeTransplant(tree, remove, NULL);
    }
    else if(remove->right == NULL && remove->left != NULL){
        treeTransplant(tree, remove, remove->left);
    }
    else if(remove->right != NULL && remove->left == NULL){
        treeTransplant(tree, remove, remove->right);
    }
    else{
        struct Node *successor;
        
        successor = treeMin(remove->right);
        
        if(successor != remove->right){
            treeTransplant(tree,successor,successor->right);
            successor->right = remove->right;
            remove->right->p = successor;
        }

        treeTransplant(tree,remove,successor);
        successor->left = remove->left;
        remove->left->p = successor;
    }

    free(remove);
}

void treeNodePrint(struct Node *node){
    if(node == NULL){
        return;
    }

    treeNodePrint(node->left);
    printf("%i ",node->item);
    treeNodePrint(node->right);
}

void treeAscendPrint(struct Tree *tree){
    treeNodePrint(tree->root);
    printf("\n");
}

int main(void){
    struct Tree tree;

    tree = newTree();

    treeInsert(&tree, 5);
    treeInsert(&tree, 4);
    treeInsert(&tree, 10);
    treeInsert(&tree, 8);
    treeInsert(&tree, 12);
    treeInsert(&tree, 6);
    treeInsert(&tree, 7);


    treeAscendPrint(&tree);

    return 0;
}
