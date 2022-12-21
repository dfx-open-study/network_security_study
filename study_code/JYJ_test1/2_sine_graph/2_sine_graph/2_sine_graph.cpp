#include <stdio.h>
#include <math.h>

#define PI 3.141592654

int main()
{
    int i, j;
    double num;

    for (i = 0; i < 180; i += 5) {
        num = sin(i * PI / 180);
        for (j = 0; j < num*80; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}