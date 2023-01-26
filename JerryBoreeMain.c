#include <stdio.h>
#include "Jerry.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "LinkedList.h"
#include <math.h>
#include <string.h>




/************************************************functions for hash table, multi hash and list************************************************/



Planet* findPlanet(Planet** planetArr, int numberOfPlanets, char* planetName)
{
    for (int i = 0; i < numberOfPlanets; i++) {
        if (strncmp(planetArr[i]->name, planetName, strlen(planetArr[i]->name)) == 0)
            return planetArr[i];
    }
    return NULL;
}

double getPCVal(Jerry* jerry, char* name, int* error){
    if( jerry == NULL || name == NULL){
        *error = 1;
        return 0;
    }
    //iterate over the PC array and search for the PC with the given name
    for (int i = 0; i < jerry->amount_of_characteristics; i++) {
        if (strcmp(jerry->jerry_characteristics[i]->characteristic_name, name) == 0) {
            *error = 0;
            return jerry->jerry_characteristics[i]->characteristic_num;
        }
    }
    //if we got here, we didn't find the PC and set the error to 1
    *error = 1;
    return 0;
}

Element CopyJerryID(Element element) /* copyKey */
{
    if (element == NULL)
        return NULL;
    char* ID = (char*)malloc(strlen(element) + 1);
    if (ID == NULL){
        printf("Memory Problem \n");
        free(ID);
        exit(1);
    }
    strcpy(ID, element);
    return ID;
}

status freeJerryID(Element element)
{
    if (element == NULL)
        return failure;
    free(element);
    return success;
}

status printJerryID(Element element){
    if (element == NULL)
        return failure;
    Jerry* jerry = (Jerry*)element;
    printf("%s",jerry->id);
    return success;
}

status freeJerry(Element element){ /* free all the pointers inside a Jerry and free the Jerry */
    if (element == NULL)
        return failure;
    Jerry* jerry = (Jerry*)element;
    free(jerry->id);
    freeOrigin(jerry->jerry_origin);
    for (int j = 0; j < jerry->amount_of_characteristics; j++){ /* for each PC of this Jerry do...*/
        freePC(jerry->jerry_characteristics[j]);
    }
    free(jerry->jerry_characteristics);
    free(jerry);
    return success;
}


Element copyJerry(Element element){ /* copy the pointer of the Jerry */
    if (element == NULL)
        return NULL;
    Jerry* jerry = (Jerry*)element;
    Jerry* Jerryptr = jerry;
    return (Jerryptr);
}

int transformIntoNumber(Element element){
    if (element == NULL)
        return 0;
    return *(int*)element;
}

status print_jerry(Element element){
    if (element == NULL)
        return failure;
    Jerry* jerry = (Jerry*)element;
    return printJerry(jerry);
}

status freePCName(Element element){
    if (element == NULL)
        return failure;
    char* str = (char*)element;
    free(str);
    return success;
}

status printPCName(Element element){
    char* name = (char*)element;
    if (element == NULL)
        return failure;
    printf("%s", name);
    return success;
}

Element copyPCName(Element element){
    if (element == NULL)
        return NULL;
    char* name = (char*)element;
    char* copy = name;
    return copy;
}

Element copyList(Element element){ /* there is no need for deep copy */
    return element;
}

status freeListElement(Element element){ /* free the inner list inside the value of kv pair */
    if (element == NULL)
        return failure;
    return success;
}

bool equalFunc (Element element1, Element element2){
    if (element1 == NULL || element2 == NULL)
        return false;
    Jerry* jerry1 = (Jerry*)element1;
    Jerry* jerry2 = (Jerry*)element2;
    return (strcmp(jerry1->id,jerry2->id)==0);
}

bool isPrime(int n){
    if (n <= 1)
        return false;
    for (int i=2; i < n; i++){
        if (n % i == 0)
            return false;}
    return true;
}

int hashNum(int number){ /* returns the closest prime number to specific number */
    int hashNum;
    hashNum = number;
    while (isPrime(hashNum) == false){
        hashNum += 1;}
    return hashNum;
}

