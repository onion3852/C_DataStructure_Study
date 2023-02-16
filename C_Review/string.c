#include <stdio.h>

int main(){
    // method 1
    char string_1 [10];

    string_1[0] = 'h';
    string_1[1] = 'e';
    string_1[2] = 'l';
    string_1[3] = 'l';
    string_1[4] = 'o';
    string_1[5] = '\0';
    printf("%s\n", string_1);

    // method 2
    char string_2 [] = "world";
    printf("%s\n", string_2);

    // method 3
    char *string_3 = "onion";
    printf("%s\n", string_3);

    return 0;
}