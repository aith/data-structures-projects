/* file: Block.c
Ari Iramanesh
id: 1628897
class: 12M
lab4

desc: implements the BlockObj structure and its functions: newBlock(),freeBlock(),data(),previousHash()
        hash(),printBlock()

*/

//double check freeBlock double circuit thing
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Block.h"
#include<assert.h>

#define STRING_MAX 100

typedef struct BlockObj{
    char data[STRING_MAX];
    int id;
    long hash;

} BlockObj;

//precondition: hash and id must not be NULL. An empty data entry is legal
Block newBlock(char* data, int id, long hash){
    Block new_block = malloc(sizeof(BlockObj));
    if(new_block == NULL){
        fprintf(stderr, "error: could not allocate space for a new block. Exiting");
        exit(EXIT_FAILURE);
    }

    /*if(hash == NULL || id == NULL){
        fprintf(stderr, "error: c cannot create new block with a NULL hash or id. Exiting\n");
        exit(EXIT_FAILURE);
    }
    if(data == ""){
        fprintf(stderr, "errror: c cannot create new block with data as empty. Exiting\n");
        exit(EXIT_FAILURE);
    }*/
    strcpy(new_block->data, data); //REMEMBER THIS
    new_block->id = id;
    new_block->hash = hash;
    return new_block;
}

// destructor for the Block type
void freeBlock(Block B){
    if( B!=NULL) { // && (*B)!=NULL){
        free(B);  //removed * from next 2 lines
        B = NULL;
    }
}

// return a pointer to this block's data.
// It would probably be better to return a copy to avoid, easy erroneous manipulation of blocks,
// but for demonstration purposes we are going to expose the actual block data.
char* data(Block B){
    return B->data;
}

// return the stored previousHash from this block
long previousHash(Block B){
    return B->hash;
}

int sum(const char *s) { return *s == 0 ? 0 : (int)(*s) + (int)sum(s + 1); };

// recompute the hash value for this block
long hash(Block B){
    return (long)((int)(sum(B->data)) + B->id + B->hash);
}

// print the block id and data
// (NOTE: for debugging purposes you may want to have it also print the hash and previousHash values during development.)
void printBlock(FILE* out, Block B){
    if( B==NULL ){
        fprintf(stderr, "Block Error: printBlock() called on NULL Block reference\n");
        exit(EXIT_FAILURE);
    }
    if( out==NULL ){
        fprintf(stderr, "Block Error: printBlockchain() called on NULL output stream\n");
        exit(EXIT_FAILURE);
    }
    fprintf(out, "%i:%s\n", B->id, B->data); //does this work
    
}
