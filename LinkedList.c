#include "LinkedList.h"


struct node{ //node structure definition for linked list
    void* element;
    struct node *next;
};

struct linkedList_t{ //linked list structure definition
    struct node* head;
    int size;
    CopyFunction copyFunc;
    FreeFunction freeFunc;
    EqualFunction equalFunc;
    PrintFunction printFunc;
};

//creates a new linked list
linkedList createLinkedList(CopyFunction copyF, FreeFunction freeF, EqualFunction equalF, PrintFunction printF) {
    if (copyF == NULL || freeF == NULL || equalF == NULL || printF == NULL) {
        return NULL;
    }
    linkedList newList = (linkedList) malloc(sizeof(struct linkedList_t));
    if (newList == NULL) {
        printf("Memory Problem\n");
        free(newList);
        exit(1);
    }
    newList->head = NULL;
    newList->size = 0;
    newList->copyFunc = copyF;
    newList->freeFunc = freeF;
    newList->equalFunc = equalF;
    newList->printFunc = printF;
    return newList;
};

//destroys a linked list
status destroyList(linkedList list) {
    struct node* next = NULL;
    if (list == NULL) {
        free(list);
        return failure;
    }
    struct node* last = list->head;
    while (last != NULL) {
        next = last->next;
        list->freeFunc(last->element);
        free(last);
        last = next;
    }
    free(list);
    return success;
}



//adds an element to the linked list
status appendNode(linkedList list, Element val) {
    struct node* temp;
    struct node* newNode;
    if (list == NULL || val == NULL) {
        return failure;
    }
    Element newElement = list->copyFunc(val);
    if (list->size == 0) {
        newNode = (struct node*) malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Memory Problem\n");
            free(newNode);
            exit(1);
        }
        list->head = (struct node *) newNode;
        newNode->element = newElement;
        newNode->next = NULL;
    }
    else{
        temp = (struct node *) list->head;
        while (temp->next != NULL) {
            temp = (struct node *) temp->next;
        }
        temp->next = (struct node *) malloc(sizeof(struct node));
        if (temp->next == NULL) {
            printf("Memory Problem\n");
            exit(1);
        }
        temp->next->element = newElement;
        temp->next->next = NULL;
    }
    list->size++;
    return success;
}

//removes a node from the linked list
status deleteNode(linkedList list, Element val) {
    struct node* temp;
    struct node* prev;
    if (list == NULL || val == NULL || list->equalFunc == NULL) {
        return failure;
    }
    temp = list->head;
    if (list->equalFunc(temp->element, val)) {
        list->head = temp->next;
        list->freeFunc(temp->element);
        free(temp);
        list->size--;
        return failure;
    }
    while (temp != NULL && !list->equalFunc(temp->element, val)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return failure;;
    }
    prev->next = temp->next;
    list->freeFunc(temp->element);
    free(temp);
    list->size--;
    return success;

}

status displayList(linkedList list) {
    struct node* temp;
    if (list == NULL) {
        return failure;
    }
    temp = list->head;
    while (temp != NULL) {
        list->printFunc(temp->element);
        temp = temp->next;
    }
    return success;
}

Element getDataByIndex(linkedList list, int index) {
    struct node* temp;
    if (list == NULL) {
        return NULL;
    }
    if (index < 1 || index > list->size) {
        return NULL;
    }
    temp = list->head;
    int i = 1;
    while (i < index) {
        temp = temp->next;
        i++;
    }
    return temp->element;
}

int getLengthList(linkedList list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}


Element searchByKeyInList(linkedList list, Element keyPart) {
    if (list == NULL || keyPart == NULL || list->equalFunc == NULL) {
        return NULL;
    }
    struct node* node;
    node = list->head;
    while (node != NULL) {
        if (list->equalFunc(node->element, keyPart)) {
            return node->element;
        }
        node = node->next;
    }
    return NULL;
}
