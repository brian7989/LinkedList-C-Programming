// Header files
#include "list.h"
#include <stdio.h>

/** create_node
  *
  * Helper function that creates a struct list_node by allocating memory for it on the heap.
  *
  * @param data a void pointer to data the user wants to store in the struct list
  * @return a struct list_node
  */
ListNode *create_node(Crab *data)
{
    ListNode* node;
    node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL) {
      return NULL;
    }
    node -> data = data;
    node -> next = NULL;
    return node;
}

/** create_list
  *
  * Creates a struct list by allocating memory for it on the heap.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
List *create_list(void)
{
    List* list;
    list = (List*)malloc(sizeof(List));
    if (list == NULL) {
      return NULL;
    }
    list -> head = NULL;
    return list;
}

/** push_back
  *
  * Adds the ListNode to the back of the list
  *
  * @param listToAddTo a pointer to the List structure
  * @param node the node to add to the list
  * @return 0 if the list or if the node is null otherwise return 1
  */
int push_back(List *listToAddTo, ListNode *node)
{
    UNUSED_PARAMETER(listToAddTo);
    UNUSED_PARAMETER(node);
    if (listToAddTo == NULL) {
      return 0;
    }
    if (node == NULL) {
      return 0;
    }
    if (listToAddTo->head == NULL) {
      listToAddTo -> head = node;
    } else {
      ListNode* curNode = listToAddTo->head;
      while (curNode-> next != NULL) {
        curNode = curNode->next;
      }
      curNode->next = node;
      return 1;

    }
    return 0;
}

/** remove_node
  *
  * Remove the first node with which the crab data's crabtitude is the specified crabbiness.
  *
  * @param listToAddTo a pointer to the struct list structure
  * @param dataOut a double pointer to return the Crab data that is being removed from the list
  * @param crabbiness the specific crabtitude
  * @return 0 if the struct list is NULL, there is no crab with the specified crabbiness,
  *         or the dataOut is NULL
  *         otherwise return 1
  */
int remove_node(List *listToRemoveFrom, Crab **dataOut, int crabbiness)
{
  UNUSED_PARAMETER(crabbiness);
    if (dataOut == NULL) {
      return 0;
    }
    if (listToRemoveFrom == NULL) {
      dataOut = NULL;
      return 0;
    }
    ListNode* curNode = listToRemoveFrom -> head; //head node
    if (curNode->data->crabtitude == crabbiness) {  //first one?
      if (curNode -> next == NULL) {
          *dataOut = curNode->data;
          free(curNode);
          listToRemoveFrom->head= NULL;
          return 1;
        }
    }
    while ((curNode->next != NULL)) {
      if (curNode->next->data->crabtitude == crabbiness) {
        if (curNode->next-> next == NULL) {
          *dataOut = curNode->next->data;
          free(curNode->next);
          curNode -> next = NULL;
          return 1;
        } else {
          *dataOut = curNode->next->data;
          ListNode* resultNode = curNode->next;
          curNode->next = resultNode->next;
          free(resultNode);
          return 1;
        }
      }
      curNode = curNode->next;
    }
    return 0;
}

/** destroy_crab
  *
  * Destroys all data in the crab. Make sure to free any crab attributes that have memory
  * allocated for them.
  *
  * @param crab The crab to destroy
*/
void destroy_crab(Crab *crab) {
    UNUSED_PARAMETER(crab);
    if (crab == NULL) {
      return;
    }
    Crab* krab = (Crab*) crab;
    free(krab -> name);
    free(krab);
}

/** destroy
  *
  * Destroys the list.
  *
  * @param listToEmpty a pointer to the struct list structure
  */
void destroy(List *listToEmpty)
{
    if (listToEmpty == NULL) {
      return;
    }
    ListNode* curNode = listToEmpty->head;
    while (curNode != NULL) {
      ListNode* deletedNode = curNode;
      destroy_crab(curNode->data);
      curNode = curNode->next;
      free(deletedNode);
    }
    free(curNode);
    listToEmpty -> head = NULL;
    free(listToEmpty);
}

