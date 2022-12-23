//링크드 리스트에 랜덤 숫자를 넣고 리스트 순서대로 출력하는 코드 작성
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};
typedef struct node list_node;
typedef list_node* list_ptr;

list_ptr create(int n) {
    list_ptr first = NULL, temp = NULL;
    int i;
    for (i = 0; i < n; i++)
    {
        temp = (list_ptr)malloc(sizeof(list_node));
        temp->data = rand() % 900; //리스트의 랜덤 값 
        temp->link = first; //새로운 노드를 리스트의 맨 앞에 삽입
        first = temp;
    }
    return first;
}

void print_list(list_ptr ptr) {
    printf("The list contains: ");
    for (; ptr; ptr = ptr->link)
        printf("%4d", ptr->data);
    printf("\n");
}

int main()
{
    list_ptr ptr = NULL;
    ptr = create(10); //10개의 노드를 가진 연결리스트
    print_list(ptr);
}