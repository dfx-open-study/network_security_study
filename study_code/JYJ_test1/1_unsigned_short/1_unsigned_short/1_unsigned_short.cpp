#include <stdio.h>

void printToBinary(int num, int length);
void bitOnOff(unsigned short* number, int onOff, int location);

int main()
{
	unsigned short number = 0;
	int changeLocation =0;
	int onOff = 1;
	int j = 0;

	for (j; j <= 16; j++) {
		printf("Location of the bit : ");
		scanf("%d", &changeLocation);
		printf("OFF/ON [0, 1] : ");
		scanf("%d", &onOff);

		bitOnOff(&number, onOff, changeLocation);

		printf("Number in decimal : %d\n", number);
		printf("Number in Binary : ");
		printToBinary(number, 16);
	}

	return 0;
}
void bitOnOff(unsigned short* number, int onOff, int location) {

	location--;
	
	//OFF
	if (onOff == 0) {
		*number &= ~(1 << location);
	}

	//ON
	else {
		*number |= 1 << location;
	}
}

void printToBinary(int num, int length) {
	int i = length;

	for(i; i > 0; --i) {
			printf("%d", (num >> i) & 1);
	}

	printf("\n");
}