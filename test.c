#include <stdio.h>
#define N 100
int array[N];
int main() 
{
    #pragma acc parallel loop copy(array[0:N])
    for (int i = 0; i < N; i++)
    {
        array[i] = 3.0;
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", array[i]);
    }
}