#include <stdio.h>

int main() {
    int num [4];
    char ch [4];
    int i;

    // define int array
    printf("Type numbers for array 'num'\n");
    for(i = 0; i < 4; i++){
        scanf("%d", &num[i]);
    }
    printf("\n");

    // define character array
    printf("Type characters for array 'ch'\n");
    for(i = 0; i < 4; i++){
        scanf("%c ", &ch[i]);
    }
    printf("\n");

    // print int array's address
    for(i = 0; i < 4; i++){
        printf("&[num + %d] is %p\n", i, &num[i]);
    }
    printf("\n");

    // print character array's address
    for(i = 0; i < 4; i++){
        printf("&[ch + %d] is %p\n", i, &ch[i]);
    }
    printf("\n");
    
    // prove pointer arithmetic
    for(i = 0; i < 4; i++){
        printf("num[%d] = %d, *(num + %d) = %d\n", i, num[i], i, *(num + i));
    }

    return 0;
}