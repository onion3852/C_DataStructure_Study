// version_3

//////////////////////////////////////////////////////////////////////////////
// 명령을 라인 단위로 받는 방식으로 변경
// 즉, 프롬프트에 입력하고 엔터키 입력하면 통째로 명령을 입력 받는 것임
// 잘못된 명령어(완전하지 않은 format 등)에 대한 반응 추가

// 받은 명령문자열을 작은 문자열들로 tokenizing 하는 기능 추가
// <string.h> 에서 제공하는 strtok()함수 이용

// 배열 재할당 기능 추가
// 저장된 사람의 수가 배열 용량을 초과할 경우, 동적메모리 할당으로 더 큰 배열 만들기
// 동적메모리 할당을 이용할 경우를 대비해 names와 numbers 자료구조의 변화가 필요
// version_2의 names와 numbers는 배열로 선언된 상태이므로
// 배열의 이름이자 포인터 변수인 names, numbers는 값을 바꿀 수 없기 때문임
// 따라서 names와 numbers의 배열을 포인터로써 정의해야함
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPA   3    // 배열 재할당 기능을 테스트하기 위해, 매우 작은 수로 설정함
#define MAX_DATA    100
#define BUFFER_SIZE 50

char **names  ;    // names는 char* 타입 배열의 '이름', 즉, char** 타입 변수
char **numbers;    // numbers는 char* 타입 배열의 '이름', 즉, char** 타입 변수

char *delim = " ";  // strtok()의 2nd argument인 delimiter로서 공백문자를 쓸 것임
int n    = 0;       // number of stored data(저장된 사람 수와 같음)
int capa = INIT_CAPA;

void init_directory();  // 배열 names와 numbers 생성
void reallocate();      // 배열 재할당 기능
void process_command();
int  read_line(char *str, int limit);
void add(char *str1, char *str2);
void find(char *name);
void status();
void delete(char *name);
void load(char *filename);
void save(char *as, char*filename);
int  search();


int main(){
    
    init_directory();
    process_command();

    return 0;
}


///////////////////////////////////////////////////////////////
// Function declaration
///////////////////////////////////////////////////////////////

void init_directory(){
    names   = (char **)malloc(INIT_CAPA * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPA * sizeof(char *));
}

void process_command(){
    char command_line [BUFFER_SIZE];  // 한 라인을 전부 읽어오기 위한 buffer
    char *command;
    char *argument_1;
    char *argument_2;

    while(1){
        printf("$ ");
        if(read_line(command_line, BUFFER_SIZE) <= 0)
            continue;   // 프롬프트에서 바로 엔터키를 누른 경우에 해당
        
        command = strtok(command_line, delim);
        if(strcmp(command, "read") == 0){
            argument_1 = strtok(NULL, delim);
            if(argument_1 == NULL){
                printf("Error : File name is required.\n");
                continue;
            }
            load(argument_1);
        }// "command == read"

        else if(strcmp(command, "add") == 0){
            argument_1 = strtok(NULL, delim);
            if(argument_1 == NULL){
                printf("Error : Person name and phone number are required\n");
                continue;
            }
            argument_2 = strtok(NULL, delim);
            if(argument_2 == NULL){
                printf("Error : Phone number is required\n");
                continue;
            }
            add(argument_1, argument_2);
        }// "command == add"

        else if(strcmp(command, "find") == 0){
            argument_1 = strtok(NULL, delim);
            if(argument_1 == NULL){
                printf("Error : Person name is required\n");
                continue;
            }
            find(argument_1);
        }// "command == find"

        else if(strcmp(command, "status") == 0){
            status();
        }// "command == status"

        else if(strcmp(command, "delete") == 0){
            argument_1 = strtok(NULL, delim);
            if(argument_1 == NULL){
                printf("Error : Person name is required\n");
                continue;
            }
            delete(argument_1);
        }// "command == delete"

        else if(strcmp(command, "save") == 0){
            argument_1 = strtok(NULL, delim);
            if(argument_1 == NULL){
                printf("Error : Word 'as' is required\n");
                continue;
            }
            argument_2 = strtok(NULL, delim);
            if(argument_2 == NULL){
                printf("Error : File name is required\n");
                continue;
            }
            save(argument_1, argument_2);
        }// "command == save"

        else if(strcmp(command, "exit") == 0)
            break;
    }
}

