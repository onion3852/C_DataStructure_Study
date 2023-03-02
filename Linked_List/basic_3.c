// 중간의 어떤 노드를 삭제하는 과정 실습

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};

typedef struct node NODE;
NODE *head = NULL;


int main(){
    // 초기에 3개의 노드가 있는 상황
    head = (NODE *)malloc(sizeof(NODE));
    head->data = "Tuesday";               
    head->next = NULL;  

    NODE *p = (NODE *)malloc(sizeof(NODE));
    p->data = "Wednesday";
    p->next = NULL;
    head->next = p;

    NODE *q = (NODE *)malloc(sizeof(NODE));
    q->data = "Thursday";
    q->next = NULL;
    p->next = q;

    NODE *ptr = head;
    while(ptr != NULL){
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }

    printf("\n");
    // 중간의 노드("Wednesday")를 삭제해야 함
    // 이떄 삭제하고자 하는 노드 이전 노드에서 부터 진행한다
    // 왜냐면 그 노드의 next필드를 바꿔야 하므로
    // 이때, 삭제하려는 노드의 주소를 알아낼 필요가 있는데
    // free하여 메모리공간을 관리하기 위해서이다
    NODE *temp = head->next;
    if(head->next != NULL)
        head->next = head->next->next;  // 이러한 표현방식은 유효하다
    free(temp);
    
    // 검증
    ptr = head;
    while(ptr != NULL){
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }

    return 0;
}