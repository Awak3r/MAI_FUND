#include <stdio.h>
#include "include/func.h"

int main() {
    Vector v = create_vector(2, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    printf("Size: %zu, Element[1]: %d\n", v.size, get_at_vector(&v, 1));
    delete_at_vector(&v, 1);
    printf("After delete: Size: %zu, Element[1]: %d\n", v.size, get_at_vector(&v, 1));
    erase_vector(&v);
    return 0;
}

