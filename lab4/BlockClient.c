
//-----------------------------------------------------------------------------
// BlockClient.c
// Test client for Block ADT
//-----------------------------------------------------------------------------

#include "Block.h"

int main(int argc, char* argv[]){

  Block blk0, blk1;
  long tmpHash;

  blk0 = newBlock("AB", 49, 0);
  printBlock(stdout, blk0);
  
  printf("get the data in the block 0\n");
  printf("data = %s\n", data(blk0));

 
  tmpHash = hash(blk0);
  printf("block 0 hash = %ld to put into blk 1\n", tmpHash);

  blk1 = newBlock("cats are wild", 49, tmpHash);
  printf("previous hash block 1 = %ld\n", previousHash(blk1));
  printf("about to free block: %p\n", blk0);
  //Block blk = newBlock("AB", 49, 8372879213);
  printBlock(stdout, blk0);
  
  printf("get the data in the block0\n");
  printf("data = %s\n", data(blk0));



  //freeBlockchain(&chain);
  return 0;
}
