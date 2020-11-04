/* file: Blockchain.c
Ari Iramanesh
id: 1628897
class: 12M
lab4

desc: implements BlockchainObj struct and its functions: newBlockchain() freeBlockchain(), append(),
        size(), get(), valid(), removeLast(), printBlockchain()

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "Blockchain.h"


#define MAX 1000

typedef struct BlockchainObj{
    Block chain[MAX];
    int block_count;
} BlockchainObj;

// constructor for the Blockchain type
Blockchain newBlockchain(){
    Blockchain new_Blockchain = malloc(sizeof(Blockchain));
    assert(new_Blockchain != NULL);
    new_Blockchain->block_count = 0; //important
    return new_Blockchain;
}

// destructor for the Blockchain type
void freeBlockchain(Blockchain B){
    for(int i=0; i<(B->block_count);i++){
        free(B->chain[i]);
        B->chain[i] = NULL;
    }
    if( B!=NULL){ //same as Block.c removal
        free(B);
        B = NULL;
    }
}

// append a new block to the chain with the data specified in the new block
// return the size of the block chain if successful and 0 otherwise
int append(Blockchain B, char* data){
    if( B==NULL ){
        fprintf(stderr, "Blockchain Error: append() called on NULL Blockchain reference\n");
        return 0;
    }
    if( data==NULL ){
        fprintf(stderr, "Blockchain Error: append() called on NULL data value\n");
        return 0;
    }
    //case 1: blockchain has no blocks
    if(B->block_count == 0){
        B->chain[(B->block_count)] = newBlock(data, (B->block_count), 0);
    } 
    //case 2: blockchain has blocks
    else {
        B->chain[(B->block_count)] = newBlock(data, (B->block_count), hash(B->chain[(B->block_count) - 1]));
    }
    return ++(B->block_count);
}

// return the number of blocks in this chain
int size(Blockchain B){
    if( B==NULL ){
        fprintf(stderr, "Blockchain Error: size() called on NULL Blockchain reference\n");
        exit(EXIT_FAILURE);
    }
    return B->block_count;
}

// return the block at index idx in the chain
Block get(Blockchain B, int idx){
    if( B==NULL ){
        fprintf(stderr, "Blockchain Error: get() called on NULL Blockchain reference\n");
        exit(EXIT_FAILURE);
    }
    if( idx>MAX || idx<0){
        fprintf(stderr, "Blockchain Error: get() called on NULL index value\n");
        exit(EXIT_FAILURE);
    }
    return B->chain[idx];
}

// check if this is a valid chain by checking the stored previousHash values in each block
// return 1 if valid, 0 otherwise
int valid(Blockchain B){
    int is_valid = 1;
    int i = 1;
    if( B==NULL ){
        fprintf(stderr, "Blockchain Error: valid() called on NULL Blockchain reference\n");
        exit(EXIT_FAILURE);
    }
    //case 1: first block doesn't have a hash value of 0, return false
    if(previousHash(B->chain[0]) != 0){
        is_valid = 0;
        return is_valid;
    }
    //iterates through list and checks if each hash is valid
    while(i < (B->block_count)){
        if(previousHash(B->chain[i]) != hash(B->chain[i-1])){ //can't do B->chain[i]->hash bc its hidden
            is_valid = 0;
            break;
        }
        i++;
    }
    return is_valid;
}   

// shorten the chain by revmoing the last block
// do nothing if the chain is already empty
void removeLast(Blockchain B){
    //case 1: blockchain is empty, return nothing
    if (B == NULL){
        return;
    } 
    //case 2: free last block's space in an occupied list
    else {
        strcpy(data(B->chain[(B->block_count) - 1]), "");
        free(B->chain[(B->block_count) - 1]);
        --(B->block_count);
    }

}

// print the chain
void printBlockchain(FILE* out, Blockchain B){
    int i = 0;
    if( B==NULL ){
        fprintf(stderr, "Block Error: printBlockchain() called on NULL Blockchain reference\n");
        exit(EXIT_FAILURE);
    }
    if( out==NULL ){
        fprintf(stderr, "Block Error: printBlockchain() called on NULL output stream\n");
        exit(EXIT_FAILURE);
    }
    while(i < (B->block_count)){ //uses data to see if block exists, is this right? or can u do without the data part
        printBlock(out, B->chain[i]);
        i++;
    }
}
