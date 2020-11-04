
/* file: BST.h
Ari Iramanesh
id: 1628897
class: 12B
assignment 3

desc: Defines the BSTObj struct and prototypes its functions that will be used in 
a binary search tree. The functions are implemented in BST.c.

*/
//-----------------------------------------------------------------------------
// BST.h
// Header file for the BST ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#ifndef _BST_H_INCLUDE_
#define _BST_H_INCLUDE_
#define TRUE 1
#define FALSE 0

// Exported reference type
// Tree node to store strings, space must be allocated for the strings
typedef struct BSTObj {
    char               *term;           /* string data in each block */
    struct BSTObj      *leftChild;      /* ptr to left child */
    struct BSTObj      *rightChild;     /* ptr to right child */
} BSTObj;


// add a new node to the BST with the new_data values, space must be allocated in the BST node
void insert(char *new_data,  BSTObj **pBST);

// print to OUT the inorder traversal
void inorderTraverse(FILE *out, BSTObj *T);

// print to OUT the preorder traversal
void preorderTraverse(FILE *out, BSTObj *T);

// print to OUT the postorder traversal
void postorderTraverse(FILE *out, BSTObj *T);

// print the leaves of the tree in inorder to OUT
void inorderLeaves(FILE *out, BSTObj *T);


// return TRUE if the item_to_find matches a string stored in the tree
int  find(char *term_to_find, BSTObj *T);
  
// compute the height of the tree
int treeHeight(BSTObj *T, int height);

// create and return a complete memory independent copy of the tree 
BSTObj * copyTree(BSTObj *T);

// remove all the nodes from the tree, deallocate space and reset Tree pointer
void makeEmpty(BSTObj **pT);

#endif
