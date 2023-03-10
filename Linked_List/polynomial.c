// 연결리스트를 이용해 다항식을 표현
// 만든 다항식을 이용할 수 있는 
// 간단한 수학 프로그램 작성

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_POLYS  25
#define BUFFER_LEN 100
#define TERM_LEN   15

// 다항식에서 각 항에 해당하는 구조체를 정의함
typedef struct term {
    int coef;   // 게수
    int expo;   // 지수
    struct term *next;
} TERM;

// 다항식 전체를 표현하기 위한 구조체
typedef struct polynomial {
    char name;     // 다항식의 이름은 알파벳 한 글자로 제한됨
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
char *erase_blanks(char *str);
POLY *create_by_parse(char name, char *body);
POLY *create_by_add_two_poly(char new_name, char former, char later);
void insert_poly(POLY *poly);
void destroy_poly(POLY *poly);
TERM *create_term();
POLY *create_poly(char name);
void add_term(POLY *poly, int c, int e);
int  calculate(POLY *poly, int x);
int  cal(TERM *ptr, int x);
void print_poly(POLY *poly);
void print_term(POLY *poly, TERM *ptr);


// 다항식의 이름은 알파벳 한 글자로 정함(a ~ z)
// 다항식간 연산은 덧셈(+)만 허용됨
int main(){
    process_command();

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
            printf("\n");
            continue;
        }  // "print" 명령

        else if(strcmp(command, "calc") == 0){
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
            continue;
        }  // "calc" 명령

        else if(strcmp(command, "exit") == 0){
            printf("Exit...\n");

            break;
        }  // "exit" 명령

        // 다항식을 정의하는 명령
        else{
            handle_define(command_copy);
            continue;
        }
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
    int i;
    printf("TEST:: polys[0]->name=%c\n", polys[0]->name);
    for(i = 0; i < n; i++){
        if(ch == polys[i]->name){
            print_poly(polys[i]);

            return;
        }
    }

    // match되는 이름의 poly가 없는 경우
    if(i == n){
        printf("Error : Polynomial '%c' isn't exists\n", ch);

        return;
    }
}

