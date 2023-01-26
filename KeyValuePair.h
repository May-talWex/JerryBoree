#ifndef KeyValuePair_H
#define KeyValuePair_H
#include "Defs.h"

typedef struct kvp *KeyValuePair;


KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey);
status destroyKeyValuePair(KeyValuePair pair);
status displayValue(KeyValuePair pair);
status displayKey(KeyValuePair pair);
KeyValuePair getValue(KeyValuePair pair);
Element getKey(KeyValuePair pair);
bool isEqualKey(KeyValuePair pair, Element key);

#endif /* KeyValuePair_H */