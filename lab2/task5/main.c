#include "include/func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char ** argv)
{
    char filein_name[1024];
    char fileout_name[1024];
    fscanf(stdin, "%s", filein_name);
    fscanf(stdin, "%s", fileout_name);
    FILE * filein = fopen(filein_name, "r");
    FILE * fileout = fopen(fileout_name, "w");
    if (!filein || !fileout){
        if (filein) fclose(filein);
        if (fileout) fclose(fileout);
        fprintf(stderr, "error: cant open the file\n");
        return -1;
    }
    char buf[1024];  
    while (fgets(buf, 1024, filein)) {  
        if (strlen(buf) <= 80) {
            fprintf(fileout,"%s",  buf);
            continue;
        }
        char * cur = malloc(sizeof(char)*1024);
        if (!cur) return -1;
        norm_string(buf);
        while (strlen(buf)) {
            cur = obrez(buf);
            cur = add_probel(cur);
            fprintf(fileout, "%s\n", cur);
        }
        free(cur);
    }
    fclose(filein);
    fclose(fileout);
    return 0;
}
