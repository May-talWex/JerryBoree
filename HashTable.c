#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s {
    linkedList* table;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    TransformIntoNumberFunction transformKeyIntoNumber;
    EqualFunction keysEqual;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    int size;
};

status freeKVP(Element element){
    if (element == NULL) return failure;
    KeyValuePair kvp = (KeyValuePair)element;
    return destroyKeyValuePair(kvp);
}

Element copyKVP(Element element){
    if (element == NULL) {
        return NULL;
    }
    return (KeyValuePair)element;
}

bool equalKVP(Element element1, Element element2){
    if (element1 == NULL || element2 == NULL) return false;
    KeyValuePair kvp = (KeyValuePair)element1;
    if(strncmp(getKey(kvp), element2, strlen(element2)) == 0){
        return true;
    }
    return false;
}

status printKVPVal(Element element){
    if (element == NULL) return failure;
    KeyValuePair kvp = (KeyValuePair)element;
    return displayValue(kvp);
}


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL || transformIntoNumber == NULL || hashNumber <= 0) {
        return NULL;
    }
    hashTable newHash = malloc(sizeof(struct hashTable_s));
    if (newHash == NULL) {
        printf("Memory Problem");
        exit(1);
    }
    newHash->size = hashNumber;
    newHash->table = malloc(sizeof(linkedList) * hashNumber);
    if (newHash->table == NULL) {
        printf("Memory Problem");
        exit(1);
    }
    int i = 0;
    while (i < hashNumber) {
        newHash->table[i] = createLinkedList(copyKVP, freeKVP, equalKVP, printKVPVal);
        i++;
    }
    newHash->copyKey = copyKey;
    newHash->freeKey = freeKey;
    newHash->printKey = printKey;
    newHash->copyValue = copyValue;
    newHash->freeValue = freeValue;
    newHash->printValue = printValue;
    newHash->keysEqual = equalKey;
    newHash->transformKeyIntoNumber = transformIntoNumber;
    return newHash;
}

status destroyHashTable(hashTable hash){
    if (hash == NULL) {
        free(hash);
        return failure;}
    int i = 0;
    while (i < hash->size) {
        destroyList(hash->table[i]);
        i++;
    }
    free(hash->table);
    free(hash);
    return success;
}

status addToHashTable(hashTable hash, Element key,Element value){
    if (hash == NULL || key == NULL || value == NULL) return failure;
    int index = hash->transformKeyIntoNumber(key) % hash->size;
    if (index > hash->size || index < 0) return failure;
    KeyValuePair kvp = createKeyValuePair(key, value, hash->copyKey, hash->freeKey, hash->printKey, hash->copyValue, hash->freeValue, hash->printValue, hash->keysEqual);
    return appendNode(hash->table[index], kvp);
}

Element lookupInHashTable(hashTable hash, Element key){
    int index;
    KeyValuePair found;
    if (hash == NULL || key == NULL){
        return NULL;
    }
    index = hash->transformKeyIntoNumber(key);
    index = index % hash->size;
    found = searchByKeyInList(hash->table[index], key);
    if (found == NULL) {
        return NULL;
    }
    return getValue(found);
}

status removeFromHashTable(hashTable hash, Element key){
    if (hash == NULL || key == NULL) return failure;
    int index = hash->transformKeyIntoNumber(key) % hash->size;
    Element kvp = searchByKeyInList(hash->table[index], key);
    if (kvp == NULL) return failure;
    return deleteNode(hash->table[index], kvp);
}

status displayHashElements(hashTable hash){
    if (hash == NULL) return failure;
    int i = 0;
    while (i < hash->size) {
        displayList(hash->table[i]);
        i++;
    }
    return success;
}

int mystrlen(const char *p)
{
    int c=0;
    while(*p!='\0')
    {
        c++;
        *p++;
    }
    return(c);
}