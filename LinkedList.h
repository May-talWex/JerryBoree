#ifndef LinkedList_H
#define LinkedList_H
#include "Defs.h"

typedef struct linkedList_t *linkedList;

linkedList createLinkedList(CopyFunction copyF, FreeFunction freeF, EqualFunction equalF, PrintFunction printF);
status destroyList(linkedList head);
status appendNode(linkedList head, Element val);
status deleteNode(linkedList head, Element val);
status displayList(linkedList list);
Element getDataByIndex(linkedList head, int index);
int getLengthList(linkedList head);
Element searchByKeyInList(linkedList head, Element key);

#endif /* LinkedList_H */
