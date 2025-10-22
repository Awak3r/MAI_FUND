#include <math.h>

int check(int base, double number){
    int n = fabs(number);
    int i;
    while(n>0){
        i = n%10;
        n%=10;
        if (base%(int)i != 0){
            return 1;
        }
    }
    return 0;
}


int main (int argc, char ** argv){

}