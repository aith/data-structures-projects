/*file: BST.c
Ari Iramanesh
id: 1628897
class: 12B
assignment 3

desc: Implements functions found in BST.h and also makeNode() for a binary search tree

*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "BST.h"
#define STR_MAX 10 //for term allocation

//precondition: empty term is legal
BSTObj *makeNode(char *term){
    BSTObj *new_node = malloc(sizeof(BSTObj));
    if (new_node == NULL){
        fprintf(stderr, "error: could not allocate space for new node. exiting\n");
        exit(EXIT_FAILURE);
    }
    new_node->term = (char*) malloc(sizeof(char)*(strlen(term)+1)); //STUDY THIS; char then *
    new_node->term = term; //does this send the whole string
    return new_node;
}

// add a new node to the BST with the new_data values, space must be allocated in the
// note: a node of equal data will be inserted to the left
void insert(char *new_data, BSTObj **pBST){
    //case 1: pointer to BST is empty, inserts node
    if(*pBST == NULL){
        *pBST = makeNode(new_data);
    }
    if((pBST) == NULL){
        fprintf(stderr, "error: cannot take null pointer");
       exit(EXIT_FAILURE); //does pointer to string return whole string
    }
    if(new_data == '\0'){
        fprintf(stderr, "error; cannot take null data as input");
        exit(EXIT_FAILURE);
    }

    //case 2: data entry is less than or equal compared node
    else if((strcmp(new_data, (*pBST)->term) <= 0)){
        insert(new_data, &((*pBST)->leftChild));
    } 
    //case 3: data entry is greater than compared node
    else if((strcmp(new_data, (*pBST)->term) > 0)){
        insert(new_data, &((*pBST)->rightChild));
    } 
    //case 4: there is already this data entry in the BST
}

// print to OUT the inorder traveral
void inorderTraverse(FILE *out, BSTObj *T){
    if(T == NULL) return;
    if(out == NULL){
        fprintf(stderr, "error: output stream is NULL, so cannot traverse. Exiting\n");
    }

    inorderTraverse(out, T->leftChild);
    fprintf(out, "%s ", T->term);
    inorderTraverse(out, T->rightChild);
}
// print to OUT the preorder traveral
void preorderTraverse(FILE *out, BSTObj *T){
    if(T == NULL) return;
    if(out == NULL){
        fprintf(stderr, "error: output stream is NULL, so cannot traverse. Exiting\n");
    }

    fprintf(out, "%s ", T->term);
    preorderTraverse(out, T->leftChild);
    preorderTraverse(out, T->rightChild);
}
// print to OUT the postorder traveral
void postorderTraverse(FILE *out, BSTObj *T){
    if(T == NULL) return;
    if(out == NULL){
        fprintf(stderr, "error: output stream is NULL, so cannot traverse. Exiting\n");
    }
    
    postorderTraverse(out, T->leftChild);
    postorderTraverse(out, T->rightChild);
    fprintf(out, "%s ", T->term);
}
// print the only the leaves of the tree in order to OUT
void inorderLeaves(FILE *out, BSTObj *T){
    if(T == NULL) return;
    if(out == NULL){
        fprintf(stderr, "error: output stream is NULL, so cannot print output. Exiting\n");
    }

    inorderLeaves(out, T->leftChild);
    if(T->leftChild == NULL && T->rightChild == NULL){
        fprintf(out, "%s ", T->term);
    }
    inorderLeaves(out, T->rightChild);
}
// return TRUE if the item_to_find matches a string stored in the tree
int find(char *term_to_find, BSTObj *T){
    //case 1: find() has reached an empty node
    if(T == NULL) return FALSE; //put null checker first or else seg fault

    //case 2: searched node is found
    if(term_to_find == T->term){
        return TRUE;
    }
    //case 3: call find() on both children of node
    //note: if the searched node is found at least once, it'll always return 1
    return( (find(term_to_find, T->leftChild) + find(term_to_find, T->rightChild)) >= 1 ? TRUE : FALSE );
}
// compute the height of the tree
// preconditions: initial call of treeHeight() should have height be 0 for correctness, T may be empty
int treeHeight(BSTObj *T, int height){
    if (T == NULL){
        return height;
    }
    //add 1 for each node downwards
    int left = treeHeight(T->leftChild,height + 1);
    int right = treeHeight(T->rightChild,height + 1);
    //compare branches, return branch with higher height
    return (left > right ? left : right);
}
// create and return a complete mempry independent copy of the tree
BSTObj * copyTree(BSTObj *T){
    //case 1: return NULL if tree or child is NULL
    if(T == NULL){
        return NULL;
    }
    //case 2: copy current node and set its children to copyTree() of current node's children
    BSTObj *new_node = makeNode(T->term);
    new_node->leftChild = copyTree(T->leftChild);
    new_node->rightChild = copyTree(T->rightChild);
    return new_node;
}
// remove all the nodes from the tree, doallocate space and reset Tree pointer
void makeEmpty(BSTObj **pT){
    //case 1: return if tree or node is empty
    if(*pT == NULL){ //checks if pointer contains BSTObj
        return;
    }
    //case 2: call makeEmpty() till last nodes are reached, then start freeing nodes upwards
    makeEmpty(&((*pT)->leftChild));
    makeEmpty(&((*pT)->rightChild));
    //free at end
    (*pT)->leftChild = NULL;
    (*pT)->rightChild = NULL;
    (*pT)->term = NULL; //since we malloc'ed space for the string, we needa free it
    free((*pT)->term);
    (*pT)->term = NULL;
    free(*pT);
    *pT = NULL;
}
