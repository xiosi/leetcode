#include <stdio.h>

int main()
{
    unsigned int x = 1;
    char        *c = (char *)&x;
    if (*c) {
        printf("小端序\n");
    } else {
        printf("大端序\n");
    }
    return 0;
}
