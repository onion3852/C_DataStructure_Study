// 연결리스트를 이용해 다항식을 표현
// 만든 다항식을 이용한 간단한 수학 프로그램 작성

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_POLYS  25
#define BUFFER_LEN 100

// 다항식에서 각 항에 해당하는 구조체를 정의함
typedef struct term {
    int coef;   // 게수
    int expo;   // 지수
    struct term *next;
} TERM;

// 다항식 전체를 표현하기 위한 구조체
typedef struct polynomial {
    char *name;     // 다항식의 이름은 알파벳 한 글자로 제한됨
    TERM *first;    // 다항식의 첫 항을 가리키도록 함
    int size;
} POLY;

POLY *polys[MAX_POLYS];  // 다항식들로 구성한 배열(배열의 이름이 polys)
int n = 0;  // 저장된 다항식들의 개수


void process_command();
int  read_line(FILE *fp, char *str, int limit);
void handle_print(char ch);
void handle_calc(char name, char *x_str);
void handle_define(char *equation);
void erase_blanks(char *str);
TERM *create_term();
POLY *create_poly(char *name);
void add_term(POLY *poly, int c, int e);
int  calculate(POLY *poly, int x);
int  cal(TERM *ptr, int x);
void print_poly(POLY *poly);
void print_term(POLY *poly, TERM *ptr);



int main(){

    return 0;
}


///////////////////////////////////////////////////////////////////////
// FUNCTION
//////////////////////////////////////////////////////////////////////

// 프롬프트 명령을 처리하는 함수
void process_command(){
    char command_line[BUFFER_LEN];
    char command_copy[BUFFER_LEN];
    char *command;
    char *arg1;
    char *arg2;

    while(1){
        printf("$ ");

        // 아무것도 입력되지 않은 경우
        if(read_line(stdin, command_line, BUFFER_LEN) <= 0)
            continue;

        strcpy(command_copy, command_line);  // copy the command for further use
        command = strtok(command_copy, " ");

        if(strcmp(command, "print") == 0){
            arg1 = strtok(NULL, " ");

            if(arg1 == NULL){
                printf("Error : Polynomial name is required\n");
                continue;
            }

            handle_print(arg1[0]);
        }  // "print" 명령

        else if(strcmp(command, "calc")){
            arg1 = strtok(NULL, " ");   // poly name

            if(arg1 == NULL){
                printf("Error : Polynomial name is required\n");
                continue;
            }

            arg2 = strtok(NULL, " ");   // value for x
            if(arg2 == NULL){
                printf("Error : value for 'x' is required\n");
                continue;
            }

            handle_calc(arg1[0], arg2);
        }  // "calc" 명령

        else if(strcmp(command, "exit") == 0){
            printf("Exit...\n");

            break;
        }  // "exit" 명령

        // 다항식을 정의하는 명령
        else
            handle_define(command_copy);
    }   
}

