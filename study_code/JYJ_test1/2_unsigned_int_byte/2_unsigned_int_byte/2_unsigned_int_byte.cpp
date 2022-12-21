#include <stdio.h>

//unsigned int ���� ����Ʈ ���� ����
//unsigned int ���� 0 �ʱ�ȭ
//Ű����� 1 ~4 ����Ʈ ��ġ �Է�, Ű����� �ش� ��ġ�� ���� ������ 0 ~255 �Է�
//�Է� �Ϸ��� ����Ʈ ������ �ɰ��� ��� & unsigned int ���� 16���� ���
//���� ������ ����� �����Ǿ�� �Ѵ�

void setByte(unsigned int* number, int location, int data);
void printByByte(void* number);

int main()
{
    unsigned int number = 0;
    int byteLocation;
    int byteData;
    int i;
    
    for (i = 0; i <= 3; i++) 
    {
        printf("Byte Location(1~4) : ");
        scanf("%d", &byteLocation);
        printf("Data(1~255) : ");
        scanf("%d", &byteData);

        setByte(&number, byteLocation, byteData);
        printByByte(&number);
        printf("4bytes value : 0x%08x", number);

        printf("\n");
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
    int j;
    for (j = 0; j < 4; j++) {
        printf("%d ", pt[j]);
    }
}