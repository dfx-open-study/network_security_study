//��ũ�� ����Ʈ�� �̿��� STACK �ڷᱸ�� ����
//�׻� ���� ���� ����Ű�� �ִ� TOP ������ ���� ����
//push�ϴ� �����ʹ� ���ο� ��ũ�� ����Ʈ ��带 �����Ͽ� TOP ������ ����
//pop�ÿ��� �����͸� �̾Ƴ��� �� ��ũ�� ����Ʈ�� free �Ѵ�
//���ÿ� ���� ���ڸ� �ְ� �ٽ� �̾Ƴ��� ����ϴ� �ڵ� �ۼ�

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

// �ʱ�ȭ �Լ�
void init(Stack* s)
{
	s->top = NULL;
}

// ���� ����
int is_empty(Stack* s) 
{
	return (s->top == NULL);
}

// ��ȭ ����
int is_full(Stack* s) 
{
	return 0;
}
// ����
void push(Stack* s, int item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// �̷� ����� ���� �ʽ��ϴ�.
// pop �� �ÿ� return ������ ����Ǿ��ִ� value �� �����ϴ� �����
// ���� stack ��ü�� ������ �ִٸ� ���� ��Ȳ�� ���� ������ ���մϴ�.
// �׷��Ƿ� parameter�� �����͸� �Ѱ��ִ� ����� ����ϰ�
// return ���� success or error state �� �Ѱ��ִ� ����� ��� �ϼž� �մϴ�.
/*
// ����
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
*/

// ex) ����
// return : (0 : ����) (-1 : ������ �������) (-2 : Value �����Ͱ� NULL)
int pop(Stack *s, int *Value)
{
	if(is_empty(s)) {
		return -1;
	}
	else {
		if(Value == NULL)
			return -2;
		Node* temp = s->top;
		*Value = temp->data;

		s->top = s->top->link;
		free(temp);
		return 0;
	}
}


// ���
void print_stack(Stack* s) 
{
	for (Node* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

int main(void)
{
	Stack s;
	int TempValue;
	int result;

	init(&s);
	push(&s, rand()%90); print_stack(&s);
	push(&s, rand()%90); print_stack(&s);
	push(&s, rand()%90); print_stack(&s);
	
	result = pop(&s, &TempValue);
	if(result == 0)
		printf("POP VALUE : %d", TempValue);
	 print_stack(&s);

	result = pop(&s, &TempValue);
	if(result == 0)
		printf("POP VALUE : %d", TempValue);
	 print_stack(&s);

	result = pop(&s, &TempValue);
	if(result == 0)
		printf("POP VALUE : %d", TempValue);
	 print_stack(&s);
	//pop(&s); print_stack(&s);
	//pop(&s); print_stack(&s);
	//pop(&s); print_stack(&s);
	return 0;
}