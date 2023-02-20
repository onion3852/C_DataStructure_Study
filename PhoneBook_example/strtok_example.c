// strtok() 함수의 사용을 연습

#include <stdio.h>
#include <string.h>

int main(void){
    char str[]   = "Now @ is the time @ to start preparing @@@ for the exam@";
    char delim[] = "@";  // delimiter
    char *token;         // tokenized string

    // strtok()의 리턴값은 delimiter를 만나 잘린 token string의 시작 주소
    // 참고로 strtok()은 원본 문자열을 가지고 작업이 이루어짐. 새로운 배열을 만드는 것이 아님
    // 원본 문자열의 delimiter는 strtok()에 의해 \0 로 변환되더 token으로 만들어짐
    // ( printf("%s", str); 을 출력해보면 알 수 있음 )
    // 따라서 원본 문자열이 보존되어야 한다면 복사 후에 strtok()를 이용해야 함 
    // 원본 문자열은, 수정되어야 하므로 string literal이 아니어야 함
    // (원본 문자열을 char *str 로 정의하면 안됨)
    token = strtok(str, delim);
    while(token != NULL){
        printf("next token is -> %s: %d\n", token, strlen(token));
        // 계속해서 token을 만드려면 strtok()가 또 호출되어야 하고
        // strtok를 이어서 이용하려면 strtok(NULL, )처럼 첫째 인자는 NULL 로 써야한다.
        // 만약 문장의 완전 끝에 도달하여 마지막 token을 만들고
        // 다시 strtok(NULL, )을 호출하면, NULL을 반환하게 됨(while문 조건 설정의 배경)
        token = strtok(NULL, delim);

        // 따라서 strtok()는 while문을 이용해 쓰는 것이 적절해 보임 
    }

    return 0;
}