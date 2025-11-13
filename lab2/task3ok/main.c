#include "include/func.h"
#include <string.h>
int main(int argc, char ** argv)
{
    int n;
    overfprintf(stdout, "%Ro %Cv %to %d %p %n", 2210, 255, 16, "00000000000000000000000000000000001", 36, 32, NULL, &n);
    overfprintf(stdout, "\n%d", n);

}
