#include <stdio.h>

#define WIDTH 10

int calculate_sum(int *array);

int main() {
    int sum;
    int i;
    int average;
    int num[WIDTH];

    printf("Write 10 numbers for the array\n");
    for(i = 0; i < WIDTH; i++){
        scanf("%d", &num[i]);
    }

    sum = calculate_sum(num);
    average = sum / WIDTH;

    printf("sum is %d\n", sum);
    printf("average is %d\n", average);

    return 0;
}

// 배열을 매게변수로 받는 함수
// int *array 처럼 포인터로 받거나
// int array[] 처럼 배열로 받을 수 있음
int calculate_sum(int *array){
    int i;
    int sum = 0;

    for(i = 0; i < WIDTH; i++){
        sum = sum + array[i];
    }

    return sum;
}