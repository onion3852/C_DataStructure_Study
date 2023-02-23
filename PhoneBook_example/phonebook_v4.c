// version_4

//////////////////////////////////////////////////////////////////////////////
// 기존의 자료구조(배열) 대신에
// 구조체를 사용하여 더 많은 항목 저장(이메일, 그룹)
// (이떄, 번호, 이메일과 그룹은 필수 항목은 아님)
// 파일에 저장할 때는 '#'를 기준으로 항목들이 구분됨
// 만약 번호, 이메일 혹은 그룹을 입력하지 않았다면 공백문자 1칸으로 저장함
// 즉, 파일 한 줄은 다음과 같은 형식 : 이름#번호#메일#그룹#

// 이름도 여러 단어가 가능하도록 수정
// 따라서 add 명령의 사용자 인터페이스의 수정이 필요
// 그리고 명령 입력시, 단어 사이의 연속된 공백이 있더라도 하나로 취급하는 기능 구현

// read_line함수는 키보드 입력뿐 만이 아니라
// 파일도 읽을 수 있게 수정
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
char *delim = " ";  // strtok()의 2nd argument인 delimiter로 공백문자를 쓸 것임

// functions
int  read_line(FILE *fp, char *str, int limit);
int  compose_name(char str[], int limit);
void add_else(char *name);
void add(char *str1, char *str2, char *str3, char *str4);
void find(char *name);
void print_find(PERSON p);
void status();
void delete(char *name);
void load(char *filename);
void save(char*filename);
int  search(char *str);


int main(){
    char command_line [BUFFER_SIZE];  // 한 라인을 전부 읽어오기 위한 buffer
    char *command;
    char *argument;
    char str_name [BUFFER_SIZE];    // char *str_name 으로 선언할 경우, 첫 명령시 add ~ 할 때, 
                                    // str_name이 null값을 가리키므로(?) segmentation fault 오류 발생하는 듯 

    while(1){
        printf("$ ");
        if(read_line(stdin, command_line, BUFFER_SIZE) <= 0)
            continue;   // 키보드 이용시, 프롬프트에서 바로 엔터키를 누른 경우에 해당
        
        command = strtok(command_line, delim);
        if(strcmp(command, "read") == 0){
            argument = strtok(NULL, delim);
            if(argument == NULL){
                printf("Error : File name is required.\n");
                continue;
            }
            load(argument);
        }// "command == read"

        else if(strcmp(command, "add") == 0){
            if(compose_name(str_name, BUFFER_SIZE) <= 0){
                printf("Error : Person name is required\n");
                continue;
            }
            add_else(str_name);
            }// "command == add"

        else if(strcmp(command, "find") == 0){
            if(compose_name(str_name, BUFFER_SIZE) <= 0){
                printf("Error : Person name is required\n");
                continue;
            }
            find(str_name);
        }// "command == find"

        else if(strcmp(command, "status") == 0){
            status();
        }// "command == status"

        else if(strcmp(command, "delete") == 0){
            if(compose_name(str_name, BUFFER_SIZE) <= 0){
                printf("Error : Person name is required\n");
                continue;
            }
            delete(str_name);
        }// "command == delete"

        else if(strcmp(command, "save") == 0){
            argument = strtok(NULL, delim);
            if(strcmp(argument, "as") != 0){
                printf("Error : Argument 'as' is required\n");
                continue;
            }
            argument = strtok(NULL, delim);
            if(argument == NULL){
                printf("Error : File name is required\n");
                continue;
            }
            save(argument);
        }// "command == save"

        else if(strcmp(command, "exit") == 0)
            break;
    }

    return 0;
}


///////////////////////////////////////////////////////////////
// Function declaration
///////////////////////////////////////////////////////////////


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

