#include <stdio.h>
#include <stdlib.h>

// 파일 읽기 쓰기 관련 코드 구현
// task_data / file_read_write_data.txt 의 데이터를 순서를 뒤집어서 result.txt에 출력 한다
// day3에 만든 스택을 이용해서 작성

typedef struct Node
{
	char data;
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
void push(Stack* s, char item) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

// 삭제
// return : (0 : 정상) (-1 : 스택이 비어있음) (-2 : Value 포인터가 NULL)
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


// 출력
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
		printf("파일 열기 실패\n");
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
	
