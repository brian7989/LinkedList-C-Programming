#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

typedef struct crab {
    char *name;
    int crabtitude;
} Crab;

typedef struct list_node
{
    struct list_node* next;
    Crab *data;
} ListNode;


typedef struct list
{
    ListNode *head;
} List;

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check list.c.                                  **
***************************************************/

/* Creating */
List *create_list(void);
ListNode *create_node(Crab*);

/* Copy */
int copy_crab(Crab *, Crab **);
List *copy_list(List *);

/* Adding */
int push_back(List *, ListNode *);

/* Remove */
int remove_node(List *, Crab **, int);

/* Destroy */
void destroy_crab(Crab *);
void destroy(List *);

/* Sort */
int compare_crabtitude(Crab *, Crab *);
int compare_name(Crab *, Crab *);
int swap_nodes(ListNode *, ListNode *, List *);
int sort(List *, int(*compare_func)(Crab *, Crab *));

/* Array */
Crab **list_to_array(List*, int);
#endif
