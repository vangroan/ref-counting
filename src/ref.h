
#ifndef REF_H
#define REF_H

#include <stddef.h>


typedef struct Ref_s {
    void (*free)(const struct Ref_s*);
    int count;
} Ref;


// Cast const pointer to mutable pointer
static inline void incRef(const struct Ref_s* ref) {
    ((struct Ref_s*)ref)->count++;
}


static inline void decRef(const struct Ref_s* ref) {
    if (--((struct Ref_s*)ref)->count == 0)
        ref->free(ref);
}


#endif