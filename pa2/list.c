//-----------------------------------------------------------------------------
// list.c
//
// Owner:  Ari Iramamesh
// CruzId: 1628897
// Class: 12B
// assignment 2
// 
// Description: implements list.h NodeObj functions: create_new_node(), insert(),  
//          ordered_insert(), delete(), delete_all().
//-----------------------------------------------------------------------------


#include<stdlib.h>
#include<stdio.h>
#include "list.h"

NodeObj * create_new_node (int id){
    NodeObj *new_node = malloc(sizeof(NodeObj));

    if(new_node == NULL){
        fprintf(stderr, "error, couldn't locate memory space for the new node, returning NULL");
        return NULL;
    }

    new_node->value = id;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
} 

void insert(NodeObj **list_head, NodeObj *to_be_inserted){
    //parameter input checking for NULL
    NodeObj *ptr_iterator = *list_head;
    if(to_be_inserted == NULL){
        fprintf(stderr, "bad input, cannot use null pointer to the inserting node\n");
        return(EXIT_FAILURE);
    }

    if(*list_head == NULL){ //inserts at head of list if list is empty
        *list_head = to_be_inserted;
        to_be_inserted->prev = NULL;
        return;
    }


    while(ptr_iterator->next != NULL){ //otherwise seg fault, and have a ptr for head?!!!!, do same for others
        ptr_iterator = ptr_iterator->next;
    }
    ptr_iterator->next = to_be_inserted;
    to_be_inserted->prev = ptr_iterator; //double connect the nodes

    to_be_inserted->next = NULL; //precaution 
}

void ordered_insert(NodeObj **list_head, NodeObj *to_be_inserted){
    //parameter input checking for NULL input
    if(*list_head == NULL){
        *list_head = to_be_inserted;
        to_be_inserted->prev = NULL;
        return;
    }
    if(to_be_inserted == NULL){
        fprintf(stderr, "bad input, cannot use null pointer to the inserting node\n");
        return(EXIT_FAILURE);
    }
    //declarations
    int key_id = to_be_inserted->value; //the value that each node compares its value with
    NodeObj *ptr_iterator = *list_head;

    //iterates through list to find the node whose value is higher than to_be_inserted
    while(ptr_iterator->next != NULL && key_id >= (ptr_iterator->value)){
        ptr_iterator = ptr_iterator->next;
    }
    //special case: to be inserted is last node
    if(ptr_iterator->next == NULL && ptr_iterator->value < key_id){
        ptr_iterator->next = to_be_inserted;
        to_be_inserted->prev = ptr_iterator;
        to_be_inserted->next = NULL;
        return;
    }
    //special case for if inserted node is first in an occupied list
    if(ptr_iterator->prev == NULL){
        ptr_iterator->prev = to_be_inserted;
        to_be_inserted->next = ptr_iterator;
        *list_head = to_be_inserted; //changes where list_head points to inserted node
    //occurs when inserted node is in middle of list
    } else{
        ptr_iterator->prev->next = to_be_inserted; //connect surrounding nodes to inserted node
        to_be_inserted->prev = ptr_iterator->prev;

        to_be_inserted->next = ptr_iterator; //set prev and next for inserted node
        ptr_iterator->prev = to_be_inserted;        
    }
}

/*preconditions: the caller should set *list_head to NULL after delete_all() is called
in order to delete all nodes
                Also, cannot take an NULL input */
void delete_all(NodeObj *list_head){

    NodeObj *head_ptr = list_head;

    //case: list is empty
    if(list_head == NULL){
        fprintf(stderr, "bad input, cannot empty an empty list\n");
        return(EXIT_FAILURE);
    } 
    //case: list only has one node
    if(head_ptr->next == NULL){
        head_ptr->prev = NULL;
        head_ptr->next = NULL;
        head_ptr->value = NULL;
        free(head_ptr);
        return;
    }
    //case: list is occupied, normal
    NodeObj *ptr_iterator = list_head;
    while(ptr_iterator->next != NULL){   
        NodeObj *temp_to_delete = ptr_iterator;
        ptr_iterator = ptr_iterator->next;

        temp_to_delete->prev = NULL;
        temp_to_delete->next = NULL;
        temp_to_delete->value = NULL;
        
        free(temp_to_delete);

    }
    ptr_iterator->next = NULL;
    ptr_iterator->next = NULL;
    ptr_iterator->next = NULL;
    free(ptr_iterator);
}   

//preconditions: cannot receive NULL as input for either list_head or to_be_deleted
void delete(NodeObj **list_head, NodeObj *to_be_deleted){
    //parameter input checking for NULL
    if(list_head == NULL){
        fprintf(stderr, "bad input, cannot delete in an empty list\n");
        return(EXIT_FAILURE);
    }
    
    if(to_be_deleted == NULL){
        fprintf(stderr, "bad input, cannot use null 'pointer to the deleteable node'\n");
        return(EXIT_FAILURE);
    }
    if(*list_head == to_be_deleted){ //if the to be deleted node is the first node in an occupied list
        NodeObj *temp_for_head = *list_head;
        *list_head = (*list_head)->next;
        //set data of the to_be_deleted to NULL
        temp_for_head->prev = NULL; 
        temp_for_head->next = NULL;
        temp_for_head->value = NULL;

        free(temp_for_head);
        (*list_head)->prev = NULL;
        return;
    }

    NodeObj *ptr_iterator = *list_head;
    while(ptr_iterator->next != to_be_deleted){ //iterates till ptr_iterator->next is the deletable node
        if(ptr_iterator->next == NULL){
            fprintf(stderr, "bad input, the node to be deleted doesn't exist in the list");
            return(EXIT_FAILURE);
        }
        ptr_iterator = ptr_iterator->next;
    }
    if(ptr_iterator->next->next != NULL){ //checks if to be deleted isn't last in the list
        ptr_iterator->next = ptr_iterator->next->next; //removes connection to to_be_deleted from list
        ptr_iterator->next->next->prev = ptr_iterator;
    } else{ //when the deletable node is the last node in the list
        ptr_iterator->next = NULL;
    }
    to_be_deleted->prev = NULL;
    to_be_deleted->next = NULL;
    to_be_deleted->value = NULL;
    free(to_be_deleted);

}