int compose_name(char str[], int limit){
    // add, find, delete등의 명령에서 이름 입력 시
    // 불필요한 공백문자 없애고 
    // 연속된 공백문자를 하나로 취급하여
    // 정상적인 이름만을 만들어내기 위한 함수
    char *ptr;
    int length = 0;
    
    // strtok() for the command_line
    // 연속된 delimiter는 무시됨을 주의(version_3 2강 12분 참고)
    ptr = strtok(NULL, " ");
    if(ptr == NULL)
        return 0;   // add 뒤에 이름 입력이 없다는 의미
    
    // 이름에 띄어쓰기가 포함되는 경우 이용됨
    strcpy(str, ptr);
    length += strlen(ptr);
    while((ptr = strtok(NULL, " ")) != NULL){
        if(length + strlen(ptr) + 1 < limit){
            str[length] = ' ';
            length++;
            str[length] = '\0';
            strcat(str, ptr);
            length += strlen(ptr); 
        }
    }
    return length;
}

void add_else(char *name){
    // command가 add일 경우 사용되는 함수
    // 새로운 이름 string에 대해 나머지 항목(번호 etc)들을 추가시킴
    char number[BUFFER_SIZE];
    char email [BUFFER_SIZE];
    char group [BUFFER_SIZE];
    char empty [] = " ";

    printf("If you wish to add more informations, write the followings.\n");
    printf("Type 'Enter' button to skip.\n");

    printf("  Phone : ");
    read_line(stdin, number, BUFFER_SIZE);
    
    printf("  Email : ");
    read_line(stdin, email, BUFFER_SIZE);
    
    printf("  Group : ");
    read_line(stdin, group, BUFFER_SIZE);
    
    // 입력하지 않은 항목에 대해선 공백문자로 대신함
    add(name, (char *)(strlen(number) > 0 ? number : empty),
              (char *)(strlen(email ) > 0 ? email  : empty),
              (char *)(strlen(group ) > 0 ? group  : empty));
}

void add(char *str1, char *str2, char *str3, char *str4){
    // 데이터를 구조체에 추가하는 함수
    int i;

    // 첫 add 실행 시
    if(n == 0){
        i = 0;
        data[i].name   = strdup(str1);        
        data[i].number = strdup(str2);
        data[i].email  = strdup(str3);
        data[i].group  = strdup(str4); 
        n++;

        return;       
    }

    // 알파벳 순 정렬
    i = n - 1;
    while((i >= 0) && (strcmp(data[i].name, str1) > 0)){
        data[i + 1] = data[i];
        i--;
    }
    data[i].name   = strdup(str1);
    data[i].number = strdup(str2);
    data[i].email  = strdup(str3);
    data[i].group  = strdup(str4);
    n++;

    return;    
}

void find(char *name){
    int i;

    if((i = search(name)) >= 0){
        print_find(data[i]);
        return;
    }
    printf("Person named '%s' isn't exists.\n", name);
}

void print_find(PERSON p){  // 구조체를 매개로 하는 함수 이용 방법
    printf("%s\n", p.name);
    printf("Phone : %s\n", p.number);
    printf("Email : %s\n", p.email);
    printf("Group : %s\n", p.group);
}

void status(){
    int i;

    for(i = 0; i < n; i++)
        print_find(data[i]);

    printf("Total %d persons.\n", n);
}

void delete(char *name){
    int i;

    if((i = search(name)) >= 0){
        for(; i < n-1; i++){
            data[i] = data[i + 1];
            n--;
            printf("'%s' was deleted successfully.\n", name);
            
            return;
        }
        // if i == n-1
        data[i].name   = '\0';
        data[i].number = '\0';
        data[i].email  = '\0';
        data[i].group  = '\0';
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
        add(buf1, buf2, buf3, buf4);
    }
    // 파일 close
    fclose(fp);
}

void save(char*filename){
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
        fprintf(fp, "%s#", data[i].name);
        fprintf(fp, "%s#", data[i].number);
        fprintf(fp, "%s#", data[i].email);
        fprintf(fp, "%s#\n", data[i].group);
    }
    printf("%s was saved successfully.\n", filename);
    fclose(fp);
}

int search(char *str){
    // function 내부에서 활용할,
    // 전화번호부 내부 이름 검색 함수
    int index;

    for(index = 0; index < n; index++){
        if(strcmp(str, data[index].name) == 0)
            return index;
            // 동일한 이름을 찾으면 
            // names 배열에서의 해당 index return
    }
    // if same name isn't exists, return -1
    return -1;
}