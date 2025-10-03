#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int max_schisl(char * number, int length){
    int max_shis = 36, k;
    char s;
    for(int i = 0;i< length;i++){
        s = toupper(number[i]);
        if (s>='0'  && s<='9'){
            k = (int)s;
        }
        else if(s>='A' && s<='Z'){
            k = 10 + (int)s - 'A';
        }
        else{
            return -1;
        }
        if (k<max_shis){
            max_shis = k;
        }
    }
    return max_shis;
}

int main()
{
    char * s = "a13";
    int length = 3;
    int result = max_schisl(s, length);
    fprintf(stdout, "%d\n", result);
}