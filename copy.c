#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int n = 1000;
    float* a = (float*)malloc(n * sizeof(float));
    float* b = (float*)malloc(n * sizeof(float));

    #pragma omp parallel for num_threads(1000)
    for(int i = 0; i < n; i++)
    {
        a[i] = i * 0.1f;
        b[i] = i * 0.2f;
    }

    //transfer data to device
    #pragma acc enter data copyin(a,b)

    //calculate sum and add to a
    #pragma acc data present(a,b)
    #pragma acc parallel loop
    for (size_t i = 0; i < n; i++)
    {
        a[i] += b[i];
    }
    
    //square every element of a by using present clause
    #pragma acc data present(a)
    #pragma acc parallel loop
    for (size_t i = 0; i < n; i++)
    {
        a[i] *= a[i];
    }
    
    //transfer results back to host
    #pragma acc exit data copyout(a)

    //print the output
    #pragma omp parallel for num_threads(1000)
    for (size_t i = 0; i < n; i++)
    {
        printf("%f\n", a[i]);
    }
    
    return 0;
}