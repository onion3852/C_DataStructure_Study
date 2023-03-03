// 연결 리스트를 수정(추가, 삭제 등)하는 다양한 함수들 만들기
// - 리스트의 n번 index 노드 주소를 반환
// - 리스트의 n번 index 위치에 노드 삽입
// - 리스트의 n번 index 노드를 삭제하고 그 노드의 데이터를 반환
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

NODE *get_node(int index);
int  insert_index(int index, char *item);
char *delete_index();
char delete_word();
void insert_ordered();
void add_first(char *item);
int  add_after(NODE *ptr, char *item);


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

    // 함수들 검증
    for(int i = 0; i < 3; i++)
        printf("address of the index %d node is %p\n",i, get_node(i));
    printf("\n");

    insert_index(0, "Ant");
    insert_index(3, "FPGA");
    for(int i = 0; i < 5; i++)
        printf("%s\n", get_node(i)->data);
    printf("\n");




    return 0;
}


/////////////////////////////////////////////////////////////
// function declaration
/////////////////////////////////////////////////////////////

// 리스트의 어떤 index(0부터)에 해당하는 노드 주소를 반환
// 포인터를 반환하므로 주소출력시 이를 주의
NODE *get_node(int index){
    if(index < 0)
        return NULL;

    NODE *ptr = head;
    for(int i = 0; (i < index) && (ptr != NULL); i++)
        ptr = ptr->next;
    
    return ptr;
}

// 리스트의 index n번 위치에 노드 삽입
// 새로운 n번 index가 된다는 의미
// 성공적으로 완료시 1 반환
int insert_index(int index, char *item){
    if(index < 0)
        return NULL;
    
    if(index == 0)
        add_first(item);
    return 1;


    NODE *ptr = get_node(index - 1);
    if(ptr != NULL){
        add_after(ptr, item);
        return 1;
    }

    return 0;
}

// 리스트의 n번 index 노드를 삭제하고 그 노드의 데이터를 반환
char *delete_index(int index){
    if(index <0 )
        return NULL;
    
    if(index == 0)
        head = head->next;
    return
    

    ptr->next = 
}

// 입력한 string을 가진 노드를 찾고 삭제하고 그 데이터 반환
char delete_word(){
    
}

// 데이터가 순서대로 정렬되어 있을 때, 새 데이터(노드)를 순서에 맞게 삽입
void insert_ordered(){
    
}


/////////////////////////
// 함수 내에서 쓸 함수들 //
/////////////////////////

// 리스트의 맨 앞에 삽입시키는 함수
void add_first(char *item){
    NODE *tmp = (NODE *)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = head;
    head      = tmp;
}

// 어떤 노드 다음 위치에 새로운 노드 삽입시키는 함수
// 성공시 1, 실패시 0 반환
int add_after(NODE *ptr, char *item){
    if(ptr == NULL)
        return 0;

    NODE *tmp = (NODE *)malloc(sizeof(NODE));
    tmp->data = item;
    tmp->next = ptr->next;
    ptr->next = tmp;

    return 1;
}