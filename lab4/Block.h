/* file: Block.h
Ari Iramanesh 
id: 1628897
class: 12M
lab4

desc: typedefs BlockObj as Block and prototypes Block functions

*/

//-----------------------------------------------------------------------------
// Block.h
// Header file for the Block ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#ifndef _BLOCK_H_INCLUDE_
#define _BLOCK_H_INCLUDE_

// Exported reference type
typedef struct BlockObj* Block;

// constructor for the Block type, create the space for the data, make a copy!
Block newBlock(char* data, int id, long hash);

// destructor for the Block type
void freeBlock(Block B);

// return a pointer to this block's data.
// It would probably be better to return a copy to avoid, easy erroneous manipulation of blocks,
// but for demonstration purposes we are going to expose the actual block data.
char* data(Block B);

// return the stored previousHash from this block
long previousHash(Block B);

// recomute the hash value for this block
long hash(Block B);

// print the block id and data
// (NOTE: for debugging purposes you may want to have it also print the hash and previousHash values during development.)
void printBlock(FILE* out, Block B);

#endif
