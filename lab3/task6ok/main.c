#include "include/func.h"
#include <stdio.h>

int main(int argc, char ** argv)
{
 int res = check_brackets("{{[<ff>]}");
 fprintf(stdout, "%d\n", res);
}


