// 연결 리스트를 수정(추가, 삭제 등)하는 다양한 함수들 만들기
// - 리스트의 n번쨰 주소를 반환
// - 리스트의 n번째 위치에 노드 삽입
// - 리스트의 n번째 노드를 삭제하고 그 노드의 데이터를 반환
// - 입력한 string을 가진 노드를 찾고 삭제하고 그 데이터 반환
// - 데이터가 순서대로 정렬되어 있을 때, 새 데이터(노드)를 순서에 맞게 삽입

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};

typedef struct node NODE;
NODE *head = NULL;

NODE *get_addr();
void insert_index();
char *delete_index();
char delete_word();
void insert_ordered();


int main(){
    // 초기에 3개의 노드가 있는 상황
    head = (NODE *)malloc(sizeof(NODE));
    head->data = "Apple";               
    head->next = NULL;  

    NODE *p = (NODE *)malloc(sizeof(NODE));
    p->data = "Car";
    p->next = NULL;
    head->next = p;

    NODE *q = (NODE *)malloc(sizeof(NODE));
    q->data = "Pizza";
    q->next = NULL;
    p->next = q;

    // 각 함수 순서대로, 1~2개씩 모두 이용하는 코드 작성


    return 0;
}


/////////////////////////////////////////////////////////////
// function declaration
/////////////////////////////////////////////////////////////

// 리스트의 n번쨰 주소를 반환
NODE *get_addr(){
    
}

// 리스트의 n번째 위치에 노드 삽입
void insert_index(){
    
}

// 리스트의 n번째 노드를 삭제하고 그 노드의 데이터를 반환
char *delete_index(){
    
}

// 입력한 string을 가진 노드를 찾고 삭제하고 그 데이터 반환
char delete_word(){
    
}

// 데이터가 순서대로 정렬되어 있을 때, 새 데이터(노드)를 순서에 맞게 삽입
void insert_ordered(){
    
}

