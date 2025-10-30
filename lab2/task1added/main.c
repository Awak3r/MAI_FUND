#include "include/func.h"

int main() {
    func(10, 4, 0.5, 0.25, 0.333333, 0.2); 
    //yes, yes, yes, yes
    func(6, 4, 0.5, 0.25, 0.333333, 0.2);
    // yes, yes, no, no
    func(2, 3, 0.5, 0.25, 0.2);
    //yes, yes, no
    func(10, 4, 1.0/7.0, 0.125, 1.0/9.0, 0.166666667); 
    //yes, yes, yes, yes

    return 0;
}
