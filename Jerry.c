#include "Jerry.h"
#include <stdio.h>

/************************************************************************creation functions************************************************************************/

//Function that creates a Jerry struct, returns pointer to the Jerry struct
Jerry* createJerry(char *id, char* dimension, Planet *planet, int happiness) {
    if (id == NULL || dimension == NULL || planet == NULL) {
        return NULL;
    }
    //Memory allocation for the Jerry struct
    Jerry *jerry = (Jerry *) malloc(sizeof(Jerry));
    //Error handling for memory allocation
    if (jerry == NULL){
        printf("Memory Problem\n");
        free(jerry);
        exit(1);
    }

    //Memory allocation for the id string
    jerry->id = (char *) malloc(strlen(id)+1);
    //Error handling for memory allocation
    if (jerry->id == NULL){
        printf("Memory Problem\n");
        free(jerry->id);
        exit(1);
    }

    //inserting the id, happiness and origin to the Jerry struct
    strcpy(jerry->id, id);
    jerry->happiness = happiness;
    jerry->jerry_origin = createOrigin(dimension, planet);
    //initializing the amount of characteristics to 0
    jerry->amount_of_characteristics = 0;
    jerry->jerry_characteristics = NULL;
    return jerry;
}

//Function that creates a Planet struct, returns pointer to the Planet struct
Planet* createPlanet(char* name, double x, double y, double z) {
    if (name == NULL) {
        return NULL;
    }
    //Memory allocation for the Planet struct
    Planet *planet = (Planet *) malloc(sizeof(Planet));
    //Error handling for memory allocation
    if (planet == NULL){
        printf("Memory Problem");
        free(planet);
        exit(1);
    }
    //Memory allocation for the name string
    planet->name = (char *) malloc(strlen(name)+1);
    //Error handling for memory allocation
    if (planet->name == NULL){
        printf("Memory Problem");
        free(planet->name);
        exit(1);
    }
    //inserting the name, x, y and z to the Planet struct
    strcpy(planet->name, name);
    planet->x = x;
    planet->y = y;
    planet->z = z;
    return planet;
}

//Function that creates a PhysicalCharacteristic struct, returns pointer to the PhysicalCharacteristic struct
PhysicalCharacteristic* createPhysicalCharacteristics(char* name, double characteristic) {
    if (name == NULL) {
        return NULL;
    }
    //Memory allocation for the PhysicalCharacteristic struct
    PhysicalCharacteristic *physicalCharacteristic = (PhysicalCharacteristic *) malloc(sizeof(PhysicalCharacteristic));
    //Error handling for memory allocation
    if (physicalCharacteristic == NULL){
        printf("Memory Problem\n");
        free(physicalCharacteristic);
        exit(1);
    }
    //Memory allocation for the name string
    physicalCharacteristic->characteristic_name = (char*)malloc(strlen(name)+1);
    //Error handling for memory allocation
    if (physicalCharacteristic->characteristic_name == NULL){
        printf("Memory Problem\n");
        free(physicalCharacteristic->characteristic_name);
        exit(1);
    }
    //inserting the name and characteristic to the PhysicalCharacteristic struct
    strcpy(physicalCharacteristic->characteristic_name, name);
    physicalCharacteristic->characteristic_num = characteristic;
    return physicalCharacteristic;
}

//Function that creates an Origin struct, returns pointer to the Origin struct
Origin* createOrigin(char* dimension, Planet* origin_planet) {
    if (dimension == NULL || origin_planet == NULL) {
        return NULL;
    }
    //Memory allocation for the Origin struct
    Origin *origin = (Origin *) malloc(sizeof(Origin));
    //Error handling for memory allocation
    if (origin == NULL){
        printf("Memory Problem\n");
        free(origin);
        exit(1);
    }
    //Memory allocation for the dimension string
    origin->dimension = (char *) malloc(strlen(dimension)+1);
    //Error handling for memory allocation
    if (origin->dimension == NULL){
        printf("Memory Problem\n");
        free(origin->dimension);
        exit(1);
    }
    //inserting the dimension and origin planet to the Origin struct
    strcpy(origin->dimension, dimension);
    origin->origin_planet = origin_planet;
    return origin;
}

