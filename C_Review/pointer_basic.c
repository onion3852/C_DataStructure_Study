#include <stdio.h>

int main(){
    int x = 1;
    int y = 2;

    printf("x = %d, y = %d\n", x, y);
    printf("...\n");

    int *ip;
    ip = &x;

    printf("address of x is %p\n", &x);
    printf("ip = %x\n", ip);
    printf("...................\n\n");

    y = *ip;
    printf("y = %d\n", y);
    printf("...................\n\n");

    *ip = 0;
    printf("x = %d\n", x);

    return 0;
}