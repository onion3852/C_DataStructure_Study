#include <stdio.h>
#include <string.h>

#define MAX_DATA    100
#define BUFFER_SIZE 20

char * names  [MAX_DATA];
char * numbers[MAX_DATA];
int n = 0;  // number of stored data(저장된 사람 수와 같음)

void add();
void find();
void status();
void delete();

int main(){
    char command [BUFFER_SIZE];

    while(1){
        printf("$ ");
        scanf("%s", command);   
        // scanf()가 공백문자 입력받기 전 까지를 저장함을 이용

        // 두 문자열을 비교하여 같다면 0을 반환하는 strcmp를 이용
        if(!strcmp(command, "add"))
            add();
        else if(!strcmp(command, "find"))
            find();
        else if(!strcmp(command, "status"))
            status();
        else if(!strcmp(command, "delete"))
            delete();
        else if(!strcmp(command, "exit"))
            break;          
    }

    return 0;
}

///////////////////////////////////////////////////////////////
// function declaration
///////////////////////////////////////////////////////////////
void add(){
    char str1 [BUFFER_SIZE];
    char str2 [BUFFER_SIZE];

    scanf("%s", str1);
    scanf("%s", str2);
    names[n]   = strdup(str1);
    numbers[n] = strdup(str2);
    // strdup()는 내부적으로 malloc()을 통해 메모리를 할당받고 
    // 거기에 문자열을 복사한다. 그리고 그 공간의 시작점을 return한다.(포인터)
    n++;

    printf("%s was added successfully.\n", str1);
}

void find(){
    char str1 [BUFFER_SIZE];
    int i;

    scanf("%s", str1);
    for(i = 0; i < n; i++){
        if(strcmp(str1, names[i]) == 0){
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("Person named '%s' isn't exists.\n", str1);
}

void status(){
    int i;

    for(i = 0; i < n; i++)
        printf("%s : %s\n", names[i], numbers[i]);

    printf("Total %d person\n", n);
}

void delete(){
    char str1[BUFFER_SIZE];
    int i;

    scanf("%s", str1);
    // 맨 마지막 저장 데이터를 없앨 데이터 위치로 옮긴다.
    // 실제 삭제 과정이 필요한 것이 아님
    for(i = 0; i < n; i ++){
        if(strcmp(str1, names[i]) == 0){
            names[i]   = names[n - 1];
            numbers[i] = numbers[n - 1];
            n--;
            printf("'%s' was deleted successfully.\n", str1);
            
            return;
        }
    }
    printf("Person named '%s' isn't exists.\n", str1);
}