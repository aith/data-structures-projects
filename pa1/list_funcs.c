//-----------------------------------------------------------------------------
// list_funcs.c
//
// Owner:  Ari Iramamesh
// CruzId: 1628897
// Class: 12B
// 
// Role: Contains functions that allow linked lists to exist and function.
// Includes: create_new_rider, front_insert, end_insert, ordered_insert, empty,
// delete, and find_next_distance_rider.
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#define MAX_DISTANCE 100000
//MAX_DISTANCE is for the find_next_distance_rider

//prototypes

rider_st* create_new_rider(int id, char *first_name, char *last_name, double
ave_rating, double distance){
    rider_st* new_rider = malloc(sizeof(rider_st));
    new_rider->ID= id;
    new_rider->first_name = first_name;
    new_rider->last_name = last_name;
    new_rider->ave_rating = ave_rating;
    new_rider->distance = distance;
    new_rider->next = NULL;
    
    return new_rider;
}

void front_insert(rider_st **list_head, rider_st *to_be_inserted){ 
    rider_st *after_to_be_inserted = *list_head; //holds the list_head's address for to_be_inserted->next to point to it after being inserted
    *list_head = to_be_inserted;
    to_be_inserted->next = after_to_be_inserted; 
}

void end_insert(rider_st **ptr_to_list_head, rider_st *to_be_inserted){
    rider_st *ptr_current = *ptr_to_list_head; //the iterator ptr
    while((ptr_current->next) != NULL){ //iterate through each node to get to end
        ptr_current = (ptr_current)->next; 
    }
    ptr_current->next = to_be_inserted; //set last's next to address of inserted
    to_be_inserted->next = NULL; //to make sure that the end node is the end
}

void ordered_insert(rider_st **ptr_to_list_head, rider_st *to_be_inserted){
    double distvalue = to_be_inserted->distance; //the distance of to_be_inserted, or the key value for comparison
    rider_st *ptr_iterator = *ptr_to_list_head; 
    rider_st *prev = *ptr_to_list_head; //holds the address of the node 'one behind' the ptr_iterator node

    if (distvalue < (ptr_iterator->distance)){ //checks if to_be_inserted has a lower distance than the front node
        front_insert(ptr_to_list_head, to_be_inserted);
    } else { //if not, then it iterates through the whole list, shifting prev and ptr_iterator up once until a node of higher distance is found
        while((ptr_iterator != NULL) && (ptr_iterator->distance <= distvalue)){ //checks if the currently iterated node exists
            prev = ptr_iterator; //could also set prev to ptr_iterator
            ptr_iterator = ptr_iterator->next;
        
        }

        to_be_inserted->next = ptr_iterator; //the insertion process
        prev->next = to_be_inserted;
        }        
}

//post condition: in order to delete the first node, the caller needs to set the head to NULL after empty() is called
void empty(rider_st *list_head){
    rider_st *ptr_iterator = list_head;
    rider_st *ptr_to_list_head = list_head; //first node freed after rest are deleted

    while(ptr_iterator->next != NULL){
        rider_st * temp_address_to_delete = ptr_iterator->next;
        ptr_iterator->next = temp_address_to_delete->next;
        free(temp_address_to_delete);
    }

    free(ptr_to_list_head);
}

void delete(rider_st **ptr_to_list_head, rider_st *to_be_deleted){
    rider_st * ptr_iterator = *ptr_to_list_head;

    if(ptr_iterator == to_be_deleted){ //checks if first node is the same as to_be_deleted
        *ptr_to_list_head = (*ptr_to_list_head)->next;
        free(to_be_deleted);
        return;
    }

    while((ptr_iterator->next) != NULL){ //iterates through list and compares for deletion                
        if ((ptr_iterator->next) == to_be_deleted){
            rider_st *temp = to_be_deleted->next; //temp holds the next node after the deleted node
            free(to_be_deleted);
            ptr_iterator->next = temp;
            break; 

        }
        ptr_iterator = ptr_iterator->next;
    }
}
//pre condition: that min_distance is <= the highest distance rider, otherwise it'll return the last node 
rider_st find_next_distance_rider(rider_st *list_head, double min_distance){
    double diff = MAX_DISTANCE - 1; //difference between the min_dist and the current closest
    rider_st *ptr_to_next_distance = NULL; //holds the returning rider_st, the answer
    rider_st *ptr_iterator = list_head;
    
    while(ptr_iterator != NULL){ //iterates through list and compares how close the iterated node's distance is from min_distance
        if ((min_distance <= (ptr_iterator->distance)) && (((ptr_iterator->distance) - min_distance) <= diff)) {
            diff = ((ptr_iterator->distance) - min_distance ); //the updated difference value 
            ptr_to_next_distance = ptr_iterator; //the updated node with lowest difference from min_distance
        }
        if (ptr_iterator->next == NULL){
            //if could not find a struct given the parameters, returns last node
            printf("%s", "Error: could not find a rider with given min_distance, returning the last node. \n");
            return(*ptr_iterator);
        }

        ptr_iterator = ptr_iterator->next;   
    
    }        

    return *ptr_to_next_distance;
}
