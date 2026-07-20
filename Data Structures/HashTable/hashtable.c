#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct HT {
    int *values;
    char **keys;
    char *delFlag; /*0 is empty, 1 is deleted, 2 is occupied*/
    int htSize;
    int numElements;
};

struct HT HT_new(void) {
    /* Construct an empty hash table */
    struct HT hashTable;
    hashTable.values = NULL;
    hashTable.keys = NULL;
    hashTable.delFlag = NULL; /*0 is empty, 1 is deleted, 2 is occupied*/
    hashTable.htSize = 0;
    hashTable.numElements = 0;

    return hashTable;
}

int hFunc(struct HT *ht, char *key){
    int letter;
    int i;
    int j;
    int index;

    i = 0;
    letter = key[0];
    index = 0;

    

    while(letter != '\0'){
        for(j=0; j < i; j++)
            letter = letter << 7;

        index += letter;

        i++;
        letter = key[i];
    }

    

    return abs(index % ht->htSize);
}

int sqrFunc(int i){
    int j;
    int odd;
    int sqr = 0;

    odd = 1;

    for(j=0; j<i; j++){
        sqr += odd;
        odd += 2;
    }

    return sqr;
}

/*hash function meant to handle the collisions.*/
int hColFunc(struct HT *ht, char *key,int i){
    return abs((hFunc(ht,key) + sqrFunc(i)) % ht->htSize);
}

int HT_contains(struct HT *ht, char *key) {
    /* Return 1 if the hash table contains the specified key; otherwise, return 0 */
    int i;
    int index;

    i = 0;

    do{
        index = hColFunc(ht,key,i);

        /*if the key at the index isn't null, compare the keys and if they're matching, return 1*/
        if(ht->keys[index] != NULL && !strcmp(key, ht->keys[index]))
            return 1;

        i++;
    }while(ht->delFlag[index] != 0); /*if an empty spot is reached, end and then return 0*/

    return 0;
}

int HT_getIndex(struct HT *ht, char *key) {
    /* Return the index associated with the specified key */
    int i;
    int index;

    i = 0;

    do{
        index = hColFunc(ht,key,i);

        /*if the key at the index isn't null, compare the keys and if they're matching, return the index*/
        if(ht->keys[index] != NULL && !strcmp(key, ht->keys[index]))
            return index;

        i++;
    }while(ht->delFlag[index] != 0); /*if an empty spot is reached, end and then return -1*/

    return -1;
}

/*adds a key value pair to a given index*/
void setValues(struct HT *ht, char *key, int value, int index){
    char *copyString;
    
    ht->delFlag[index] = 2; /*set to occupied*/
    ht->numElements++;
    ht->values[index] = value;

    /*allocates proper memory for string*/
    copyString = malloc((strlen(key)+1)*sizeof(char));
    /*copies string*/
    strcpy(copyString,key);
    /*frees original spot which is either a null ptr or some key*/
    free(ht->keys[index]);
    /*sets the array ptr to the new string*/
    ht->keys[index] = copyString;
}

/*shortened put function used for rehash*/
void ShortenedPut(struct HT *ht, char *key, int value) {
    /* Insert the key-value pair into the hash table */

    int index;

    index = HT_getIndex(ht,key);

    if(index != -1){ /*if an index with the key exists already*/
        /*set all values using that index*/
        ht->numElements--;
        setValues(ht, key, value, index);
    }
    else{ /*the index */
        int i;

        i = 0;

        do{
            index = hColFunc(ht,key,i);

            i++;
        }while(ht->delFlag[index] == 2); /*loop as long as it takes to reach a deleted or empty spot*/

        setValues(ht, key, value, index);
    }
}

