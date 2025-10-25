#include "include/func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv)
{
    char *filein_name = NULL;
    char *fileout_name = NULL;
    size_t len1 = 0, len2 = 0;
    if (getline(&filein_name, &len1, stdin) == -1 || \
        getline(&fileout_name, &len2, stdin) == -1) {
        fprintf(stderr, "error: cant read \n");
        free(filein_name);
        free(fileout_name);
        return -1;
    }
    filein_name[strcspn(filein_name, "\n")] = '\0';
    fileout_name[strcspn(fileout_name, "\n")] = '\0';
    if (!strcmp(filein_name, fileout_name)){
        fprintf(stderr, "error: cant read\n");
        free(filein_name);
        free(fileout_name);
        return -1;
    }
    FILE * filein = fopen(filein_name, "r");
    FILE * fileout = fopen(fileout_name, "w");
    if (!filein || !fileout){
        if (filein) fclose(filein);
        if (fileout) fclose(fileout);
        fprintf(stderr, "error: cant open the file\n");
        free(filein_name);
        free(fileout_name);
        return -1;
    }
    char *buf = NULL;
    size_t len = 0;
    while (getline(&buf, &len, filein) != -1) {  
        if (strlen(buf) <= 80) {
            fprintf(fileout, "%s", buf);
            continue;
        }
        norm_string(buf);
        while (strlen(buf)) {
            char *cur = obrez(buf);
            cur = add_probel(cur);
            fprintf(fileout, "%s\n", cur);
            free(cur);  
        }
    }
    free(buf);
    fclose(filein);
    fclose(fileout);
    free(filein_name);
    free(fileout_name);
    return 0;
}
