/* file: DictionaryTest.c
Ari Iramanesh
id: 1628897
class: 12B
assignment 5

desc: Tests out the Dictionary's functionality

*/

#include "Dictionary.h"
/*
 * test the hash table really simple tests, you will want to make
 * many more tests.
 */

int
main () {
 


    HashTableObj  *H;

    // you can make this hash table size anything you like that is a prime but the example
    // results will be different based on the has table size.
    H = newHashTable(5);

    insert(H, "dog");
    insert(H, "cat");
    insert(H, "frog");
    insert(H, "banana");
    insert(H, "apple");
    insert(H, "pear");

    int boolean = member(H, "");
    if(boolean == 1){   
        printf("this is wrong\n");
    } else printf("right\n");

    delete(H, "pear");
    delete(H, "dog");
    delete(H, "frog");
    printHashTable(stdout, H);

	deleteHashTable(H);
	
    //printHashTable(stdout, H); //this works but causes errors?

    return 0; 
}