int main(int argc, char *argv[])
{
    //parameters
    int numOfPlanets = atoi(argv[1]), err = 0;
    FILE *file = fopen(argv[2], "r");
    char line[1000], *name, *ID, *dim, *planetName = NULL, *pcSrch = NULL;
    char* characteristicName = NULL, *jerryID = NULL;
    double value, pcValue, PCval;
    int happinessL, jerryCounter = 0, pcNum = 0;
    linkedList jerryList, list, physList;
    Planet** planetArr = (Planet**)malloc(numOfPlanets * sizeof(Planet*));
    if (planetArr == NULL){
        printf("Memory Problem \n");
        free(planetArr);
        exit(1);}
    status statusCheck1;
    status statusCheck2;
    status statusCheck;
    jerryList = createLinkedList(copyJerry, freeJerry, equalFunc, print_jerry);
    int ch = 1;


    /* read the file */
    fgets(line, sizeof(line), file); /* read "Planets" */
    for (int i = 0; i < numOfPlanets; i++)
    {
        fgets(line, sizeof(line), file);
        name = strtok(line, ",");
        double x = atof(strtok(NULL, ","));
        double y = atof(strtok(NULL, ","));
        double z = atof(strtok(NULL, ","));
        planetArr[i] = createPlanet(name, x, y, z);
    }
    /* end of planet part */

    fgets(line, sizeof(line), file); /* read Jerries */
    bool finishRead = false;
    Planet* planet;
    Jerry* newJerry;
    if (fgets(line, sizeof(line), file) != NULL) {
        while (!finishRead) {
            ID = strtok(line, ",");
            dim = strtok(NULL, ",");
            planetName = strtok(NULL, ",");
            happinessL = atoi(strtok(NULL, ","));
            planet = findPlanet(planetArr, numOfPlanets, planetName);
            newJerry = createJerry(ID, dim, planet, happinessL);
            appendNode(jerryList, newJerry);
            jerryCounter++;

            /* read characteristics */
            if (fgets(line, 300, file) == NULL)
                break;
            while (line[0] == '\t')
            {
                name = strtok(&line[1], ":");
                value = atof(strtok(NULL, ":"));
                addPhysicalCharacteristicsToJerry(newJerry, name, value);
                pcNum++;
                if (fgets(line, 300, file) == NULL) {
                    finishRead = true;
                    break;
                }
            }
        }
    }
    fclose(file);


    int hashNumber = hashNum(jerryCounter); /* calculate the hash number according to the function */
    int multiHashNum = hashNum(pcNum); /* calculate the multihash number according to the function */
    hashTable JerriesHash = createHashTable(CopyJerryID, freeJerryID, printJerryID, copyJerry, freeListElement, print_jerry, equalFunc, transformIntoNumber, hashNumber);
    MultiValueHashTable PCHash = createMultiValueHashTable(copyPCName, freePCName, printPCName, copyList, freeListElement, print_jerry, equalFunc, transformIntoNumber, multiHashNum);

    /* update the hash and multihash values according to the jerryList */
    Jerry* tempJerry;
    Jerry* sadJerry;
    for (int i=1; i < jerryCounter + 1; i++){
        tempJerry = getDataByIndex(jerryList, i);
        jerryID = (char*)malloc(strlen(tempJerry->id) + 1);
        if (jerryID == NULL){
            printf("Memory Problem \n");
            free(jerryID);
            exit(1);}
        strcpy(jerryID, tempJerry->id);
        addToHashTable(JerriesHash, jerryID, tempJerry);
        for (int j=0; j < tempJerry->amount_of_characteristics; j++){
            characteristicName = (char*)malloc(strlen(name) + 1);
            if (characteristicName == NULL){
                printf("Memory Problem \n");
                free(characteristicName);
                exit(1);
            }
            strcpy(characteristicName, tempJerry->jerry_characteristics[j]->characteristic_name);
            physList = lookUpInMultiValueHashTable(PCHash, characteristicName);
            if (physList == NULL) { /* this charactaristic is not in the hash */
                addToMultiValueHashTable(PCHash, characteristicName, tempJerry);
            }
            else {
                appendNode(physList, tempJerry);
                free(characteristicName);
            }
        }
    }

    //start of the program - case definitions
    while (ch != 0){
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf("%d", &ch);

        switch(ch){
            case 1: /* add new Jerry */
                printf("What is your Jerry's ID ? \n");

                char* idSrch = (char*)malloc(301 * sizeof(char));
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                scanf("%s", idSrch);
                idSrch = (char*)realloc(idSrch, sizeof(idSrch));
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                Jerry* foundJerry;
                foundJerry = lookupInHashTable(JerriesHash, idSrch);
                if (foundJerry != NULL){ /* jerry is in the table */
                    printf("Rick did you forgot ? you already left him here ! \n");
                    free(idSrch);
                    break;
                }
                else {
                    printf("What planet is your Jerry from ? \n");
                    char* planetSrch = (char*)malloc(301 * sizeof(char));
                    if (planetSrch == NULL) {
                        free(idSrch);
                        printf("Memory Problem \n");
                        exit(0);
                    }
                    scanf("%s", planetSrch);
                    planetSrch = (char*)realloc(planetSrch, strlen(planetSrch) + 1);
                    if (planetSrch == NULL) {
                        printf("Memory Problem \n");
                        free(idSrch);
                        free(planetSrch);
                        exit(0);
                    }
                    Element planetFound = findPlanet(planetArr, numOfPlanets, planetSrch);
                    if (planetFound == NULL) {
                        printf("%s is not a known planet ! \n", planetSrch);
                        free(idSrch);
                        free(planetSrch);
                        break;
                    }
                    else {
                        printf("What is your Jerry's dimension ? \n");
                        dim = (char*)malloc(301 * sizeof(char));
                        if (dim == NULL) {
                            printf("Memory Problem \n");
                            free(idSrch);
                            free(planetSrch);
                            free(dim);
                            exit(0);
                        }
                        scanf("%s", dim);
                        dim = (char*)realloc(dim, strlen(dim) + 1);
                        if (dim == NULL) {
                            free(idSrch);
                            free(planetSrch);
                            free(dim);
                            printf("Memory Problem \n");
                            exit(0);
                        }
                        printf("How happy is your Jerry now ? \n");
                        int happinessValue;
                        scanf("%d", &happinessValue);
                        newJerry = createJerry(idSrch, dim, planetFound, happinessValue);
                        appendNode(jerryList, newJerry);
                        jerryID = (char*)malloc(strlen(newJerry->id) + 1);
                        if (jerryID == NULL){
                            free(idSrch);
                            free(planetSrch);
                            free(dim);
                            printf("Memory Problem \n");
                            exit(0);}
                        strcpy(jerryID,newJerry->id);
                        addToHashTable(JerriesHash, jerryID, newJerry);
                        print_jerry(newJerry);
                        free(dim);
                    }
                    free(planetSrch);
                }
                free(idSrch);

                break;

            case 2: /* add characteristic to specific Jerry */
                printf("What is your Jerry's ID ? \n");
                idSrch = (char*)malloc(301 * sizeof(char));
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                scanf("%s", idSrch);
                idSrch = (char*)realloc(idSrch, strlen(idSrch) + 1);
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                foundJerry = lookupInHashTable(JerriesHash, idSrch);
                if (foundJerry == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    free(idSrch);
                    break;
                }
                printf("What physical characteristic can you add to Jerry - %s ? \n", idSrch);
                pcSrch = (char*)malloc(301 * sizeof(char));
                if (pcSrch == NULL) {
                    free(idSrch);
                    printf("Memory Problem \n");
                    exit(0);
                }
                scanf("%s", pcSrch);
                pcSrch = (char*)realloc(pcSrch, strlen(pcSrch) + 1);
                if (pcSrch == NULL) {
                    free(idSrch);
                    printf("Memory Problem \n");
                    exit(0);
                }
                if (doesJerryHavePhysicalCharacteristics(foundJerry, pcSrch)) {
                    printf("The information about his %s already available to the daycare ! \n", pcSrch);
                    free(pcSrch);

                }
                else {
                    printf("What is the value of his %s ? \n", pcSrch);
                    scanf("%lf", &pcValue);
                    addPhysicalCharacteristicsToJerry(foundJerry, pcSrch, pcValue);
                    linkedList JerriesWithPC;
                    JerriesWithPC = lookUpInMultiValueHashTable(PCHash, pcSrch);
                    if (JerriesWithPC == NULL) { /* this charactaristic is not in the hash */
                        statusCheck = addToMultiValueHashTable(PCHash, pcSrch, foundJerry);
                        if (statusCheck == success) {
                            printf("%s : \n", pcSrch);
                            print_jerry(foundJerry);
                        }
                    }
                    else {
                        statusCheck=appendNode(JerriesWithPC, foundJerry);
                        if (statusCheck == success) {
                            printf("%s : \n", pcSrch);
                            displayList(JerriesWithPC);
                            free(pcSrch);
                        }
                    }
                }
                free(idSrch);
                break;

            case 3: /* remove characteristic from specific Jerry */
                printf("What is your Jerry's ID ? \n");
                idSrch = (char*)malloc(301 * sizeof(char));
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                scanf("%s", idSrch);
                idSrch = (char*)realloc(idSrch, strlen(idSrch) + 1);
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);
                }
                foundJerry = lookupInHashTable(JerriesHash, idSrch);
                if (foundJerry == NULL) /* jerry is not in the table */
                    printf("Rick this Jerry is not in the daycare ! \n");
                else {
                    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", foundJerry->id);
                    pcSrch = (char*)malloc(301 * sizeof(char));
                    if (pcSrch == NULL) {
                        free(idSrch);
                        printf("Memory Problem \n");
                        exit(0);
                    }
                    scanf("%s", pcSrch);
                    pcSrch = (char*)realloc(pcSrch, strlen(pcSrch) + 1);
                    if (pcSrch == NULL) {
                        free(idSrch);
                        printf("Memory Problem \n");
                        exit(0);
                    }
                    if (!doesJerryHavePhysicalCharacteristics(foundJerry, pcSrch)) {
                        printf("The information about his %s not available to the daycare ! \n", pcSrch);
                    }
                    else { /* foundJerry Jerry has this characteristic */
                        statusCheck1 = deletePhysicalCharacteristicsFromJerryByName(foundJerry, pcSrch);
                        statusCheck2 = removeFromMultiValueHashTable(PCHash, pcSrch, foundJerry);
                        if (statusCheck1 == success && statusCheck2 == success)
                            print_jerry(foundJerry);
                    }
                    free(pcSrch);
                }
                free(idSrch);
                break;

            case 4: /* remove jerry from the daycare */
                printf("What is your Jerry's ID ? \n");
                idSrch = (char*)malloc(301 * sizeof(char));
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);}
                scanf("%s", idSrch);
                idSrch = (char*)realloc(idSrch, strlen(idSrch) + 1);
                if (idSrch == NULL) {
                    printf("Memory Problem \n");
                    free(idSrch);
                    exit(0);}
                foundJerry = lookupInHashTable(JerriesHash, idSrch);
                if (foundJerry == NULL) { /* jerry is not in the table */
                    free(idSrch);
                    free(foundJerry);
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                for (int i=0; i < foundJerry->amount_of_characteristics; i++){
                    removeFromMultiValueHashTable(PCHash, foundJerry->jerry_characteristics[i]->characteristic_name, foundJerry);
                }
                removeFromHashTable(JerriesHash, foundJerry->id);
                deleteNode(jerryList, foundJerry);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                free(idSrch);
                break;

            case 5:
                printf("What do you remember about your Jerry ? \n");
                pcSrch = (char*)malloc(301 * sizeof(char));
                if (pcSrch == NULL) {
                    printf("Memory Problem \n");
                    free(pcSrch);
                    exit(0);
                }
                scanf("%s", pcSrch);
                pcSrch = (char*)realloc(pcSrch, strlen(pcSrch) + 1);
                if (pcSrch == NULL) {
                    printf("Memory Problem \n");
                    free(pcSrch);
                    exit(0);
                }
                linkedList pcList = lookUpInMultiValueHashTable(PCHash, pcSrch);
                if(pcList == NULL){
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pcSrch);
                    free(pcSrch);
                    break;}
                printf("What do you remember about the value of his %s ? \n", pcSrch);
                scanf("%lf", &PCval);
                double closestVal = -1;
                double tmpClosestVal;
                Jerry* closestJerry = NULL;
                for (int i = 1; i <= getLengthList(pcList); i++) {
                    tempJerry = (Jerry* )getDataByIndex(pcList, i);
                    err = 0;
                    if (closestVal < 0){ /* closestVal still -1 */
                        tmpClosestVal = fabs(getPCVal(tempJerry, pcSrch, &err) - PCval); /*absolute value of the difference between the wanted val and the current one*/
                        if (err)
                            continue;
                        closestVal = tmpClosestVal;
                        closestJerry = tempJerry;}
                    else {
                        if(fabs(getPCVal(tempJerry, pcSrch, &err) - PCval) < closestVal){ /*absolute value of the difference between the wanted val and the current one is the smallest until noe*/
                            if (err)
                                continue;
                            tmpClosestVal = fabs(getPCVal(tempJerry, pcSrch, &err) - PCval);
                            if (err)
                                continue;
                            closestVal = tmpClosestVal;
                            closestJerry = tempJerry;}
                    }
                }
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(closestJerry);
                removeFromHashTable(JerriesHash, closestJerry->id);
                removeFromMultiValueHashTable(PCHash, pcSrch, closestJerry);
                deleteNode(jerryList, closestJerry);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                free(pcSrch);
                break;

            case 6: /* return the saddest Jerry */
                if(getLengthList(jerryList) == 0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                sadJerry =  getDataByIndex(jerryList, 1);
                for (int i = 1; i < getLengthList(jerryList) + 1; i++){
                    tempJerry = getDataByIndex(jerryList, i);
                    if (i == 1)
                        happinessL = tempJerry->happiness;
                    if (tempJerry->happiness < happinessL){
                        sadJerry = tempJerry;
                        happinessL = tempJerry->happiness;
                    }
                }
                printf("Rick this is the most suitable Jerry we found : \n");
                print_jerry(sadJerry);
                for (int i=0; i < sadJerry->amount_of_characteristics; i++){
                    removeFromMultiValueHashTable(PCHash, sadJerry->jerry_characteristics[i]->characteristic_name, sadJerry);
                }
                removeFromHashTable(JerriesHash, sadJerry->id);
                deleteNode(jerryList, sadJerry);
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;

            case 7:
                printf("What information do you want to know ? \n");
                printf("1 : All Jerries \n");
                printf("2 : All Jerries by physical characteristics \n");
                printf("3 : All known planets \n");
                int ch2 = 1;
                scanf("%d", &ch2);

                switch (ch2) {
                    case 1:
                        if(getLengthList(jerryList) == 0)
                            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                        else
                            displayList(jerryList);
                        break;

                    case 2:
                        printf("What physical characteristics ? \n");
                        pcSrch = (char*)malloc(301 * sizeof(char));
                        if (pcSrch == NULL) {
                            printf("Memory Problem \n");
                            free(pcSrch);
                            exit(0);
                        }
                        scanf("%s", pcSrch);
                        pcSrch = (char*)realloc(pcSrch, strlen(pcSrch) + 1);
                        if (pcSrch == NULL) {
                            printf("Memory Problem \n");
                            free(pcSrch);
                            exit(0);
                        }
                        list = (linkedList)lookUpInMultiValueHashTable(PCHash, pcSrch);
                        if (list == NULL){
                            printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pcSrch);
                            free(pcSrch);
                            break;
                        }
                        printf("%s : \n", pcSrch);
                        displayList(list);
                        free(pcSrch);
                        break;

                    case 3:
                        for (int i=0; i < numOfPlanets; i++)
                            printPlanet(planetArr[i]);
                        break;


                    default: /* if different option was chosen */
                        printf("Rick this option is not known to the daycare ! \n");
                }

                break;

            case 8:
                if(getLengthList(jerryList) == 0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                int ch3 = 1;
                printf("What activity do you want the Jerries to partake in ? \n");
                printf("1 : Interact with fake Beth \n");
                printf("2 : Play golf \n");
                printf("3 : Adjust the picture settings on the TV \n");
                scanf("%d", &ch3);
                switch (ch3) {
                    case 1:
                        for (int i = 1; i < (getLengthList(jerryList) + 1) ; i++){
                            tempJerry = getDataByIndex(jerryList, i);
                            if (tempJerry->happiness >= 20){
                                tempJerry->happiness = tempJerry->happiness + 15;
                                if (tempJerry->happiness > 100)
                                    tempJerry->happiness = 100;}
                            else{
                                tempJerry->happiness = tempJerry->happiness - 5;
                                if (tempJerry->happiness < 0)
                                    tempJerry->happiness = 0;}
                        }
                        printf("The activity is now over ! \n");
                        displayList(jerryList);
                        break;

                    case 2:
                        for (int i = 1; i < getLengthList(jerryList) + 1; i++){
                            tempJerry = getDataByIndex(jerryList, i);
                            if (tempJerry->happiness >= 50){
                                tempJerry->happiness = tempJerry->happiness + 10;
                                if (tempJerry->happiness>100)
                                    tempJerry->happiness = 100;}
                            else{
                                tempJerry->happiness = tempJerry->happiness - 10;
                                if (tempJerry->happiness<0)
                                    tempJerry->happiness = 0;}
                        }
                        printf("The activity is now over ! \n");
                        displayList(jerryList);
                        break;

                    case 3:
                        for (int i = 1; i < getLengthList(jerryList) + 1; i++){
                            tempJerry = getDataByIndex(jerryList, i);
                            tempJerry->happiness = tempJerry->happiness + 20;
                            if (tempJerry->happiness>100)
                                tempJerry->happiness = 100;
                        }
                        printf("The activity is now over ! \n");
                        displayList(jerryList);
                        break;

                    default: /* if different option was chosen */
                        printf("Rick this option is not known to the daycare ! \n");
                }
                break;

            case 9: /* clean memory and exit */
                destroyMultiValueHashTable(PCHash);
                freePlanet(planetArr, numOfPlanets);
                destroyList(jerryList);
                destroyHashTable(JerriesHash);
                printf("The daycare is now clean and close ! \n");
                exit(0);

            default: /* if different option was chosen */
                printf("Rick this option is not known to the daycare ! \n");
                break;
        }
    }
}



