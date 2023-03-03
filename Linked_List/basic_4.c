// 연결리스트 순회(traverse)하기 실습
// 원하는 데이터가 있는 노드를 찾기 위해
// 처음부터 읽어나가기

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
};

typedef struct node NODE;
NODE *head = NULL;

NODE *find_word(char *word);


int main(){
    char str[50];

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

    while(1){
        printf("Word to find : ");
        scanf("%s", str);
        find_word(str);
    }

    return 0;
}


// function
NODE *find_word(char *word){
    NODE *ptr = head;
    while(ptr != NULL){
        if(strcmp(ptr->data, word) == 0){
            printf("Word '%s' found\n", ptr->data);
            return ptr;
        }
        ptr = ptr->next;
    }
    printf("Can't find the word '%s' \n", word);
    return ptr;
}