void rehash(struct HT *ht){
    char *originalFlags;
    int *originalValues;
    char **originalKeys;
    int originalSize;
    int newSize;
    int i;
    int primes[14] = {97, 233, 479, 997, 2039, 4099, 8219, 17027, 34127, 68437, 139999, 280009, 640007,1280309};

    newSize = ht->htSize*2;

    /*find the closest prime number greater than 2 times the current size through a loop. once done, update the htSize*/
    for(i=0; i<14; i++){
        if(newSize < primes[i]){
            newSize = primes[i];
            break;
        }
    }

    originalSize = ht->htSize;
    ht->htSize = newSize;

    /*KEEP DELFLAG VALUES AND KEYS ATTACHED TO 3 LOCAL POINTERS*/
    originalFlags = ht->delFlag;
    originalValues = ht->values;
    originalKeys = ht->keys;

    /*attach new pointers (values keys delFlag), update size*/
    /*KEYS AND DELFLAG ARE TO USE CALLOC TO CREATE ALL NULL POINTERS AND EMPTY SPACES*/
    ht->values = malloc(sizeof(int)*newSize); /*malloc a new values array*/
    ht->delFlag = calloc(newSize,sizeof(char));
    ht->keys = calloc(newSize,sizeof(char*));

    /*just go through the whole keys array using delFlag as an indicator of occupied space and put those
    occupying keys and values through the HT_put function*/

    ht->numElements = 0;

    for(i=0; i<originalSize; i++){
        if(originalFlags[i] == 2){
            /*use the shortened put in order to place all the proper values in after the rehash*/
            ShortenedPut(ht,originalKeys[i],originalValues[i]);
        }
    }

    for(i=0; i<originalSize; i++)
        free(originalKeys[i]);

    /*free all of the remaining arrays*/
    free(originalFlags);
    free(originalKeys);
    free(originalValues);
}

void HT_put(struct HT *ht, char *key, int value) {
    /* Insert the key-value pair into the hash table */

    int index;

    /*if the number of elements has went over half, or the size is 0 we must rehash*/
    if(ht->htSize == 0 || ht->numElements*2 >= ht->htSize)
        rehash(ht);

    index = HT_getIndex(ht,key);

    if(index != -1){ /*if an index with the key exists already*/
        /*set all values using that index*/
        ht->numElements--;

        setValues(ht, key, value, index);
    }
    else{ /*the index */
        int i;

        i = 0;

        do{
            index = hColFunc(ht,key,i);
            
            i++;
        }while(ht->delFlag[index] == 2); /*loop as long as it takes to reach a deleted or empty spot*/

        setValues(ht, key, value, index);
    }
}

void HT_clear(struct HT *ht) {
    /* Remove all key-value pairs from the hash table */
    int i;
    int size;
    size = ht->htSize;

    if(ht->values == NULL){
        return;
    }

    free(ht->delFlag);
    free(ht->values);

    /*frees the allocated strings*/
    for(i=0; i<size; i++)
        free(ht->keys[i]);

    free(ht->keys);

    ht->delFlag = NULL;
    ht->keys = NULL;
    ht->values = NULL;
    ht->htSize = 0;
    ht->numElements = 0;
}

int HT_get(struct HT *ht, char *key) {
    /* Return the value associated with the specified key */
    int i;
    int index;

    i = 0;

    do{
        index = hColFunc(ht,key,i);

        /*if the key at the index isn't null, compare the keys and if they're matching, return the value*/
        if(ht->keys[index] != NULL && !strcmp(key, ht->keys[index]))
            return ht->values[index];

        i++;
    }while(ht->delFlag[index] != 0); /*if an empty spot is reached, end*/

    return 0; /*placeholder value since the function MUST return something*/
}

int HT_empty(struct HT *ht) {
    /* Return 1 if the hash table is empty; otherwise, return 0 */

    return ht->numElements == 0;
}

void HT_remove(struct HT *ht, char *key) {
    /* Delete the specified key and its associated value from the hash table */
    int index;

    /*grabs the associated index*/
    index = HT_getIndex(ht,key);
    
    if(index == -1)
        return;

    ht->numElements--;
    /*sets flag to deleted*/
    ht->delFlag[index] = 1;
    /*frees the memory of the string*/
    free(ht->keys[index]);
    /*sets the string pointer to NULL*/
    ht->keys[index] = NULL;

    /*no need to adjust ht->values[index]*/
}

char **HT_keys(struct HT *ht) {
    /* Return an array of all keys in the hash table, ending with NULL */
    char **keys;
    int i;
    int j;
    int size;

    j=0;
    size = ht->numElements;

    /*allocates space for all the keys and a NULL ptr at the end*/
    /*BECAUSE CALLOC IS USED, NULL PTR SHOULD ALREADY BE PRESENT*/
    keys = calloc(size + 1,sizeof(char*));
    
    for(i=0; i<ht->htSize; i++){
        if(ht->keys[i] != NULL){
            keys[j] = ht->keys[i];
            j++;
        }
    }

    return keys;
}
