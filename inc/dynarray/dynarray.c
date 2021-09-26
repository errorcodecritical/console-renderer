#include "dynarray.h"

//-

void __Memcpy(void* dest, void* src, int n) {
    for (int i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void __Memmove(void* dest, void* src, int n) {
    char* temp = (char*)malloc(n * sizeof(char));

    for (int i = 0; i < n; i++) {
        ((char*)temp)[i] = ((char*)src)[i];
    }

    for (int i = 0; i < n; i++) {
        ((char*)dest)[i] = ((char*)temp)[i];
    }
    free(temp);
}

void __Memset(void* dest, char value, int n) {
    for (int i = 0; i < n; i++) {
        ((char*)dest)[i] = value;
    }
}

//-

static void __Shift(set_t* this, int index, int shift) {
    int n_byte = ((this->next) - index) * this->width;

    __Memmove(
        &((char*)this->contents)[(index + shift) * this->width],
        &((char*)this->contents)[index * this->width], 
        n_byte
    );
    this->next += shift;
}

static void __Grow(set_t** set_ptr, int amount) {
    set_t* this = realloc(*set_ptr, sizeof(set_t) + ((*set_ptr)->length + amount) * (*set_ptr)->width);
    assert(this, "Error: failed to grow set.\n");

    this->length += amount;
    this->contents = this + 1;
    *set_ptr = this;
}

static set_t* __Create(int width, int length) {
    set_t* new_set = malloc(sizeof(set_t) + width * length);

    new_set->width = width;
    new_set->length = length;
    new_set->next = 0;
    new_set->contents = new_set + 1; // naughty >:)
    
    return new_set;
}

static void __Insert(set_t** set_ptr, int index, void* value) {
    set_t* this = *set_ptr;
    assert(value, "Pointer to value must not be NULL.\n");

    if (this->next >= this->length) {
        __Grow(set_ptr, this->length / 2);
        this = *set_ptr;
    }

    if (index == this->next) {    
        __Memcpy((char*)this->contents + index * this->width, value, this->width);
        this->next += 1;
    } else if (index < this->next) {
        __Shift(this, index, 1);
        __Memcpy((char*)this->contents + index * this->width, value, this->width);
    } else {
        // idfk
    }
}

static void __Remove(set_t** set_ptr, int index) {
    set_t* this = *set_ptr;
    
    if (index == this->next) {
        __Memset((char*)this->contents + index * this->width, 0, this->width);
        this->next -= 1;
    } else if (index < this->next) {
        __Shift(this, index, -1);
        __Memset((char*)this->contents + this->next * this->width, 0, this->width);
    } else {
        // still idfk
    }
}

static void __Destroy(set_t** set_ptr) {
    free(*set_ptr);
    *set_ptr = 0;
}

//-

struct __SetMethods set = {
    .create = __Create,
    .destroy = __Destroy,
    .insert = __Insert,
    .remove = __Remove
};