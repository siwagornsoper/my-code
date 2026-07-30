#include <stdio.h>
#include <stdlib.h>

struct Node{
    int height;
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

void fixHeight(struct Node *node){
    int tallest;

    if(node == NULL)
        return;

    tallest = -1;

        if(node->right != NULL){
            tallest = node->right->height;
        }

        if(node->left != NULL && node->left->height > tallest)
            tallest = node->left->height;

        node->height = tallest+1;
}

void singleLeft(struct Tree *tree, struct Node *node){
    struct Node *child;

    child = node->right;
    
    if(node->p == NULL){
        tree->root = child;
        child->p = NULL;
    }
    else{
        /*if the node is a right child*/
        if(node->p->right != NULL && node->p->right == node){
            node->p->right = child;
            child->p = node->p;
        }
        else{/*the node is a left child*/
            node->p->left = child;
            child->p = node->p;
        } 
    }

    node->right = child->left;
    if(node->right != NULL)
        node->right->p = node;
    node->p = child;
    child->left = node;

    fixHeight(node);
    fixHeight(child);
}



void singleRight(struct Tree *tree, struct Node *node){
    struct Node *child;

    child = node->left;

    if(node->p == NULL){
        child->p = NULL;
        tree->root = child;
    }
    else{
        child->p = node->p;
        if(node->p->right != NULL && node->p->right == node){
            node->p->right = child;
        }
        else
            node->p->left = child;
    }

    node->left = child->right;
    if(child->right != NULL){
        child->right->p = node;
    }

    node->p = child;
    child->right = node;

    fixHeight(node);
    fixHeight(child);
}

void doubleLeft(struct Tree *tree, struct Node *node){
    singleRight(tree, node->right);
    singleLeft(tree, node);
}

void doubleRight(struct Tree *tree, struct Node *node){
    singleLeft(tree, node->left);
    singleRight(tree, node);
}

int balanceFind(struct Node *node){
    int leftHeight;
    int rightHeight;
    int balance;

    if(node->left == NULL)
        leftHeight = -1;
    else
        leftHeight = node->left->height;

    if(node->right == NULL)
        rightHeight = -1;
    else
        rightHeight = node->right->height;

    return rightHeight - leftHeight;
}

void balanceAdjust(struct Tree *tree, struct Node *node){
    int balance;

    balance = balanceFind(node);
    
    if(balance >= 2){ /*right heavy*/
        if(balanceFind(node->right) > 0) /*child is right heavy*/
            singleLeft(tree, node);
        else
            doubleLeft(tree, node);
    }
    else if(balance <= -2){ /*left heavy*/
        if(balanceFind(node->left) > 0) /*child is right heavy*/
            doubleRight(tree, node);
        else
            singleRight(tree, node);
    }
}



/*does the proper rotations and height adjustments on the tree*/
void adjustTree(struct Tree *tree, struct Node *node){
    while(node != NULL){
        balanceAdjust(tree, node);
        
        fixHeight(node);

        node = node->p;
    }
}

void treeInsert(struct Tree *tree, int num){
    struct Node *newNode;
    struct Node *current;
    struct Node *parent;
    int right;
    int height;

    
    newNode = malloc(sizeof(struct Node));

    newNode->item = num;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    current = tree->root;
    parent = NULL;
    
    while(current != NULL){
        parent = current;

        if(current->item < num){
            current = current->right;
            right = 1;
        }
        else{
            current = current->left;
            right = 0;
        }
    }
    if(parent == NULL){
        tree->root = newNode;
        newNode->p = NULL;
        return;
    }

    if(right)
        parent->right = newNode;
    else
        parent->left = newNode;

    newNode->p = parent;

    adjustTree(tree, parent);
}

void treeTransplant(struct Tree *tree, struct Node *node, struct Node *transplant){
    if(node->p == NULL){
        tree->root = transplant;
    }
    else if(node->p->left != NULL && node->p->left == node){
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
    struct Node *fixPoint;

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
    if(remove == tree->root)
        tree->root = NULL;

    if(remove->right == NULL && remove->left == NULL){
        fixPoint = remove->p;
        treeTransplant(tree, remove, NULL);
    }
    else if(remove->right == NULL && remove->left != NULL){
        fixPoint = remove->p;
        treeTransplant(tree, remove, remove->left);
    }
    else if(remove->right != NULL && remove->left == NULL){
        fixPoint = remove->p;
        treeTransplant(tree, remove, remove->right);
    }
    else{
        struct Node *successor;
        
        successor = treeMin(remove->right);
        
        fixPoint = successor;

        if(successor != remove->right){
            fixPoint = successor->p;

            treeTransplant(tree,successor,successor->right);
            successor->right = remove->right;
            remove->right->p = successor;
        }

        treeTransplant(tree,remove,successor);
        successor->left = remove->left;
        remove->left->p = successor;
    }

    adjustTree(tree, fixPoint);

    free(remove);
}

void treeNodePrint(struct Node *node){
    if(node == NULL){
        return;
    }

    treeNodePrint(node->left);
    printf("%i:%i ",node->item,node->height);
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
