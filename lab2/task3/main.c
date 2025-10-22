#include <stdio.h>
#include <string.h>



int overprintf(char *filename, char* string[]){
    FILE *file = fopen(filename, "w");
    int length = sizeof(string)/ sizeof(string[0]);
    int i = 0;
    int k = 0;
    int len;
    if (length == 1){
        fputs(string[0], file);
        return 0;
    }
    else{
        if (string[0][0] != '"' && string[0][-1] != '"'){
            return -1;
        }
        ++i;
        while(string[0][i]!='"'){
            if (string[0][i] == '%'){
                ++i;
                switch (string[0][i]) {
                    case("d" || "i"){
                        len = strlen()
                    }
                }
            }
            else{
                fputc(string[0][i], file);
                ++i;
            }
        }
    }
}