/************************************************************************add & delete functions************************************************************************/
//boolean function to check if a Jerry struct has PhysicalCharacteristics
bool doesJerryHavePhysicalCharacteristics(Jerry* jerry, char* name) {
    if (jerry == NULL || name == NULL) {
        return false;
    }
    for (int i = 0; i < jerry->amount_of_characteristics; i++) {
        if (strcmp(jerry->jerry_characteristics[i]->characteristic_name, name) == 0) {
            return true;
        }
    }
    return false;
}

//Function that adds a PhysicalCharacteristic to a Jerry struct
status addPhysicalCharacteristicsToJerry(Jerry *jerry, char* name, double characteristic) {
    if (jerry == NULL || name == NULL) {
        return failure;
    }
    if (!doesJerryHavePhysicalCharacteristics(jerry, name)){
        jerry->amount_of_characteristics++;
        jerry->jerry_characteristics = (PhysicalCharacteristic**)realloc(jerry->jerry_characteristics, jerry->amount_of_characteristics * sizeof(PhysicalCharacteristic*));
        if (jerry->jerry_characteristics == NULL){
            printf("Memory Problem\n");
            free(jerry->jerry_characteristics);
            exit(1);
        }
        jerry->jerry_characteristics[jerry->amount_of_characteristics-1] = createPhysicalCharacteristics(name, characteristic);
    }
    return success;
}

//Function that deletes a PhysicalCharacteristic from a Jerry struct
status deletePhysicalCharacteristicsFromJerryByName(Jerry* jerry, char* name) {
    if (jerry == NULL || name == NULL) {
        return failure;
    }
    if (!doesJerryHavePhysicalCharacteristics(jerry, name)) {
        return failure;
    }
    else{
        for (int i = 0; i < jerry->amount_of_characteristics; i++){
            if (strcmp(jerry->jerry_characteristics[i]->characteristic_name, name) == 0){
                freePC(jerry->jerry_characteristics[i]);
                for (int j = i + 1; j < jerry->amount_of_characteristics; j++){
                    jerry->jerry_characteristics[j-1] = jerry->jerry_characteristics[j];
                }
                jerry->amount_of_characteristics--;
                jerry->jerry_characteristics = (PhysicalCharacteristic**)realloc(jerry->jerry_characteristics, jerry->amount_of_characteristics * sizeof(PhysicalCharacteristic*));
                break;
            }
        }
        return success;
    }
}

/************************************************************************print functions************************************************************************/

//Function that prints a Planet struct
status printPlanet(Planet* planet) {
    if (planet == NULL) {
        return failure;
    }
    printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->name, planet->x, planet->y, planet->z);
    return success;
}

//Function that prints a Jerry struct
status printJerry(Jerry* jerry) {
    if (jerry == NULL) {
        return failure;
    }
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d \n", jerry->happiness);
    printf("Origin : %s \n", jerry->jerry_origin->dimension);
    printPlanet(jerry->jerry_origin->origin_planet);
    if (jerry->amount_of_characteristics != 0) {
        printf("Jerry's physical Characteristics available : \n");
        bool flag = false;
        for (int i = 0; i < jerry->amount_of_characteristics; i++) {
            if (flag == false) {
                printf("\t%s : %.2f" , jerry->jerry_characteristics[i]->characteristic_name,
                       jerry->jerry_characteristics[i]->characteristic_num);
                flag = true;
                continue;
            }
            else {
                printf(" , %s : %.2f", jerry->jerry_characteristics[i]->characteristic_name,
                       jerry->jerry_characteristics[i]->characteristic_num);
            }
        }
        printf("\n");
    }
    return success;
}


/************************************************************************free functions************************************************************************/

status freeOrigin(Origin* origin) {
    if (origin == NULL) {
        return failure;
    }
    free(origin->dimension);
    free(origin);
    return success;
}

status freePC(PhysicalCharacteristic* physicalCharacteristic) {
    if (physicalCharacteristic == NULL) {
        return failure;
    }
    free(physicalCharacteristic->characteristic_name);
    free(physicalCharacteristic);
    return success;
}

status freePlanet(Planet** planet, int num) {
    if (planet == NULL) {
        free(planet);
        return failure;
    }
    for (int i = 0; i < num; i++) {
        free(planet[i]->name);
        free(planet[i]);
    }
    free(planet);
    return success;
}


