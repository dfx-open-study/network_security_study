#include <stdio.h>

//unsigned int 변수 바이트 단위 제어
//unsigned int 변수 0 초기화
//키보드로 1 ~4 바이트 위치 입력, 키보드로 해당 위치에 넣을 데이터 0 ~255 입력
//입력 완료후 바이트 단위로 쪼개서 출력 & unsigned int 변수 16진수 출력
//이전 실행의 결과는 보존되어야 한다

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