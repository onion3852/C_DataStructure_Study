// linked list의 기본적인 구현 및
// 새로운 노드를 맨 앞에 삽입하는 과정 실습

#include <stdio.h>
#include <stdlib.h>

// linked list를 만드는 기본적인 방법
// struct가 각각의 노드(node)가 되고
// 노드(구조체)는 data필드와 link필드(next필드)로 구성됨
// 이때, link필드에는 다음 노드의 주소를 저장시켜야 하므로
// 자신과 동일한 구조체의 포인터를 멤버로 가짐
struct node {
    char *data;
    struct node *next;
};

// 각 노드를 NODE 라는 타입으로 정의
typedef struct node NODE;
// 첫 노드(구조체)의 주소를 저장할 포인터 선언
NODE *head = NULL;


int main(){
    // 새로운 데이터가 저장되어야 할 때마다 
    // 동적 메모리할당을 통해서 노드를 만들어야함
    // 즉, 배열처럼 미리 메모리를 할당받는 방식이 아님
    // 다음은 첫 노드를 만드는 과정
    head = (NODE *)malloc(sizeof(NODE));
    head->data = "Tuesday";               
    head->next = NULL;  // 아직 다음 노드가 없으므로 NULL

    // 두 번째 데이터가 저장되어야 해서
    // 다음 노드를 만드는 과정
    NODE *p = (NODE *)malloc(sizeof(NODE));
    p->data = "Wednesday";
    p->next = NULL;
    // 첫 노드의 next필드에 두번째 노드의 주소를 할당함
    head->next = p;

    // 만약 순서상 리스트의 첫번째 데이터를 바꿔야 할 경우
    p = (NODE *)malloc(sizeof(NODE));
    p->data = "Monday";
    p->next = head;
    // 주소를 정상적인 순서로 다시 맞추는 과정
    head = p;
    NODE *ptr = head;
    while(ptr != NULL){
        printf("%s\n", ptr->data);
        ptr = ptr->next;
    }

    // 포인터는 주소를 가리키는 변수일 뿐이다
    // 따라서 포인터 변수들이 할당되는 식은
    // 항상 그 포인터가 어떤 주소를 가리키고 있는지를 확인해야 함

    return 0;
}

// 연결리스트 맨 앞에 새로운 노드를 삽입하는 절차
// (참고로 이 방식은 head가 NULL인, 즉, 첫 노드를 만드는 과정도 대신할 수 있음)
// 1) 새로운 노드를 만들고 추가할 데이터를 저장함
// 2) 새로운 노드의 next 필드가 현재 head 노드를 가리키도록 함
// 3) head 포인터가 새로운 노드의 주소를 가리키도록 함
// 이 방법을 함수로 만들어 사용할 수도 있음
// 다만, head가 전역변수가 아니면, 값에 의한 호출시 head의 값이 바뀌지 않을 수 있으므로 head의 포인터를 매개로 하여 이용하거나
// 값에 의한 호출을 하되, 함수가 새로운 노드의 주소를 리턴하게 하고,  리턴값을 head에 할당하는 방법도 있음
