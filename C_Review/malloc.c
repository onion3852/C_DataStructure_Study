#include <stdio.h>
#include <stdlib.h>

int main(){
    // malloc을 이용한 동적 메모리 할당
    int i;
    int *ptr;

    ptr = (int *)malloc(5 * sizeof(int));

    printf("initialize array and print\n");
    for(i = 0; i < 5; i++){
        scanf("%d", &ptr[i]);
        printf("ptr[%d] is %d\n", i, *(ptr + i));
    }

    return 0;
}