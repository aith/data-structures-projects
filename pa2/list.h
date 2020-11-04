/* Ari Iramanesh
 * 1628897
 * 12B, Bhatti
 * 
 * Description: defines the NodeObj structure and prototypes its necessary functions.
 */


typedef struct NodeObj{
   int value;
   struct NodeObj* prev;
   struct NodeObj* next;
} NodeObj;


NodeObj * create_new_node (int id);
void insert(NodeObj **list_head, NodeObj *to_be_inserted);
void ordered_insert(NodeObj **list_head, NodeObj *to_be_inserted);
void delete_all(NodeObj *list_head);
void delete(NodeObj **list_head, NodeObj *to_be_deleted);

