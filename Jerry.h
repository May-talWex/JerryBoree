#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Defs.h"
#include "LinkedList.h"

/************************************************************************structs creations************************************************************************/
typedef struct Planet_t {
    char *name;
    double x;
    double y;
    double z;
} Planet;

typedef struct Origin_t {
    char *dimension;
    Planet* origin_planet;
} Origin;

typedef struct PhysicalCharacteristic_t {
    char *characteristic_name;
    double characteristic_num;
} PhysicalCharacteristic;

typedef struct Jerry_t {
    char *id;
    int happiness;
    Origin* jerry_origin;
    int amount_of_characteristics;
    PhysicalCharacteristic** jerry_characteristics;
} Jerry;

/************************************************************************function signatures************************************************************************/
Jerry* createJerry(char *id, char* dimension, Planet *planet, int happiness);

Planet* createPlanet(char name[], double x, double y, double z);

PhysicalCharacteristic* createPhysicalCharacteristics(char* name, double characteristic);

Origin* createOrigin(char* dimension, Planet* origin_planet);

bool doesJerryHavePhysicalCharacteristics(Jerry* jerry, char* name);

status addPhysicalCharacteristicsToJerry(Jerry *jerry, char* name, double characteristic);

status deletePhysicalCharacteristicsFromJerryByName(Jerry* jerry, char* name);

status printPlanet(Planet* planet);

status printJerry(Jerry* jerry);

status freePlanet(Planet** planet, int num);

status freeOrigin(Origin *origin);

status freePC(PhysicalCharacteristic* physicalCharacteristic);









