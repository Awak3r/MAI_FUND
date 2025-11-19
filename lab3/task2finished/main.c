#include <stdio.h>
#include "include/func.h"

int main() {
    Vector v = create_vector(2, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    int res;
    get_at_vector(&v, 1, &res);
    printf("Size: %zu, Element[1]: %d\n", v.size, res);
    delete_at_vector(&v, 1);
    get_at_vector(&v, 1, &res);
    printf("After delete: Size: %zu, Element[1]: %d\n", v.size, res);
    erase_vector(&v);
    return 0;
}

