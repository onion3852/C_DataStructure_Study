// 노드 중간에 새로운 노드를 삽입하는 과정 실습

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};

typedef struct node NODE;
NODE *head = NULL;


int main(){
    // 초기에 2개의 노드가 있는 상황
    head = (NODE *)malloc(sizeof(NODE));
    head->data = "Tuesday";               
    head->next = NULL;  

    NODE *p = (NODE *)malloc(sizeof(NODE));
    p->data = "Thursday";
    p->next = NULL;
    head->next = p;

    // 새로운 노드를 두 노드 사이의 삽입해야 함
    // 기본적인 절차는 다음과 같음
    // 1) 새로운 노드를 메모리상에 동적 할당으로 만들고 
    // 2) 새로운 데이터를 저장함
    // 3) 삽입시키는 노드의 next필드에 삽입할 자리의 다음 노드의 주소를 할당하고
    // 4) 삽입할 자리의 이전 노드의 next필드에, 삽입시키는 노드의 주소를 할당함
    NODE *temp = (NODE *)malloc(sizeof(NODE));
    temp->data = "Wedneday";
    temp->next = head->next;
    head->next = temp;

    // 검증
    NODE *ptr = head;
    while(ptr != NULL){
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }

    return 0;
}

// 참고로 어떤 노드 뒤에 삽입하는 것은 간단하지만
// 어떤 노드 앞에 삽입하는 것을 구현하는 것은 상대적으로 더 어렵다