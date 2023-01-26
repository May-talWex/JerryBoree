#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"

struct MultiValueHashTable_t { //MultiValueHash struct decleration
    hashTable table;
    FreeFunction freeFunc;
    CopyFunction copyFunc;
    PrintFunction printFunc;
    EqualFunction equalFunc;
};

status freeList(Element element){ //free list function
    if (element == NULL) return failure;
    linkedList list = (linkedList)element;
    return destroyList(list);
}

status printList(Element element){ //print list function
    if (element == NULL) return failure;
    linkedList list = (linkedList)element;
    return displayList(list);
}

//Create a new MultiValueHashTable
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL || transformIntoNumber == NULL || hashNumber <= 0) {
        return NULL;
    }
    MultiValueHashTable newHash = (MultiValueHashTable)malloc(sizeof(struct MultiValueHashTable_t));
    if (newHash == NULL) {
        printf("Memory Problem");
        free(newHash);
        exit(1);
    }
    newHash->table = createHashTable(copyKey, freeKey, printKey, copyValue, freeList, printList, equalKey, transformIntoNumber, hashNumber);
    if (newHash->table == NULL) {
        printf("Memory Problem");
        free(newHash->table);
        free(newHash);
        exit(1);
    }
    newHash->freeFunc = freeValue;
    newHash->copyFunc = copyValue;
    newHash->printFunc = printValue;
    newHash->equalFunc = equalKey;
    return newHash;
}

//Destroy a MultiValueHashTable
status destroyMultiValueHashTable(MultiValueHashTable hash){
    if (hash == NULL) return failure;
    if (destroyHashTable(hash->table) == success){
        free(hash);
        return success;
    } else {
        free(hash);
        return failure;
    }
}


status addToMultiValueHashTable(MultiValueHashTable mvHash, Element key, Element value){
    if (mvHash == NULL || key == NULL || value == NULL) return failure;
    Element ptrList = lookupInHashTable(mvHash->table, key);
    if (ptrList != NULL) {
        return appendNode(ptrList, value);
    }
    ptrList = createLinkedList(mvHash->copyFunc, mvHash->freeFunc, mvHash->equalFunc, mvHash->printFunc);
    appendNode(ptrList, value);
    return addToHashTable(mvHash->table, key, ptrList);
}


Element lookUpInMultiValueHashTable(MultiValueHashTable mvHash, Element key){
    if (mvHash == NULL || key == NULL) return NULL;
    return lookupInHashTable(mvHash->table, key);
}

status removeFromMultiValueHashTable(MultiValueHashTable mvHash, Element key, Element value){
    if (mvHash == NULL || key == NULL || value == NULL) return failure;
    Element ptrList = lookupInHashTable(mvHash->table, key);
    if (ptrList == NULL) {
        return failure;
    }
    deleteNode(ptrList, value);
    if (getLengthList(ptrList) == 0) {
        removeFromHashTable(mvHash->table, key);
    }
    return success;
}

status displayMultiValueHashElementsByKey(MultiValueHashTable mvHash, Element key){
    if (mvHash == NULL || key == NULL) return failure;
    Element ptrList = lookupInHashTable(mvHash->table, key);
    if (ptrList == NULL) {
        return failure;
    }
    return displayList(ptrList);
}

