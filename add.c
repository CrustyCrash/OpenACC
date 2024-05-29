#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 10

void add(int* a, int* b, int* c)
{
    #pragma acc kernels loop copyout(c[0:N])
    for(int i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];
    }
}

int main()
{
    int* a = (int*)malloc(N * sizeof(int));
    int* b = (int*)malloc(N * sizeof(int));
    int* c = (int*)malloc(N * sizeof(int));

    #pragma omp parallel for 
    for(int i = 0; i < N; i++)
    {
        a[i] = i;
        b[i] = -i;
    }
    add(a,b,c);
    int verify = 1;
    #pragma omp parallel for
    for(int i = 0; i < N; i++)
    {
        if(a[i]+b[i]!=c[i])
        {
            printf("Error at index %d\n %d + %d != %d\n", i,a[i],b[i],c[i]);
            verify = 0;
        }
    }
    if(verify)
    {
        printf("Program executed successfully\n");
    }
}