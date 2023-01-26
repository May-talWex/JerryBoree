#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "Defs.h"

typedef struct MultiValueHashTable_t *MultiValueHashTable;

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
Element lookUpInMultiValueHashTable(MultiValueHashTable mvHash, Element key);
status addToMultiValueHashTable(MultiValueHashTable mvHash, Element key, Element value);
status removeFromMultiValueHashTable(MultiValueHashTable mvHash, Element key, Element value);
status destroyMultiValueHashTable(MultiValueHashTable hash);
status displayMultiValueHashElementsByKey(MultiValueHashTable mvHash, Element key);
#endif /*MULTIVALUEHASHTABLE_H*/
