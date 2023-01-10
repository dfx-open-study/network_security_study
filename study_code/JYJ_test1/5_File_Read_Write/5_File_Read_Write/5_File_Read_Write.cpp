#include <stdio.h>
#include <stdlib.h>

// ���� �б� ���� ���� �ڵ� ����
// task_data / file_read_write_data.txt �� �����͸� ������ ����� result.txt�� ��� �Ѵ�
// day3�� ���� ������ �̿��ؼ� �ۼ�

typedef struct Node
{
	char data;
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
void push(Stack* s, char item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// ����
// return : (0 : ����) (-1 : ������ �������) (-2 : Value �����Ͱ� NULL)
int pop(Stack* s, char* Value)
{
	if (is_empty(s)) {
		return -1;
	}
	else {
		if (Value == NULL)
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
		printf("%s", p->data);
	printf("\n");
}

int main(void)
{
	Stack s;
	char TempValue;
	char result;

	init(&s);

	FILE* fp;
	char buf[10000];

	fp = fopen("C:\\ns_study\\network_security_study\\task_data\\file_read_write_data.txt", "r");
	if (fp == NULL) {
		printf("���� ���� ����\n");
	}

	while (fgets(buf, 10000, fp) != NULL) 
	{
		push(&s, *buf);
		print_stack(&s);
	}

	fclose(fp);

	FILE* fp;
	char buf[10000];

	fp = fopen("C:\ns_study\network_security_study\study_code\JYJ_test1\\5_File_Read_Write\\result.txt", "w");

	while (fgets(buf, 10000, fp) != NULL) 
	{
		result = pop(&s, &TempValue);
		//if (result == 0)
			//printf("%s", TempValue);
		print_stack(&s);
	}

	return 0;
}
	
