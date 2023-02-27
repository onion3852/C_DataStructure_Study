// version_5

//////////////////////////////////////////////////////////////////////////////
// 더 효율적인 방식으로 만들고자,
// 구조체가 아니라 구조체에 대한 포인터를 사용
// 따라서 새로운 연산자 " -> " 를 사용하게됨

//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPA   100
#define BUFFER_SIZE 50

typedef struct person
{
    char *name;
    char *number;
    char *email;
    char *group;
} PERSON;

// 전화번호부의 데이터 자료구조 선언시 포인터를 이용함
// PERSON 포인터 타입의 배열을 만드는데,
// 그 배열을 포인터 방식으로 선언한 것
PERSON ** data;

int capa;
int n;           // number of stored data(저장된 사람 수와 같음)
char *delim = " ";  // strtok()의 2nd argument인 delimiter로 공백문자를 쓸 것임

// functions
void init();
int  read_line(FILE *fp, char *str, int limit);
int  compose_name(char str[], int limit);
void add_else(char *name);
void add(char *str1, char *str2, char *str3, char *str4);
void reallocate();
void find(char *name);
void print_find(PERSON *p);
void status();
void delete(char *name);
void release_person(PERSON *ptr);
void load(char *filename);
void save(char*filename);
int  search(char *str);


int main(){
    char command_line [BUFFER_SIZE];  // 한 라인을 전부 읽어오기 위한 buffer
    char *command;
    char *argument;
    char str_name [BUFFER_SIZE];    // char *str_name 으로 선언할 경우, 첫 명령시 add ~ 할 때, 
                                    // str_name이 null값을 가리키므로(?) segmentation fault 오류 발생하는 듯 
    
    // 동적메모리 할당을 통해 초기 메모리 확보 
    data = (PERSON **)malloc(INIT_CAPA * sizeof(PERSON *));
    capa = INIT_CAPA;
    n    = 0;

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

    printf("If you wish to add more informations, write the followings.\n");
    printf("Type 'Enter' button to skip.\n");

    printf("  Phone : ");
    read_line(stdin, number, BUFFER_SIZE);
    
    printf("  Email : ");
    read_line(stdin, email, BUFFER_SIZE);
    
    printf("  Group : ");
    read_line(stdin, group, BUFFER_SIZE);
    
    // 입력하지 않은 항목에 대해선 공백문자로 대신함
    add(name, (char *)(strlen(number) > 0 ? number : NULL),
              (char *)(strlen(email ) > 0 ? email  : NULL),
              (char *)(strlen(group ) > 0 ? group  : NULL));
}

void add(char *str1, char *str2, char *str3, char *str4){
    // 데이터를 전화번호부 자료구조에 추가하는 함수

    if(n >= capa)
        reallocate();

    int i;
    int p = 0;

    // 첫 add 실행 시
    if(n == 0){
        i = 0;
        data[i] = (PERSON *)malloc(sizeof(PERSON));
        // data는 구조체의 포인터에 대한 배열이므로
        // strdup를 사용하지 않음
        data[i]->name   = str1;        
        data[i]->number = str2;
        data[i]->email  = str3;
        data[i]->group  = str4; 
        n++;

        return;       
    }

    // 알파벳 순 정렬
    i = n - 1;
    while((i >= 0) && (strcmp(data[i]->name, str1) > 0)){
        data[i + 1] = data[i];
        i--;
    }
    p = i + 1;  // p가 새로운 데이터의 인덱스임

    // 새로운 데이터를 저장할 구조체 공간이 있는 것은 아니므로
    // 동적할당을 통해 이를 만들어줌
    // 처음에 정의한 것은 구조체의 포인터들에 대한 배열이고
    // 새로운 데이터가 저장되어야 할 때는
    // 새로운 구조체를 만들어 놓고 포인터를 지정해주는 것임
    data[p] = (PERSON *)malloc(sizeof(PERSON));

    data[p]->name   = str1;
    data[p]->number = str2;
    data[p]->email  = str3;
    data[p]->group  = str4;
    n++;

    return;    
}

void reallocate(){
    capa *= 2;
    PERSON **temp = (PERSON **)malloc(capa * sizeof(PERSON *));
    for(int i = 0; i < n; i++){
        temp[i] = data[i];
    }
    free(data);
    data = temp;
}

void find(char *name){
    int i;

    if((i = search(name)) >= 0){
        print_find(data[i]);
        return;
    }
    printf("Person named '%s' isn't exists.\n", name);
}

int search(char *str){
    // function 내부에서 활용할,
    // 전화번호부 내부 이름 검색 함수
    int index;

    for(index = 0; index < n; index++){
        if(strcmp(str, data[index]->name) == 0)
            return index;
            // 동일한 이름을 찾으면 
            // names 배열에서의 해당 index return
    }
    // if same name isn't exists, return -1
    return -1;
}

void print_find(PERSON *p){  // 구조체의 포인터를 매개로 하는 함수 이용 방법
    printf("%s\n", p->name);
    printf("Phone : %s\n", p->number);
    printf("Email : %s\n", p->email);
    printf("Group : %s\n", p->group);
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
        PERSON *p = data[i];

        for(; i < n-1; i++){
            data[i] = data[i + 1];
        }
        n--;
        release_person(p);
        printf("'%s' was deleted successfully.\n", name);
            
        return;
        
        // if i == n-1
        p = data[i];
        data[i]->name   = NULL;
        data[i]->number = NULL;
        data[i]->email  = NULL;
        data[i]->group  = NULL;
        n--;
        release_person(p);
        printf("'%s' was deleted successfully.\n", name);
            
        return;
    }
    printf("Person named '%s' isn't exists.\n", name);
}

void release_person(PERSON *ptr){
free(ptr->name);    
free(ptr->number);
free(ptr->email);
free(ptr->group);
free(ptr);
}

void load(char *filename){
    // 파일을 불러오기 위해 호출되는 함수
    // read 명령의 format은
    // read <file_name>
    char temp [BUFFER_SIZE];
    char *token;
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

        token = strtok(NULL, "#");
        if(strcmp(token, " ") == 0)
            buf2 = NULL;
        else
            buf2 = strdup(token);

        token = strtok(NULL, "#");
        if(strcmp(token, " ") == 0)
            buf3 = NULL;
        else
            buf3 = strdup(token);
        
        token = strtok(NULL, "#");
        if(strcmp(token, " ") == 0)
            buf4 = NULL;
        else
            buf4 = strdup(token);

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
        fprintf(fp, "%s#", data[i]->name);
        fprintf(fp, "%s#", data[i]->number);
        fprintf(fp, "%s#", data[i]->email);
        fprintf(fp, "%s#\n", data[i]->group);
    }
    printf("%s was saved successfully.\n", filename);
    fclose(fp);
}