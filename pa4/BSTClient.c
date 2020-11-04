

//---------------------------------------------------------------------
// BSTClient.c
// Test client for Binary Search Tree ADT
// 
// This is just an example, you will be doing a lot more tests!
//---------------------------------------------------------------------

#include "stdio.h"
#include "BST.h"

int main(int argc, char* argv[]){

    BSTObj  *T;
    
    T = NULL;

    printf("inserting a lot of nodes to build a tree \n");
    insert("cat", &T);
    insert("rat", &T);
    insert("bat", &T);
    insert("crow", &T);
    insert("dog", &T);
    //insert("dan", &T);
   // insert("dtsh", &T);
    //insert("fox", &T);
    insert("aaz", &T);
    insert("zoo", &T);
    insert("zaa", &T);
    insert("chive", &T);
    insert("churn", &T);
    insert("zab", &T);
    //insert("zac", &T);
    
    printf("done\n");
    //delete test
    /*printf("no dtsh\n");
    deleteItem("dtsh",&T);
    inorderTraverse(stdout, T);
    printf("no bat\n");
    deleteItem("bat",&T);
    inorderTraverse(stdout, T);
    */
    //printf("not fox\n");
    //deleteItem("fox", &T);
    //inorderTraverse(stdout, T);

   /* printf("no rat\n");
    deleteItem("rat", &T);
   */ 
    inorderTraverse(stdout, T);

    printf("no rat");
    deleteItem("rat", &T);
    inorderTraverse(stdout, T);

  /*  printf("no cat");
    deleteItem("cat", &T);
    inorderTraverse(stdout, T);
*/
    /*
    printf("no 
    printf("inorder traverse == \n");
    inorderTraverse(stdout, T);
    printf("\npreorder traverse == \n");
    preorderTraverse(stdout, T);
    printf("\npostorder traverse == \n");
    postorderTraverse(stdout, T);
    printf("\ninorder leaves == \n");
    inorderLeaves(stdout, T);
    int istrue = find("aaz", T);
    printf("\nfind aaz? %i \n", istrue);
    istrue = find("cat", T);
    printf("find cat? %i \n", istrue);
    istrue = find("dog", T);
    printf("find dog? %i \n", istrue);
    istrue = find("zoo", T);
    printf("find zoo? %i \n", istrue);
    istrue = find("nahhg", T);
    printf("find nahhg? %i \n", istrue);

    BSTObj *cpy = copyTree(T);
    printf("mem add of original: %p\n", T);
    printf("mem add of copy: %p\n", cpy);
    printf("printing cpy\n");
    inorderTraverse(stdout, cpy);

    makeEmpty(&T);
    printf("\nprinting T\n");
    inorderTraverse(stdout, T);
    printf("\nprinting cpy\n");
    inorderTraverse(stdout, cpy);
    int ht = treeHeight(cpy, 0);
    printf("\n cpy's height is %i\n", ht);
    
  return 0; */
}
