//��ũ�� ����Ʈ�� ���� ���ڸ� �ְ� ����Ʈ ������� ����ϴ� �ڵ� �ۼ�
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
        temp->data = rand() % 900; //����Ʈ�� ���� �� 
        temp->link = first; //���ο� ��带 ����Ʈ�� �� �տ� ����
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
    ptr = create(10); //10���� ��带 ���� ���Ḯ��Ʈ
    print_list(ptr);
}