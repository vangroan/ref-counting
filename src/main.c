
#include <stdlib.h>
#include <stdio.h>

#include "ref.h"


// http://stackoverflow.com/questions/10269685/kernels-container-of-any-way-to-make-it-iso-conforming
// Non-type-safe generic implementation of container_of
#define container_of(ptr, type, member) \
    ((type*) ((char*)(ptr) - offsetof(type, member)))


typedef struct Obj_s {
    int value;
    Ref refcount;
} Obj;


void freeObj(const Ref* ref) {
    Obj* obj = container_of(ref, Obj, refcount);
    printf("Freeing Object %d\n", obj->value);
    free(obj);
}


Obj* newObj(int val) {
    Obj* obj = malloc(sizeof(Obj));
    obj->value = val;
    obj->refcount = (Ref){freeObj, 1};
    return obj;
}


int main() {

    Obj* obj1 = newObj(1);
    
    // Pass in address of refcount member
    incRef(&obj1->refcount);
    incRef(&obj1->refcount);
    incRef(&obj1->refcount);

    printf("Object {value: %d, count: %d}\n", obj1->value, obj1->refcount.count);

    decRef(&obj1->refcount);
    decRef(&obj1->refcount);
    decRef(&obj1->refcount);

    printf("Object {value: %d, count: %d}\n", obj1->value, obj1->refcount.count);

    decRef(&obj1->refcount);

    // Expect undefined behaviour
    printf("Object {value: %d, count: %d}\n", obj1->value, obj1->refcount.count);

    return 0;
}