// 프롬프트에 작성한 명령을 읽어들이는 함수
int read_line(FILE *fp, char *str, int limit){
    int ch;  // getchar()의 리턴은 int type이어야 한다는 점 주의
    int i = 0;

    // 두 번째 조건식은 파일을 읽을 때 필요
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

// 다항식 출력 함수
void handle_print(char ch){
    int i = 0;

    while((strcmp(&ch, polys[i]->name) != 0)){
        i++;
    }
    // match되는 이름의 poly가 없는 경우
    if(i == n){
        printf("Error : Polynomial '%c' isn't exists\n", ch);

        return;
    }
    
    printf("%s = ");
    print_poly(polys[i]);
}

// 다항식 계산 함수
void handle_calc(char name, char *x_str){
    POLY *temp;

    // name이라는 다항식이 존재하는지 검색
    for(int i = 0; i < n; i++){
        if(strcmp(&name, polys[i]->name) == 0){
            temp = polys[i];

            break;
        }
    }

    if(temp != NULL){
        int x = (int)x_str;
        int result = calculate(temp, x);
        printf("calculation result : %c = %d\n", name, result);
    }

    else
        printf("Error : Polynomial name '%c' not found.\n", name);
}

// 다항식 정의 함수
void handle_define(char *equation){
   erase_blanks(equation);

}

// 전달받은 문자배열의 모든 공백 문자들을 제거하여 압축하고
// 문자열의 끝에 ‘\0’를 추가함
void erase_blanks(char *str){
    char *ptr;
    int length = 0;

    ptr = strtok(str, " ");
    strcpy();
        
}

// 새 term 구조체 공간을 동적 할당받고
// 멤버들을 초기화 시키는 함수
// (동적으로 생성된 객체를 적절히 초기화하지 않는 것이
// 프로그램의 오류를 야기할 수도 있음)
TERM *create_term(){
    TERM *ptr = (TERM *)malloc(sizeof(TERM));
    ptr->coef = 0;
    ptr->expo = 0;
    ptr->next = NULL;

    return ptr;
}

// 새 polynomial 구조체 공간을 동적 할당받고
// 멤버들을 초기화 시키는 함수
// 이 경우는 다항식의 이름을 지정하면서(매개변수) 생성하도록 함
POLY *create_poly(char *name){
    POLY *ptr  = (POLY *)malloc(sizeof(POLY));
    ptr->name  = name;
    ptr->size  = 0;
    ptr->first = NULL;

    return ptr;
}

// 다항식에 새로운 항을 추가하는 함수
// 두 가지 케이스가 있음
// 1) 동일한 차수의 항이 있어, 계수 계산을 하는 경우
// 2) 새로운 차수의 항이 추가되는 경우(차수에 대해 내림차순 정렬해야 함) 
void add_term(POLY *poly, int c, int e){
    if(c == 0)
        return;
    
    TERM *tmp1 = poly->first;
    TERM *tmp2 = NULL;

    while((tmp1 != NULL) && (tmp1->expo > e)){
        tmp2 = tmp1;
        tmp1 = tmp1->next;
    }   // 동일 차수 항이 있든 없든 모두 while문을 빠져나오긴 함

    // 동일한 차수항이 있는 경우
    if((tmp1 != NULL) && (tmp1->expo == e)){
        tmp1->coef += c;

        // 계수 계산 결과가 0인 경우
        if(tmp1->coef == 0){
            if(tmp2 == NULL)  // 다항식 전체가 0이 되는 경우
                poly->first = tmp1->next;  //(= NULL)
            else
                tmp2->next = tmp1->next;
            
            poly->size--;
            free(tmp1);
        }
        return;
    }

    // 새로운 차수의 항이 추가되는 경우
    // tmp2 노드의 다음 노드에 새로운 노드를 추가하는 상황
    TERM *term = create_term();
    term->coef = c;
    term->expo = e;

    if(tmp2 == NULL)  // 첫 번째 항으로서 추가되는 경우
        poly->first = term;
    else{
        term->next = tmp1;
        tmp2->next = term;
    }
    poly->size++;
    
    return;
}

// 다항식을 계산하는 함수
// 다항식과 미지수를 선택
int calculate(POLY *poly, int x){
    int result = 0;
    TERM *p = poly->first;

    while(p != NULL){
        result += cal(p, x);
        p = p->next;
    }

    return result;
}

// 특정 항에 대한 계산을 하는 함수
int cal(TERM *ptr, int x){
    int value = ptr->coef;

    for(int i = 0; i < ptr->expo; i++)
        value *= x;
    
    return value;
}

// 다항식을 터미널에 출력하는 함수
void print_poly(POLY *poly){
    printf("%s = ", poly->name);
    TERM *p = poly->first;

    while(p != NULL){
        print_term(poly, p);
        p = p->next;
    }
}

// 각 항을 print하는 함수
// +/-, 1제곱, 0제곱 등의 예외 판단 기능을 포함
void print_term(POLY *poly, TERM *ptr){
    char sign;

    // + 부호 출력여부 판단
    if((ptr != poly->first) && (ptr->coef > 0)){
        printf("+");
    }

    printf("%d", ptr->coef);

    // 차수가 1인 경우
    if(ptr->expo == 1){
        printf("x ");
        
        return;
    }
    // 차수가 0인경우
    else if(ptr->expo == 0){
        return;
    }
    // 차수가 2이상인 경우
    else
        printf("x^%d ", ptr->expo);

    return;
}

