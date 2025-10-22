#include "include/func.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv)
{
    if (argc != 3){
        fprintf(stderr, "error: invalid arguments\n");
        return -1;
    }
    FILE * file_in = fopen(argv[1], "r");
    FILE * file_out = fopen(argv[2],"w");
    if (!file_in || !file_out){
        fprintf(stderr, "error: can't open the file\n");
        return -1;
    }
    char string[1024];
    int len=0, result;
    char number[1024];
    while (fgets(string, sizeof(string), file_in) != NULL) {
        for (int i = 0; string[i]!='\0'; i++){
            if (string[i] == '\n' || string[i] == '\t' || string[i] == ' '){
                result = max_schisl(number, len);
                len = 0;
                if (result == -1){
                    fprintf(stderr, "error: file contains wrong symbols\n");
                    fclose(file_in);
                    fclose(file_out);
                    return -1;
                }
                else{
                    fprintf(file_out, "%d\n", result);
                }
            }
            else{
                number[len++] = string[i];
            }
        }
        if (len > 0){
            result = max_schisl(number, len);
            len = 0;
            if (result == -1){
                fprintf(stderr, "error: file contains wrong symbols\n");
                fclose(file_in);
                fclose(file_out);
                return -1;
            }
            else{
                fprintf(file_out, "%d\n", result);
            }
         }
    }


}