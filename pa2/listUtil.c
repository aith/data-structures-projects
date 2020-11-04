
/* Ari Iramanesh
 * 1628897
 * 12B, Bhatti
 * assignment2
 *
 * Description
 * This is a set of utility routines to print doubly linked lists
 * YOU SHOULD ADD MORE FUNCTIONS TO THIS FILE, REMEMBER DOUBLY LINKED LIST CAN BE TRAVERSED
 * IN BOTH DIRECTIONS
 *
 * Functions:
 *     print_node     	- prints the values of a single node to stdout
 *     traverse_print   - walk through the list and print out each node to stdout
 *
 * Author
 *     Nina Bhatti
 *
 * Date
 *    Oct 16, 2018
 *
 * Notes
 * list printing routines to show the contents of linked list of structures.
 * prints to stdout
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "listUtil.h"


/*
 * print an individual node, the value and the pointers.
 */
void
print_node(node)

    NodeObj *node;

{

    if (node == NULL ) {
        printf("print_node: no node passed for printing\n");
    }
    else {
        /* for testing using file diff you will likely want to remove ptr value printing */
        printf("Node: value=%d,  node_ptr = %p, prev=%p, next=%p \n",
        node->value, node, node->prev,  node->next);
    }
}

/*
 * traverse list and print each individual node, the value and the pointers.
 */

void
traverse_print(list_head)
    NodeObj *list_head;

{

    NodeObj *ptr=NULL;    /* show other way to do this */

    ptr = list_head;

    printf("\nList traversal printing all elements of the list \n");
    /* walk down the list printing until we have no more elements */

    while (ptr != NULL) {
        print_node(ptr);
        ptr = ptr->next;        /* what if we don't have this statement? */
    }
    printf("List printing done, end.\n");
}

