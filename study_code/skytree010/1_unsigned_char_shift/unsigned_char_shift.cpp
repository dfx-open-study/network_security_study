#include <stdio.h>

int main()
{
	//unsigned char 변수 값을 비트단위로 찍기
	//ex) unsigned char 값이 0xFF인 경우 -> 11111111 출력
	//unsigned char 값이 0x50인 경우 -> 01010000 출력
	unsigned char num = 0x50;
	int count;
	for (count = 0; count < 8; count++)
	{
		unsigned char temp = (num >> (7 - count)) & 1;
		printf("%d", temp);
	}
	return 0;
}