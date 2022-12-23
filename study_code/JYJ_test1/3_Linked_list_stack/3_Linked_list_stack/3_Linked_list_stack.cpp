//링크드 리스트를 이용한 STACK 자료구조 구현
//항상 가장 위를 가리키고 있는 TOP 포인터 변수 설정
//push하는 데이터는 새로운 링크드 리스트 노드를 생성하여 TOP 변수에 연결
//pop시에는 데이터를 뽑아내고 빈 링크드 리스트는 free 한다
//스택에 랜덤 숫자를 넣고 다시 뽑아내서 출력하는 코드 작성

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* link;
} Node;

typedef struct 
{
	Node* top;
} Stack;

// 초기화 함수
void init(Stack* s)
{
	s->top = NULL;
}

// 공백 검출
int is_empty(Stack* s) 
{
	return (s->top == NULL);
}

// 포화 검출
int is_full(Stack* s) 
{
	return 0;
}
// 삽입
void push(Stack* s, int item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// 삭제
int pop(Stack *s)
{
	if (is_empty(s)) {
		return s->top == NULL;
	}
	else {
		Node* temp = s->top;
		int data = temp->data;

		s->top = s->top->link;
		free(temp);
		return data;
	}
}

// 출력
void print_stack(Stack* s) 
{
	for (Node* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

int main(void)
{
	Stack s;
	init(&s);
	push(&s, rand()%90); print_stack(&s);
	push(&s, rand()%90); print_stack(&s);
	push(&s, rand()%90); print_stack(&s);
	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	pop(&s); print_stack(&s);
	return 0;
}