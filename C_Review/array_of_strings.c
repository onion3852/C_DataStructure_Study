#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    // 여러개의 단어를 배열에 저장하기
    char buffer [100];  // maximum 100 letters
    char * words [5];   // array to save buffer's word
                        // words 라는 배열에 저장할 것은 배열 buffer 임
                        // buffer는 배열의 이름으로서, 포인터에 해당하므로
                        // 배열 words는 포인터를 저장하는 배열이 되어야 함
                        // 그리고 그 포인터는 buffer, 즉 char형 데이터를
                        // 가리키고 있으므로 char형 포인터를 선언하는 것이다.
    int i = 0;
    char *ptr [5];

    printf("Type words...\n");
    while((i < 5) && (scanf("%s", buffer) != EOF)){
        ptr[i] = (char *)malloc(strlen(buffer) * sizeof(char));
        strcpy(ptr[i], buffer);
        words[i] = ptr[i];
        i++;
    }

    printf("\nThese are the words that you chosen...\n\n");
    for(i = 0; i < 5; i++){
        printf("%s\n", words[i]);
    }

    return 0;
}