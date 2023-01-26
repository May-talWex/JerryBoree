The JerryBoreeProgram is made up of 4 ADTs and a main file.
ADTs: LinkedList, HashTavle, KeyValuePair, Multi Value Hash Table
The program definition is as follows:
Hash table the size of Hash Number. Made up of linked lists.
Each cell in the hash table contains linked list nodes that were mapped to indexes according to the hash function.
Each node has an element and a pointer to the next node. The element is a pointer to a Key Value Pair struct.

1. Jerry Hash - hashtable that contains Jerries. The hash table cells are nodes that contain a pointer to a key - a Jerry ID, and a pointer to a Key Value Pair.
The size of the hashtable is as the size of the Jerries that are in the config file. In order to minimize clashes in the hashtable the number chosen is a prime number.

2. Physical Characteristic MultiValuesHash - Multi Value Hash table that contains node linked lists, each node contains a pointer to a Key Value Pair. The key is the name of the characteristic and the value is a pointer to alinked list that contains all Jerries with that characteristic.

3.Jerries List - linked list that contains pointers to all Jerries that were inserted into the program in order of insertion.

4. Planet Array - Array that contains pointers to planets
