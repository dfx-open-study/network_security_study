#include <stdio.h>

void setByte(unsigned int* number, int location, int data);
void printByByte(void* number);

int main()
{
    unsigned int number = 0;
    int byteLocation;
    int byteData;
    while (1) {
        printf("�����Ϸ��� 0�� �Է��ϼ���\n");
        printf("Byte ��ġ ( 1 ~ 4 ) : ");
        scanf_s("%d", &byteLocation);
        if (byteLocation == 0) {
            break;
        }
        else {
            printf("��( 0 ~ 255 ) : ");
            scanf_s("%d", &byteData);

            setByte(&number, byteLocation, byteData);
            printByByte(&number);
            printf("4����Ʈ �� ( 16���� ): 0x%08x \n\n", number);
        }
    }
    return 0;
}

void setByte(unsigned int* number, int location, int data) {
    // clear
    *number &= ~(0xFF << ((location - 1) * 8));

    // set
    *number |= data << ((location - 1) * 8);
}

void printByByte(void* number) {
    unsigned char* pt = (unsigned char*)number;
    int i;
    for (i = 0; i < 4; i++) {
        printf("%d ", pt[i]);
    }
}