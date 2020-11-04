#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dictionary.h"
#define TRUE 1
#define FALSE 0

//study insert and deletes for linked lists, doubly, and binary search tree
//check passing by reference using pointer!!!!
//q's: where do we make the newBucketList. How does it fit into the hashtable? 

bucketList create_new_node(char *str);
unsigned int rotate_left(unsigned int value, int shift);
unsigned int pre_hash(char* input);
int hash(char* key, int tableSize);
void deleteNode(bucketList N);


bucketList create_new_node(char *str){
    if(str == NULL){
        fprintf(stderr, "error, cannot input null data, Exiting\n");
        exit(EXIT_FAILURE);
    }
    //struct bucketListObj *new_node =  (bucketListObj *)sizeof(bucketListObj) + strlen(str)+ 1;
    struct bucketListObj *new_node = malloc(sizeof(bucketListObj) + strlen(str)+ 1);
    if(new_node == NULL){
        fprintf(stderr, "error, couldn't locate memory space for the new node, Exiting\n");
        exit(EXIT_FAILURE);
    }

    //new_node->item = (char *)malloc(sizeof(char)*strlen(str)+1);

    strcpy(new_node->item,str);
    new_node->next = NULL;
    return new_node;
} 
HashTableObj *newHashTable(int size) {
    // error checking code omitted
    // we explicitly allocate space for the fixed size element in HashTableObj,
    // the size element plus the space for the variable size array
    HashTableObj *H = malloc(sizeof(HashTableObj) + sizeof(bucketListObj) * size);
    if(size <= 0){
        printf("error: cannot create hash table of size 0 or lower. Exiting\n");
        exit(EXIT_FAILURE);
    }
    H->size = size;
    for(int i = 0; i<size; i++){
        H->bucket[i] = NULL;
    }
    //needa set buckets to null? to avoid errors

    //do we needa declare an array>
    return H;
}
void deleteHashTable(HashTableObj * H){
    if(H == NULL){
        fprintf(stderr, "error: HashTable is already empty. Exiting");
        exit(EXIT_FAILURE);
    }
    //iterate through each link list and their nodes, freeing space
    for(int i=0; i<=(H->size-1); i++){
        bucketList N = H->bucket[i];
        while(N != NULL){//while(H->bucket[i] != NULL){
            bucketList tobedeleted = N;
            N=N->next;
            deleteNode(tobedeleted); 
            /*bucketList next = H->bucket[i]->next;
            deleteNode(H->bucket[i]);
            H->bucket[i] = next;*/
        }
        H->bucket[i] = NULL;
        N = NULL; 
    }
    //H->size = NULL;
    free(H);
    H = NULL;
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
    int sizeInBits = 8*sizeof(unsigned int);
    shift = shift & (sizeInBits - 1);
    if ( shift == 0 )
    return value;
    return (value << shift) | (value >> (sizeInBits - shift));
}
// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
    unsigned int result = 0xBAE86554;
    while (*input) {
    result ^= *input++;
    result = rotate_left(result, 5);
}
return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key, int tableSize){
    return pre_hash(key)%tableSize;
}

bool member(HashTableObj *H, char *str){
    if(H == NULL){
        fprintf(stderr, "error: hash table is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    if(str == NULL){
        fprintf(stderr, "error: cannot search for an entry with an empty string\n");
        return FALSE;
    }
    int hvalue = hash(str, H->size);
    bucketList iterator = H->bucket[hvalue]; //check if it needs malloc if its null
    while(iterator != NULL){
        if(strcmp(iterator->item, str) == 0){
            return TRUE;
        }
        iterator = iterator->next;
    }
    fprintf(stderr, "could not locate given member\n");
    return FALSE;
}

void insert(HashTableObj *H, char *str){
    if(H == NULL){
        fprintf(stderr, "error: hash table is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    if(str == NULL){
        fprintf(stderr, "error: string is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    int hvalue = hash(str, H->size);
    bucketList newnode = create_new_node(str); 
    newnode->next = H->bucket[hvalue]; //put newnode at the front(append), u may need to malloc H->bucket[hvalue]
    H->bucket[hvalue] = newnode;
}

//the code for delete/print/and member are all similar because they all traverse through the list
bool delete(HashTableObj *H, char *str) {
    if(H == NULL){
        fprintf(stderr, "error: hash table is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    if(str == NULL){
        fprintf(stderr, "error: string is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    int hvalue = hash(str, H->size); //search for hash progressively
    bucketList N = H->bucket[hvalue];
    //check if head is to be deleted and otherwise list is empty
    if(strcmp(N->item, str) == 0 && N->next == NULL){
        deleteNode(N);
        H->bucket[hvalue] = NULL;
        return TRUE;
    }
    //check if head is to be deleted and list is occupied elsewhere
    if (strcmp(N->item, str) == 0){
        H->bucket[hvalue] = H->bucket[hvalue]->next;
        deleteNode(N);
        return TRUE;
    }
    
    //check non-head rest of list
    while(N->next != NULL){
        if(strcmp(N->next->item,str) == 0){
            //at end
            if(N->next->next == NULL){
                deleteNode(N->next);
                N->next = NULL;
                return TRUE;
            }
            //in middle
            else {
                bucketList deleteds_next = N->next->next; //potential error/leak
                deleteNode(N->next);
                N->next = deleteds_next;
                return TRUE;
                //deleteds_next = NULL; //precaution?
            }
        } else {
            N = N->next;
        }
    }
    fprintf(stderr, "could not locate the node to be deleted\n");
    return FALSE;    
}

void deleteNode(bucketList N){
    if(N == NULL){
       fprintf(stderr, "error: cannot delete NULL Node\n");
       exit(EXIT_FAILURE); 
    }
    
    N->next = NULL;
    //free(N->item);
    //N->item = NULL;
    free(N);
    N = NULL;
}

void printHashTable(FILE *out, HashTableObj *H){
    if(H == NULL){
        fprintf(stderr, "error: hash table is set to NULL. exiting\n");
        exit(EXIT_FAILURE);
    }
    if(out == NULL){
        fprintf(stderr, "error: cannot locate output. exiting\n");
        exit(EXIT_FAILURE);
    }
    fprintf(out, "Hash Table contents\n");
    for(int i=0; i<=(H->size)-1; i++){
        bucketList N = H->bucket[i];
        fprintf(out, "bucket #%i\n", i);
        while(N != NULL){
            fprintf(out, "    bucket list item = %s\n", N->item);
            N=N->next;
        }
    }
}