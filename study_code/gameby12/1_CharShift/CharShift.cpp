#include <stdio.h>

//unsigned char ���� ���� ��Ʈ������ ���
//ex) unsigned char ���� 0xFF�� ��� -> 11111111 ���
//unsigned char ���� 0x50�� ��� -> 01010000 ���
int main(){
unsigned char num = 0xFF;
int count;
for (count = 0; count < 8; count++)
{
	unsigned char temp = (num >> (7 - count)) & 1;
	printf("%d", temp);
}
return 0;
}
