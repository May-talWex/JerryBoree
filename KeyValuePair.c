#include "KeyValuePair.h"

struct kvp {
    Element key;
    Element value;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
};

KeyValuePair createKeyValuePair(Element key, Element value, CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey){
    if (key == NULL || value == NULL || copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL || printValue == NULL || equalKey == NULL){
        return NULL;
    }
    KeyValuePair newKVP = (KeyValuePair)malloc(sizeof(struct kvp));
    if(newKVP == NULL){
        printf("Memory Problem\n");
        exit(1);
    }
    newKVP->key = key;
    newKVP->value = value;
    newKVP->copyKey = copyKey;
    newKVP->freeKey = freeKey;
    newKVP->printKey = printKey;
    newKVP->copyValue = copyValue;
    newKVP->freeValue = freeValue;
    newKVP->printValue = printValue;
    newKVP->equalKey = equalKey;
    return newKVP;
}

status destroyKeyValuePair(KeyValuePair pair){
    if (pair == NULL){
        return failure;
    }
    pair->freeKey(pair->key);
    pair->freeValue(pair->value);
    free(pair);
    return success;
}

status displayValue(KeyValuePair pair){
    if (pair == NULL){
        return failure;
    }
    pair->printValue(pair->value);
    return success;
}

status displayKey(KeyValuePair pair){
    if (pair == NULL){
        return failure;
    }
    pair->printKey(pair->key);
    return success;
}

KeyValuePair getValue(KeyValuePair pair){
    if (pair == NULL){
        return NULL;
    }
    return pair->value;
}

Element getKey(KeyValuePair pair){
    if (pair == NULL){
        return NULL;
    }
    return pair->key;
}

bool isEqualKey(KeyValuePair pair, Element key){
    if (pair == NULL || key == NULL){
        return false;
    }
    return pair->equalKey(pair->key, key);
}

