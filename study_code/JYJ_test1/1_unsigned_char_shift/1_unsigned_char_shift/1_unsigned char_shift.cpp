#include <stdio.h>

int main()
{   
	// unsigned char ���� ���� ��Ʈ������ ���
	// unsigned char ���� 0x50�� ��� -> 01010000 ���
	
	unsigned char num = 0x50;
	int count;
	for (count = 0; count < 8; count++)
	{
		unsigned char temp = (num >> (7 - count)) & 1;
		printf("%d", temp);
	}
	return 0;
}