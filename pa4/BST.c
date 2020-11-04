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

void deleteNode(BSTObj *T);
BSTObj **retrieveNode(char *term_to_delete, BSTObj **T);
int findLeftmost (BSTObj *T, BSTObj **leftmostParent, BSTObj **leftmost);

//precondition: empty term is legal
BSTObj *makeNode(char *term){
    BSTObj *new_node = malloc(sizeof(BSTObj));
    if (new_node == NULL){
        fprintf(stderr, "error: could not allocate space for new node. exiting\n");
        exit(EXIT_FAILURE);
    }
    new_node->term = (char*) malloc(sizeof(char)*(strlen(term)+1)); //STUDY THIS; char then *
    new_node->term = term; //does this send the whole string
    new_node->rightChild = NULL;
    new_node->leftChild = NULL;
    return new_node;
}

// add a new node to the BST with the new_data values, space must be allocated in the
// note: a node of equal data will be inserted to the left
void insert(char *new_data, BSTObj **pBST){
    //case 1: pointer to BST is empty, inserts node
    if((*pBST) == NULL){
        *pBST = makeNode(new_data); //does pointer to string return whole string
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

//might not do anything if passed as a copy
void deleteNode(BSTObj *T){
    printf("in deletenode\n");
    /*if(T == NULL){
        fprintf(stderr, "error; cannot delete null");
        exit(EXIT_FAILURE);
    } else {
    */printf("deleting inhere");
    (T)->leftChild = NULL;
    (T)->rightChild = NULL;
    (T)->term = NULL; 
    printf("deleting here");
    
    (T)->term = NULL;
    free((T)->term);
    free(T);
    //printf("deleting there");
    T = NULL;   
    free(T);
    
}

int deleteItem(char *term_to_delete, BSTObj **pT){
    printf("recursive call\n");//find parent of node to delete
    inorderTraverse(stdout, *pT);
    //printf("**pT is %s, with child %s with child %s", (*pT)->term, (*pT)->leftChild->term, (*pT)->leftChild->rightChild->term);
    BSTObj **parent_of_deleted = malloc(sizeof(BSTObj));
    BSTObj *leftmost = malloc(sizeof(BSTObj));
    BSTObj *parent_of_leftmost = malloc(sizeof(BSTObj));
    parent_of_deleted = (retrieveNode(term_to_delete, pT));
    printf("hi");
    //printf("retrieved/parentofdeleted is %s\n",parent_of_deleted->term);
    if((*parent_of_deleted) == NULL){
        fprintf(stderr, "error: could not locate node with given term. Exiting \n");
        exit(EXIT_FAILURE);
    }
    printf("past that stuff\n");
    int deleteds_on_parents_left = 1;
    BSTObj **to_be_deleted = malloc(sizeof(BSTObj));
    if(strcmp(((*pT)->term),term_to_delete) == 0){
        printf("HEAD PATH\n");
        (*to_be_deleted) = makeNode((*pT)->term);
        (*to_be_deleted)->rightChild = (*pT)->rightChild;
        (*to_be_deleted)->leftChild = (*pT)->leftChild;
    }
    else if((*parent_of_deleted)->leftChild != NULL && strcmp((*parent_of_deleted)->leftChild->term, term_to_delete) == 0 ){
       (*to_be_deleted) = makeNode((*parent_of_deleted)->leftChild->term);
       (*to_be_deleted)->rightChild = (*parent_of_deleted)->leftChild->rightChild;
       (*to_be_deleted)->leftChild = (*parent_of_deleted)->leftChild->leftChild;
    } else {
        (*to_be_deleted) = makeNode((*parent_of_deleted)->rightChild->term);
        (*to_be_deleted)->rightChild = (*parent_of_deleted)->rightChild->rightChild;
        (*to_be_deleted)->leftChild = (*parent_of_deleted)->rightChild->leftChild;
        
        deleteds_on_parents_left = 0;
    }
    
   // printf("tbd is %s\n", to_be_deleted->term);
    //printf("tbd's rchild is %s\n", to_be_deleted->rightChild->term);
    if((*to_be_deleted) == NULL){
        fprintf(stderr, "error: could not locate node with given term. xiting \n");
        exit(EXIT_FAILURE);
    }
    printf("are we here");
    //case: no children
    printf("parent of deleted is %s\n", (*parent_of_deleted)->term);
    if((*to_be_deleted)->leftChild == NULL && (*to_be_deleted)->rightChild == NULL){
        printf("no children");
       /*if(deleteds_on_parents_left == 1){
            parent_of_deleted->leftChild = NULL;
        } else {
            parent_of_deleted->rightChild = NULL;
        }
       */ deleteNode(*to_be_deleted); //might be affected by non double pointer
        printf("done1");
        return TRUE;
    }
 
    //case: 2 children
    else if ((*to_be_deleted)->leftChild != NULL && (*to_be_deleted)->rightChild != NULL){
        printf("in 2 child case\n");
        int leftmost_located = 0;
        //BSTObj *leftmost = malloc(sizeof(BSTObj)); 
        //BSTObj *parent_of_leftmost = malloc(sizeof(BSTObj)); 
        leftmost_located = findLeftmost((*to_be_deleted)->rightChild, &parent_of_leftmost, &leftmost);
        int size = strlen(leftmost->term);
        char *replacement_str = (char*) malloc(sizeof(char)*size+1);
        strcpy(replacement_str,leftmost->term);
        printf("leftmost is %s\n", leftmost->term); 
        //printf("lchild of tbd is %s", to_be_deleted->leftChild->term);
        //printf("rchild of tbd is %s", to_be_deleted->rightChild->term);
        if(leftmost_located != 1){
            fprintf(stderr, "error: could not find left-most node. Exiting\n");
            exit(EXIT_FAILURE);
        }
        printf("entering\n");
        if(deleteds_on_parents_left == 1){
            printf("in left");
            if((*to_be_deleted) != (*parent_of_deleted)){
               (*parent_of_deleted)->leftChild = leftmost;
            }
            deleteItem(replacement_str,pT);
            (*to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1);
            strcpy((*to_be_deleted)->term,replacement_str);
            /*deleteNode(to_be_deleted);
            */
            //parent_of_deleted->leftChild = NULL;

        } else {
             deleteItem(replacement_str,pT);
            //free(to_be_deleted->term);
            //to_be_deleted->term = (char *) malloc(sizeof(char)*(strlen(replacement_str)+1));
           (* to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1);
            strcpy((*to_be_deleted)->term,replacement_str);
            }
        printf("got to post function");
        parent_of_leftmost->leftChild = NULL;
        return TRUE;
    } 
    //case: 1 child
    else { 
        //int leftmost_located = findLeftmost((*to_be_deleted)->rightChild, &parent_of_leftmost, &leftmost);
        
        printf("1 child case\n");
        //int size = strlen(leftmost->term);
        //char *replacement_str = (char *) malloc(sizeof(char)*size+1);
        //subcase: left child of deleted to be moved up
        if((*to_be_deleted)->leftChild != NULL){
            printf("left tree\n");
            if(deleteds_on_parents_left == 1){
                printf("now working\n");
                
                int size = strlen((*to_be_deleted)->leftChild->term);
                        char *replacement_str = (char *) malloc(sizeof(char)*size+1);

                strcpy(replacement_str, (*to_be_deleted)->leftChild->term);
                deleteItem(replacement_str, pT);
                (*to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1);
                strcpy((*to_be_deleted)->term,replacement_str);
                
                
                //parent_of_deleted->leftChild = to_be_deleted->leftChild;
               // to_be_deleted->leftChild = NULL;
                //deleteNode(to_be_deleted->leftChild);
            } else {
              //  printf("its here, gonna recursive w/ %s", replacement_str);
                
                int size = strlen((*to_be_deleted)->leftChild->term);
                        char *replacement_str = (char *) malloc(sizeof(char)*size+1);        
                
                strcpy(replacement_str, (*to_be_deleted)->leftChild->term);
                deleteItem(replacement_str, pT);
                (*to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1); 
                strcpy((*to_be_deleted)->term,replacement_str);
                //parent_of_deleted->rightChild = to_be_deleted->leftChild;
              //  to_be_deleted->leftChild = NULL;
                //deleteNode(to_be_deleted->leftChild);
            }
            return TRUE;
        }
        //subcase: right child of deleted to be moved up
        else {
            if(deleteds_on_parents_left == 1){
                //parent_of_deleted->leftChild = to_be_deleted->rightChild;
                //to_be_deleted->rightChild = NULL;
                //deleteNode(to_be_deleted->rightChild);
                
                int size = strlen((*to_be_deleted)->rightChild->term);
                        char *replacement_str = (char *) malloc(sizeof(char)*size+1);

                strcpy(replacement_str, (*to_be_deleted)->rightChild->term);
                printf("the replacement is %s", replacement_str);
                deleteItem(replacement_str, pT);
                (*to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1);
                strcpy((*to_be_deleted)->term,replacement_str);
            
            } else {
                //parent_of_deleted->rightChild = to_be_deleted->rightChild;
                //to_be_deleted->rightChild = NULL;
                int size = strlen((*to_be_deleted)->rightChild->term);
                        char *replacement_str = (char *) malloc(sizeof(char)*size+1);

                
                strcpy(replacement_str, (*to_be_deleted)->rightChild->term);
                printf("the replacement is %s", replacement_str);
                deleteItem(replacement_str, pT);
                (*to_be_deleted)->term = (char *) malloc(sizeof(char)*strlen(replacement_str)+1);
                strcpy((*to_be_deleted)->term,replacement_str);
            }
            return TRUE;
        }
    }
    return FALSE;
}
//if not found return NULL
BSTObj **retrieveNode(char *term_to_delete, BSTObj **T){
    if((*T)==NULL){
        return NULL;
    } 
    //if head is the found node
    if(strcmp((*T)->term, term_to_delete) == 0) return (T);
    if((*T)->leftChild == NULL){
        //do nothing, just to catch a seg fault
    } else if (strcmp(term_to_delete,(*T)->leftChild->term) == 0){
        return (T);
    } else if ((*T)->rightChild == NULL && (*T)->leftChild != NULL){
        return retrieveNode(term_to_delete, &((*T)->leftChild));
    }
    if((*T)->rightChild == NULL){
        return NULL;
    } else if (strcmp(term_to_delete,(*T)->rightChild->term) == 0){
        return (T);
    } else if((*T)->rightChild != NULL && (*T)->leftChild == NULL){
        return retrieveNode(term_to_delete, &((*T)->rightChild));
    }
    else {
        BSTObj **left_retrieval = retrieveNode(term_to_delete,&((*T)->leftChild));
        BSTObj **right_retrieval = retrieveNode(term_to_delete,&((*T)->rightChild));
        return((left_retrieval != NULL) ? left_retrieval : right_retrieval);
    }
}

int findLeftmost (BSTObj *T, BSTObj **leftmostParent, BSTObj **leftmost) {
    printf("in fleftmost\n");
//if there is another left child, set leftmostParent and find it
    if( T->leftChild != NULL) {
        *leftmostParent = T;
        T = T->leftChild;
        return findLeftmost(T, leftmostParent, leftmost);
    }
    else {
        *leftmost = T;
        return TRUE;
    }
}
