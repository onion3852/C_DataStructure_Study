// version_4

//////////////////////////////////////////////////////////////////////////////
// 기존의 자료구조(배열) 대신에
// 구조체를 사용하여 더 많은 항목 저장(이메일, 그룹)
// (이떄, 이메일과 그룹은 필수 항목은 아님)
// 파일에 저장할 때는 '#'를 기준으로 항목들이 구분됨
// 만약 이메일 혹은 그룹을 입력하지 않았다면 공백문자 1칸으로 저장함
// 즉, 파일 한 줄은 다음과 같은 형식 : 이름#번호#메일#그룹#

// 이름도 여러 단어가 가능하도록 수정
// 따라서 add 명령의 사용자 인터페이스의 수정이 필요
// 그리고 단어들 사이의 공백이 여러개 이더라도 하나로 취급하는 기능 구현

// read_line함수는 키보드 입력뿐 만이 아니라
// 파일도 읽을 수 있게 수정
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPA   3    // 배열 재할당 기능을 테스트하기 위해, 매우 작은 수로 설정함
#define MAX_DATA    100
#define BUFFER_SIZE 50


typedef struct person
{
    char *name;
    char *number;
    char *email;
    char *group;
} PERSON;

PERSON data [MAX_DATA];  // struct로 정의된 PERSON 타입의 배열(크기 100)을 선언
int n = 0;               // number of stored data(저장된 사람 수와 같음)

char **names  ;    // names는 char* 타입 배열의 '이름', 즉, char** 타입 변수
char **numbers;    // numbers는 char* 타입 배열의 '이름', 즉, char** 타입 변수

char *delim = " ";  // strtok()의 2nd argument인 delimiter로 공백문자를 쓸 것임

int capa = INIT_CAPA;

void init_directory();  // 배열 names와 numbers 생성
void reallocate();      // 배열 재할당 기능
void process_command();
int  read_line(FILE *fp, char *str, int limit);
void add(char *str1, char *str2, char *str3, char *str4);
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
        if(read_line(stdin, command_line, BUFFER_SIZE) <= 0)
            continue;   // 키보드 이용시, 프롬프트에서 바로 엔터키를 누른 경우에 해당
        
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

// 표준 입력을 이용할 경우 파일 포인터는 stdin
int read_line(FILE *fp, char *str, int limit){
    int ch;  // getchar()의 리턴은 int type이어야 한다는 점 주의
    int i = 0;

    // while문 두 번째 조건식은 파일을 읽을 때 필요
    while( ((ch = fgetc(fp)) != '\n') && (ch != EOF) ){
        if(i < limit - 1)
            str[i] = ch;

        i++;
    }
    // 만약 i 가 'limit' 까지 증가
    // 또는 i 가 0일 때 \n 만날 경우
    str[i] = '\0';

    return i;
}

void add(char *str1, char *str2, char *str3, char *str4){
    int i, p;

    // 알파벳 순 정렬
    for(i = 0; i < n; i++){
        if(strcmp(str1, data[i].name) < 0){
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
    char temp [BUFFER_SIZE];
    char *buf1;  // 이름
    char *buf2;  // 번호
    char *buf3;  // 이메일
    char *buf4;  // 그룹

    // 파일에 접근하기 위해 파일 open
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Open failed,\n");
        return;
    }

    while(1){
        if(read_line(fp, temp, BUFFER_SIZE) <= 0)
            break;
        buf1 = strtok(temp, "#");
        buf2 = strtok(NULL, "#");        
        buf3 = strtok(NULL, "#");
        buf4 = strtok(NULL, "#");

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