/** copy_crab
  *
  * A function that will deep copy the crab and all its attributes.
  *
  * @param crab_to_copy The crab to copy
  * @param copied_crab A double pointer used to return the copied crab
  * @return 0 if malloc fails, crab_to_copy is null, or copied_crab is null
  *         1 otherwise
*/
int copy_crab(Crab *crab_to_copy, Crab **copied_crab) {
    UNUSED_PARAMETER(crab_to_copy);
    UNUSED_PARAMETER(copied_crab);
    if (crab_to_copy == NULL || copied_crab == NULL) {
      return 0;
    }

    char *nameString = crab_to_copy->name;
    int crabtitudeNumber = crab_to_copy->crabtitude;
    Crab* result = (Crab*) malloc(sizeof(Crab));
    if (result == NULL) {
      free(result);
      return 0;
    }
    result->name = malloc((strlen(nameString)+1));
    if(result -> name == NULL) {
      free(result->name);
      free(result);
      return 0;
    }
    strcpy(result->name, nameString);
    result->crabtitude = crabtitudeNumber;
    *copied_crab = result;
    return 1;
    
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
List *copy_list(List *listToCopy)
{
    if (listToCopy == NULL || listToCopy->head == NULL) {
      return NULL;
    }
    List* copiedList = (List*)malloc(sizeof(List));
    if (copiedList == NULL) {
      destroy(copiedList);
      return NULL;
    }
    copiedList ->head = NULL;
    ListNode* desNode = (ListNode*)malloc(sizeof(ListNode));
    if (desNode == NULL) {
      free(desNode);
      destroy(copiedList);
      return NULL;
    }
    desNode -> next = NULL;
    desNode -> data = NULL;
    copiedList -> head = desNode;
    ListNode* curNode = listToCopy->head;
    if (copy_crab(curNode -> data, &(desNode -> data)) == 0){
        destroy(copiedList);
        return NULL;
    }
    while (curNode->next != NULL) {
      ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
      if (newNode == NULL) {
        free(newNode);
        destroy(copiedList);
      }
      newNode ->next =NULL;
      newNode ->data = NULL;
      desNode -> next = newNode;
      curNode = curNode->next;
      desNode = desNode -> next;
      if (copy_crab(curNode -> data, &(desNode -> data)) == 0){
        destroy(copiedList);
      return NULL;
      }
    }
    return copiedList;
}

/** compare_crabtitude
 *
 * This method compares the crabtitudes of two crabs
 *
 * @param a A crab
 * @param b Another crab
 * @return >0 if crab a's crabtitude > crab b's crabtitude
 *          0 if crab a's crabtitude = crab b's crabtitude
 *         <0 if crab a's crabtitude < crab b's crabtitude
 **/
int compare_crabtitude(Crab *a, Crab *b) {
    UNUSED_PARAMETER(a);
    UNUSED_PARAMETER(b);
    if ((a == NULL) && (b!= NULL)) {
      return 1;
    }
    if ((a != NULL) && (b == NULL)) {
      return -1;
    }
    if ((a == NULL) && (b == NULL)) {
      return 0;
    }
    if (a->crabtitude > b->crabtitude) {
      return 1;
    } else if (a->crabtitude == b->crabtitude) {
      return 0;
    } else {
      return -1;
    }
}

/** compare_name
 *
 * This method compares the name of two crabs
 *
 * @param a A crab
 * @param b Another crab
 * @return >0 if crab a's name > crab b's name
 *          0 if crab a's name = crab b's name
 *         <0 if crab a's name < crab b's name
 **/
int compare_name(Crab *a, Crab *b) {
    UNUSED_PARAMETER(a);
    UNUSED_PARAMETER(b);
    if ((a == NULL) && (b!= NULL)) {
      return 1;
    }
    if ((a != NULL) && (b == NULL)) {
      return -1;
    }
    if ((a == NULL) && (b == NULL)) {
      return 0;
    }
    if (strcmp(a->name, b->name) > 0) {
      return 1;
    }
    if (strcmp(a->name, b->name) == 0) {
      return 0;
    }
    if (strcmp(a->name, b->name) < 0) {
      return -1;
    }
    return 0;
}

/** swap_nodes
 *
 * This method swaps two nodes in place.
 *
 * @param node_a A node to swap
 * @param node_b The other node to swap
 * @param list The list within which the nodes will be swapped
 * @return 0 if any of the parameters are null or node_a = node_b
 *         1 on success
**/
int swap_nodes(ListNode *node_a, ListNode *node_b, List *list) {
    UNUSED_PARAMETER(node_a);
    UNUSED_PARAMETER(node_b);
    UNUSED_PARAMETER(list);
    if (node_a == NULL || node_b == NULL || list == NULL) {
      return 0;
    }
    ListNode *prevX = NULL;
    ListNode *currX = list -> head;
    
    while (currX && currX != node_a) {
        prevX = currX;
        currX = currX -> next;
    }
    
    ListNode *prevY = NULL;
    ListNode *currY = list -> head;
    
    while (currY && currY != node_b) {
        prevY = currY;
        currY = currY -> next;
    }
    
    if (currX == NULL || currY == NULL) {
        return 0;
    }
    
    if (prevX != NULL) {
        prevX->next = currY;
    } else {
        list->head = currY;
    }
    
    if (prevY != NULL) {
        prevY->next = currX;
    } else {
        list->head = currX;
    }
    // Swap next pointers
    ListNode *temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
    
    return 1;
}

/** sort
 *
 * A function to sort the nodes in ascending order (in place) using the comparator function passed in.
 *
 * @param list The list to sort
 * @param compare_func A function pointer that denotes which compare method (written above) will be utilized.
 * @return 0 if list is null, the list is empty, or compare_func is null
 *         1 on success
*/
int sort(List *list, int (*compare_func)(Crab *a, Crab *b)) {
    UNUSED_PARAMETER(list);
    UNUSED_PARAMETER(compare_func);
    if (list == NULL || compare_func == NULL)
        return 0;
    if (list->head == NULL)
        return 0;
    ListNode *temp = NULL;
    ListNode *node = list->head;
    while(node != NULL) {
        temp = node;
        while (temp->next !=NULL) {
            ListNode *save = temp->next;
            if (compare_func(temp->data, temp->next->data) > 0) {
                swap_nodes(temp, temp->next, list);
            }
            temp = save;
        }
        node = node->next;
    }
    return 1;
}

/** list_to_array
 *
 * This function will create and utilize a new structure to represent our crabs.
 *
 * @param list The linked list to be converted to an array
 * @param size The amount of crabs in the list
 * @return NULL if list is null, the list is empty, or their is a malloc failure
 *         An array to crab pointers otherwise
*/
Crab **list_to_array(List *list, int size) {
    UNUSED_PARAMETER(list);
    UNUSED_PARAMETER(size);
    if (list == NULL || size == 0) {
      return NULL;
    }
    Crab** crabArray = (Crab**)malloc(sizeof(Crab*)*size);
    if (crabArray == NULL) {
      free(crabArray);
        return NULL;
    }
    ListNode *temp = list->head;
    ListNode *des = list->head;
    int i = 0;
    while (temp != NULL) {
        crabArray[i] = (temp->data);
        i++;
        temp = temp->next;
        free(des);
        des = temp;
    }
    free(list);
    return crabArray;
}