int read_line(char *str, int limit){
    int ch;  // getchar()의 리턴은 int type이어야 한다는 점 주의
    int i = 0;

    while((ch = getchar()) != '\n'){
        if(i < limit - 1)
        str[i] = ch;
        i++;
    }
    // 만약 i 가 'limit' 까지 증가
    // 또는 i 가 0일 때 \n 만날 경우
    str[i] = '\0';

    return i;
}

void add(char *name, char *number){
    if(n >= capa)
        reallocate();

    int i, p;

    // 알파벳 순서대로 정렬하기 위한 part
    i = search(name);
    if(i >= 0){
        printf("Person named '%s' already exists. Try other name.\n", name);

        return;
    }

    // 새로운 사람일 경우
    for(i = 0; i < n; i++){
        if(strcmp(name, names[i]) < 0){
            for(p = n - 1; p > i - 1; p--){
                names  [p + 1] = names[p];
                numbers[p + 1] = numbers[p];
            }
            names[i]   = strdup(name);
            numbers[i] = strdup(number);
            n++;
            printf("%s was added successfully.\n", name);

            return;
        }
    }
    // 만약 가장 마지막 순서의 이름일 경우
    names[n]   = strdup(name);
    numbers[n] = strdup(number);
    n++;
    printf("%s was added successfully.\n", name);
}

void find(char *name){
    int i;

    if((i = search(name)) >= 0){
        printf("%s's number is %s.\n",names[i], numbers[i]);
        return;
    }
    printf("Person named '%s' isn't exists.\n", name);
}

void status(){
    int i;

    for(i = 0; i < n; i++)
        printf("%s : %s\n", names[i], numbers[i]);

    printf("Total %d persons.\n", n);
}

void delete(char *name){
    int i;

    if((i = search(name)) >= 0){
        for(; i < n - 1; i++){
            names[i]   = names[i + 1];
            numbers[i] = numbers[i + 1];
            n--;
            printf("'%s' was deleted successfully.\n", name);
            
            return;
        }
        // if i == n
        names[i]   = '\0';
        numbers[i] = '\0';
        n--;
        printf("'%s' was deleted successfully.\n", name);
            
        return;
    }
    printf("Person named '%s' isn't exists.\n", name);
}

void load(char *filename){
    // 파일을 불러오기 위해 호출되는 함수
    // read 명령의 format은
    // read <file_name>
    char buf1 [BUFFER_SIZE];
    char buf2 [BUFFER_SIZE];

    // 파일에 접근하기 위해 파일 open
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Open failed,\n");
        return;
    }

    // 파일의 끝에 도달할 때 까지 반복해서
    // 이름과 전화번호를 읽어 배열에 저장함
    while((fscanf(fp, "%s", buf1) != EOF)){
        fscanf(fp, "%s", buf2);
        names[n]   = strdup(buf1);
        numbers[n] = strdup(buf2);
        n++;
    }
    // 파일 close
    fclose(fp);
}

void save(char *as, char*filename){
    // save 명령의 입력 format은 
    // save as <file_name>
    int i;

    // 파일에 write하기 위해 파일 open
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Open failed.\n");
        return;
    }

    for(i = 0; i < n; i++){
        fprintf(fp, "%s ", names[i]);
        fprintf(fp, "%s\n", numbers[i]);
    }
    printf("%s was saved successfully.\n", filename);
    fclose(fp);
}

int search(char *name){
    // function 내부에서 활용할,
    // 전화번호부 내부 이름 검색 함수
    int index;

    for(index = 0; index < n; index++){
        if(strcmp(name, names[index]) == 0)
            return index;
            // 동일한 이름을 찾으면 
            // names 배열에서의 해당 index return
    }
    // if same name isn't exists, return -1
    return -1;
}

void reallocate(){
    // 전화번호부 배열 용량 초과 시,
    // 배열 재할당하여 더 큰 배열로 대체하는 함수
    capa *= 2;
    int i;

    char **ptr1;    // names에 대응됨
    char **ptr2;    // numbers에 대응됨

    ptr1 = (char **)malloc(capa * sizeof(char *));
    ptr2 = (char **)malloc(capa * sizeof(char *));

    for(i = 0; i < n; i++){
        ptr1[i] = names[i];
        ptr2[i] = numbers[i];
    }
    free(names);
    free(numbers);

    names   = ptr1;
    numbers = ptr2;
}