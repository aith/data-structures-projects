/* file: BlockchainClient.c
Ari Iramanesh
id: 1628897
class: 12M
lab4

desc: demonstrates basic functionality of the Blockchain system using its functions defined in
      Blockchain.c

*/

//-----------------------------------------------------------------------------
// BlockchainClient.c
// Test client for Blockchain ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Blockchain.h"

//////// add your own tests here /////////////


int main(int argc, char* argv[]){

  Blockchain chain = newBlockchain();

  char hackable[] = "one";
  printf("putting in first block = %d\n", append(chain, hackable));
  printBlockchain(stdout, chain);

  printf("putting in second block = %d\n", append(chain, "two"));
  printBlockchain(stdout, chain);

  printf("putting in third block %d\n", append(chain, "three"));

  printf("how many total blocks now? = %d\n", size(chain));

  printBlockchain(stdout, chain);
  //freeBlockchain(chain);
  //chain = NULL;

  printf("find block 2\n");
  Block b =  get(chain, 2);
  printBlock(stdout,b);
 
  //printf("remove last block and print out\n");
  //removeLast(chain);
  //printBlockchain(stdout, chain);

  printf("valid = %d\n", valid(chain));


  //could use printBlockChain() here but want to explicitly test printBlock()
  printf("printing each block through block print calls \n");
  for (int i = 0; i < size(chain); i++) {
    printBlock(stdout,get(chain, i));
  }

  printf("about to remove the last block\n");

  removeLast(chain);
  printf("removed last block\n");
  printBlockchain(stdout, chain);

  // now break the chain
  b = get(chain, 0);
  char* value =  data(b);
  *value = (*value)+1; // change a value in the first block
   //attempt to append to an invalid chain
  printf("putting in block should have 3 in the chain, %d\n", append(chain, "five"));
  printf("after appending a 3rd element with name five\n");
  // just won't be able to invalidate it
  printf("after append and bad chain valid = %d\n", valid(chain));
  printBlockchain(stdout, chain);

  return 0;
}
