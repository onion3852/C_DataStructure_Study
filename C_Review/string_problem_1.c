// 프롬프트($)와 한 칸의 공백문자를 출력시키고 사용자의 입력을 받는 프로그램
// 문장을 입력하고 리턴키를 입력하면
// 리턴을 제외하고, 입력한 문장을 그대로 출력하고 입력한 문장의 길이를 출력한다.
// 이때 띄어쓰기(공백문자)와 문장의 앞, 뒤 공백문자도 모두 카운트 하도록 한다.

// 작성하려는 기능에 따라
// scanf, gets, fgets 등등
// 여러가지 함수들을 생각해 볼 수 있음

#include <stdio.h>
#include <string.h>

#define LENGTH 50

int read_line(char *ptr, int limit);

int main(){
    // maximum length is 50
    char buffer [LENGTH];
    int n;

    // Initializing buffer
    for(n = 0; n < LENGTH; n++)
            buffer[n] = '\0';

    printf("Hello onion...\n");
    while(1){
        printf("$ ");
        read_line(buffer, LENGTH);
        printf("$ %s : %d characters\n", buffer, strlen(buffer));
    }

    return 0;
}

int read_line(char *ptr, int limit){
    int ch;  // why int ???
    int i = 0;

    while((ch = getchar()) != '\n'){
        if(i < limit){
            ptr[i] = ch;
            i++;
        }
    }
    ptr[i] = '\0';

    return i;
}