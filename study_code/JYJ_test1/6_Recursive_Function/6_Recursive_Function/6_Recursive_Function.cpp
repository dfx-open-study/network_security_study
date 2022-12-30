#include <stdio.h>
#include <Windows.h>
#define SCREAN_HEIGHT 10
#define SCREAN_WIDTH 20

char Original[SCREAN_HEIGHT][SCREAN_WIDTH] = {
    { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', 'O', 'O', 'O' },
    { ' ', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', ' ', 'O' },
    { ' ', ' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },
    { ' ', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O' },
    { ' ', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O' },
    { 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', 'O', 'O', 'O', 'O', ' ', ' ', ' ', ' ', 'O', 'O' },
    { 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O', 'O', ' ', 'O', ' ', ' ', ' ', ' ', 'O', 'O' },
};

char Temp[SCREAN_HEIGHT][SCREAN_WIDTH];
int main()
{
    int y = 0, x = 0;
    void Print_Screan();
    void Find_Way(int, int, char);
    while (1)
    {
        memcpy(Temp, Original, sizeof(Original));
        Print_Screan();											//ȭ�� ���
        Sleep(2000);
        Find_Way(5, 8, '.');										//��ã��
        Sleep(2000);
    }

    return 0;

}

void Print_Screan()
{
    system("cls");   //ȭ�� û��
    int P_y = 0, P_x = 0;
    for (P_y = 0; P_y < 10; P_y++)
    {
        for (P_x = 0; P_x < 20; P_x++)
        {
            printf("%c", Temp[P_y][P_x]);
        }
        printf("\n");
    }
}

void Find_Way(int F_y, int F_x, char c)
{
    int y = F_y;
    int x = F_x;

    Print_Screan();

    //���� ���� ��ġ���� ������ 'O' �� �ִ� ��� Temp���� c�� �ٲٰ� �� ��ġ���� �ٽ� find_way ����Ѵ�.
    if (Temp[y][x + 1] == 'O')
    {
        Temp[y][x + 1] = c;
        Find_Way(y, x+1, '.');
    }
    //���� ���� ��ġ���� ������ 'O' �� �ִ� ��� Temp���� c�� �ٲٰ� �� ��ġ���� �ٽ� find_way ����Ѵ�.
    if (Temp[y][x - 1] == 'O')
    {
        Temp[y][x - 1] = c;
        Find_Way(y, x-1, '.');
    }
    //���� ���� ��ġ���� ���� 'O' �� �ִ� ��� Temp���� c�� �ٲٰ� �� ��ġ���� �ٽ� find_way ����Ѵ�.
    if (Temp[y - 1][x] == 'O')
    {
        Temp[y-1][x] = c;
        Find_Way(y-1, x, '.');
    }
    //���� ���� ��ġ���� �Ʒ��� 'O' �� �ִ� ��� Temp���� c�� �ٲٰ� �� ��ġ���� �ٽ� find_way ����Ѵ�.
    if (Temp[y + 1][x] == 'O')
    {
        Temp[y+1][x] = c;
        Find_Way(y+1, x, '.');
    }
           
    return;
}