// 다항식 계산 함수
void handle_calc(char name, char *x_str){
    POLY *temp;

    // name이라는 다항식이 존재하는지 검색
    for(int i = 0; i < n; i++){
        if(name == polys[i]->name){
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
void handle_define(char equation[]){
    char *new_equation = erase_blanks(equation);
    printf("TEST:: ERASE_BLANK : %s\n\n", new_equation);
    char *poly_name = strtok(new_equation, "=");
    if((poly_name == NULL) || (strlen(poly_name) != 1)){
        printf("Error : You've written the unsupported name.\n");
        
        return;
    }

    char *body = strtok(NULL, "=");
    if((body == NULL) || (strlen(body) <= 0)){
        printf("Error : Invalid ewpression used after '=' .\n");
        
        return;
    }
    
    // g = f + h 처럼 기존 poly를 이용하여 새로운 poly를 정의하는 경우
    if((body[0] >= 'a') && (body[0] <= 'z') && (body[0] != 'x')){
        char *former = strtok(body, "+");
        if((former == NULL) || (strlen(former) != 1)){
            printf("Error : Invalid ewpression format.(1)\n");
            return;
        }

        char *later = strtok(NULL, "+");
        if((later == NULL) || (strlen(later) != 1)){
            printf("Error : Invalid ewpression format.(2)\n");
            return;
        }

        POLY *new = create_by_add_two_poly(poly_name[0], former[0], later[0]);
        if(new == NULL){
            printf("Error : Invalid expression format.(3)\n");

            return;
        }

        insert_poly(new);
    }

    // 새로운 poly를 정의하는 경우
    // g = ax^2 + bx + c 형식
    else{
        printf("TEST:: poly_name : %c\n", poly_name[0]);
        printf("TEST:: body      : %s\n", body);
        POLY *new = create_by_parse(poly_name[0], body);
        if(new == NULL){
            printf("Error : Invalid expression format.(4)\n");

            return;
        }

        insert_poly(new);
    }
}

// 전달받은 문자배열의 모든 공백 문자들을 제거하여 압축하고
// 문자열의 끝에 ‘\0’를 추가함
char *erase_blanks(char str[]){
    char *ptr;
    char *new;

    new = strtok(str, " ");

    while((ptr = strtok(NULL, " ")) != NULL){
        printf("TEST:: token : %s\n", ptr);
        strcat(new, ptr);
        printf("TEST:: string : %s\n", new);
    }
        printf("TEST:: final string : %s\n", new);
    if(ptr == NULL)
        return new;
}

// 다항식을 새로 정의하는 함수
POLY *create_by_parse(char name, char *body){
    POLY *ptr = create_poly(name);
    int i = 0, p = 0;
    int start_point = 0;
    int sign = 1;
    int coef = 0;
    int expo = 0;

    // 얻어진 하나의 항을 분석하여 TERM 으로서 저장
    while(i < strlen(body)){
        printf("TEST:: i=%d, start_point=%d, p=%d\n", i, start_point, p);
        if((body[i] == '+') || (body[i] == '-')){
            if(i != 0)
                p++;
            
            i++;
        }
        // 하나의 항이 끝날 때까지 전진
        while((i < strlen(body)) && (body[i] != '+') && (body[i] != '-')){
            i++;
        }   /*여기까지가 하나의 항을 구분하는 부분*/
        
        // 구분한 항 1개에 대한 분석 시작
        // 음수 계수이면 부호를 따로 기억
        if(body[start_point] == '-'){
            sign = -1;
            if(start_point == 0)
                p++;
        }
        
        printf("TEST:: 'i' is %d\n", i);
        printf("TEST:: 'p' is %d\n", p);
        // 항의 계수를 감지
        // 현재는 body 배열에 character 타입으로 나열되어 있는 상태
        while((body[start_point + p] >= '0') && (body[start_point + p] <= '9')){
            coef = (coef * 10) + ((int)body[start_point + p] - 48);  // 아스키코드가 가리키는 숫자를 실제 정수로 mapping
            p++;
            printf("TEST:: sign=%d, coef=%d \n", sign, coef);
        }
        printf("TEST:: 'p' is %d\n", p);
        // 상수항인 경우,
        // 미지수 x가 감지되지 않고
        // 다항식의 마지막이거나, 바로 다음 character가 +/- 이게 되므로
        if((i == (strlen(body))) || (body[start_point + p] == '+') || (body[start_point + p] == '-')){
            expo = 0;
            if(sign == -1)
                coef *= -1;

            printf("TEST:: sign=%d, coef=%d, expo=%d \n", sign, coef, expo);
            add_term(ptr, coef, expo);
            sign = 1;
            coef = 0;
            expo = 0;
            start_point += p;
            p    = 0;
            
            
            continue;
        }

        // 미지수 x 감지
        if(body[start_point + p] != 'x'){
            destroy_poly(ptr);
            printf("TEST:: 'p' is %d\n", p);
            printf("TEST:: sign=%d, coef=%d \n", sign, coef);
            printf("Error : Invalid expression format.(4)-1\n");
            return NULL;
        }
        else
            p++;
        printf("TEST:: 'p' is %d\n", p);

        // ^ 기호 감지
        // 1차식일 경우 ^가 없는 경우 포함
        if((body[start_point + p - 1] == 'x') && (body[start_point + p] != '^')){
            expo = 1;
            if(sign == -1)
                coef *= -1;
            printf("TEST:: sign=%d, coef=%d, expo=%d \n", sign, coef, expo);
            add_term(ptr, coef, expo);
            sign = 1;
            coef = 0;
            expo = 0;
            start_point += p;
            p    = 0;

            continue;
        }
        else if((body[start_point + p - 1] == 'x') && (body[start_point + p] == '^'))
            p++;
        else
            p++;

        // 항의 차수를 감지
        while((body[start_point + p] >= '0') && (body[start_point + p] <= '9')){
            expo = (expo * 10) + ((int)body[start_point + p] - 48);  // 아스키코드가 가리키는 숫자를 실제 정수로 mapping
            p++;
            printf("TEST:: sign=%d, coef=%d, expo=%d \n", sign, coef, expo);
        }

        //////////////////////////////////////////////////////
        // FOR DEBUGGING
        if((start_point + p) != i){
            printf("TEST ERROR");
        }
        //////////////////////////////////////////////////////

        // 최종적으로 항 1개를 확정짓는 부분
        if(sign == -1)
            coef *= -1;
        
        printf("TEST:: sign=%d, coef=%d, expo=%d \n", sign, coef, expo);
        add_term(ptr, coef, expo);
        sign = 1;
        coef = 0;
        expo = 0;
        start_point += p;
        p    = 0;

        continue;
    }

    return ptr;
}

// 이미 존재하는 두 다항식을 더하여 새로운 다항식을 만드는 함수 
POLY *create_by_add_two_poly(char new_name, char former, char later){
    POLY *temp1;
    POLY *temp2;

    // 새로운 poly를 위한 동적 할당
    POLY *new = create_poly(new_name);

    // former과 later에 해당하는 poly 맵핑시키기
    for(int i = 0; i < n; i++){
        if(former == polys[i]->name){
            temp1 = polys[i];    
        }
        if(later == polys[i]->name){
            temp2 = polys[i];    
        }
    }
    // 우변에 작성한 다항식중 존재하지 않는 다항식이 포함된 경우
    if((temp1 == NULL) || (temp2 == NULL)){
        printf("Error : Equation's right-handed side contains undefined polynomial.\n");
        
        return NULL;
    }

    // 두 다항식을 더하는 부분
    int i = 0;
    int size_1 = temp1->size;
    int size_2 = temp2->size;
    TERM *ptr1 = temp1->first;
    TERM *ptr2 = temp2->first;
    
    if(ptr1->expo > ptr2->expo){
        add_term(new, ptr1->coef, ptr1->expo);
        ptr1 = ptr1->next;
        i++;

        while((i <= size_1) && (ptr1 != NULL)){
            if(ptr1->expo > ptr2->expo){
                add_term(new, ptr1->coef, ptr1->expo);
                ptr1 = ptr1->next;
                i++;

                continue;
            }

            else if(ptr2->expo > ptr1->expo){
                add_term(new, ptr2->coef, ptr2->expo);
                ptr2 = ptr2->next;

                continue;
            }

            else if(ptr1->expo == ptr2->expo){
                add_term(new, ptr1->coef + ptr2->coef, ptr1->expo);
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
                i++;

                continue;
            }
        }
    }// former 다항식이 더 고차항을 가짐

    if(ptr2->expo > ptr1->expo){
        add_term(new, ptr2->coef, ptr2->expo);
        ptr2 = ptr2->next;
        i++;

        while((i <= size_2) && (ptr2 != NULL)){
            if(ptr2->expo > ptr1->expo){
                add_term(new, ptr2->coef, ptr2->expo);
                ptr2 = ptr2->next;
                i++;

                continue;
            }

            else if(ptr1->expo > ptr2->expo){
                add_term(new, ptr1->coef, ptr1->expo);
                ptr1 = ptr1->next;

                continue;
            }

            else if(ptr1->expo == ptr2->expo){
                add_term(new, ptr1->coef + ptr2->coef, ptr1->expo);
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
                i++;

                continue;
            }
        }
    }// later 다항식이 더 고차항을 가짐

    else if(ptr1->expo == ptr2->expo){
        // i의 기준값은 size_1, size_2 모두 가능
        add_term(new, ptr1->coef + ptr2->coef, ptr1->expo);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        i++;

        while((i <= size_1) && (ptr1 != NULL)){
            if(ptr1->expo > ptr2->expo){
                add_term(new, ptr1->coef, ptr1->expo);
                ptr1 = ptr1->next;
                i++;

                continue;
            }

            else if(ptr2->expo > ptr1->expo){
                add_term(new, ptr2->coef, ptr2->expo);
                ptr2 = ptr2->next;

                continue;
            }

            else if(ptr1->expo == ptr2->expo){
                add_term(new, ptr1->coef + ptr2->coef, ptr1->expo);
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
                i++;

                continue;
            }
        }
    }// 두 다항식의 최고차수가 같은 경우
}

// 새로 만든 다항식을 polys 배열에 추가하는 함수
// 덮어쓰는 기능도 함
void insert_poly(POLY *poly){
    if(n == 0){
        polys[n] = poly;
        n++;
        printf("TEST:: poly name=%c\n", polys[0]->name);
        return;
    }
    for(int i = 0; i < n; i++){
        // 덮어쓰는 경우
        if(poly->name == polys[i]->name){
            destroy_poly(polys[i]);
            polys[i] = poly;

            return;
        }

        // 새로운 다항식이 추가되는 경우
        // 다항식들 자체는 알파벳 순으로 배열하지 않음
        polys[n] = poly;
        n++;
    }
}

// polys 배열에 저장되어 있는 다항식을 지우는 함수
void destroy_poly(POLY *poly){
    if(poly == NULL)
        return;
    
    TERM *tmp1 = poly->first;
    TERM *tmp2;

    while(tmp1 != NULL){
        tmp2 = tmp1;
        tmp1 = tmp1->next;
        free(tmp2);
    }
    free(poly);

    return;
}

// 새 term 구조체 공간을 동적 할당받고
// 멤버들을 초기화 시키는 함수
// (동적으로 생성된 객체를 적절히 초기화하지 않는 것은
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
POLY *create_poly(char name){
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
    printf("%c = ", poly->name);
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
    if((ptr != NULL) && (ptr != poly->first) && (ptr->coef > 0)){
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

