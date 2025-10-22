#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)
{
    if (argc < 3){
        fprintf(stderr, "error: invalid input\n");
        return -1;
    }
    char * file_in_name = argv[2];
    char flag;
    if(argv[1][0] != '/' && argv[1][0] != '-'){
        fprintf(stderr, "error: invalid input\n");
        return -1;
    }
    const char * prefix = "out_";
    char *file_out_name = (char *)malloc(
        strlen(prefix)*sizeof(char)+ strlen(file_in_name)*sizeof(char)+1);
    int freek = 0;
    if (argv[1][1] != 'n'){
       const char * prefix = "out_";
       strcpy(file_out_name, prefix);
       strcat(file_out_name, file_in_name);
       freek = 1;
       flag = argv[1][1];
    }
    else if (argc == 4){
        free(file_out_name);
        file_out_name = argv[3];
        flag = argv[1][2];
    }
    else{
        fprintf(stderr, "error: invalid input\n");
        return -1;
    }
    FILE *file_in = fopen(file_in_name, "r");
	FILE *file_out = fopen(file_out_name, "w");
    if (!file_in || !file_out){
        fprintf(stderr, "error: can't open the file\n");
        if(freek) free(file_out_name);
        return -1;
    }
    
    int simbol;
    char string[256];
    int counter;
    switch (flag) {
        case 'd':
            while ((simbol = fgetc(file_in)) != EOF){
                if (!(simbol>='0' && simbol<='9')){
                    fputc(simbol, file_out);
                    }
            }
        break;
        case 'i':
            while(fgets(string, sizeof(string), file_in) != NULL){
                counter = 0;
                for(int i = 0; i<strlen(string); i++){
                    if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')){
                        ++counter;
                    }
                }
                fprintf(file_out, "%d\n", counter);
            }
        break;
        case 's':
            while(fgets(string, sizeof(string), file_in) != NULL){
                counter = 0;
                for(int i = 0; i<strlen(string); i++){
                    if (!((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (string[i] == ' ') || (string[i]>='0' && string[i]<='9'))){
                        ++counter;
                    }
                }
                fprintf(file_out, "%d\n", counter);
            }
        break;
        case 'a':
            while((simbol = fgetc(file_in))!=EOF){
                if(!(simbol>='0' && simbol<='9')){
                   fprintf(file_out, "%02X", simbol);
                }
                else{
                    fputc(simbol, file_out);
                }
            }

        break;
    }
    if(freek) free(file_out_name);
    fclose(file_in);
    fclose(file_out);
}
