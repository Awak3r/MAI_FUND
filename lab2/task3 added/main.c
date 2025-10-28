#include "include/func.h"
#include <string.h>
int main(int argc, char ** argv)
{
    overfprintf(stdout, "%Ro %Cv %to %d %p", 2210, 255, 16, "00000000000000000000000000000000001", 36, 32, NULL);

}
