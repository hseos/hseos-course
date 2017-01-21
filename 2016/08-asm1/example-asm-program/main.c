#include <stdio.h>
#include <stdlib.h>

int N;
int * A;
int * B;
int * R;

extern void summ_asm();
extern void summ2_asm();

void summ2_c()
{
    // assert N > 0   
    while (N>=0) {
        R[N-1] = A[N-1] + B[N-1];
        N--;
    }   
}

void summ_c()
{
    /*
    for (int i=0; i<N; ++i) {
        R[i] = A[i] + B[i];
    }
    */
    int i = 0;
    /*
    while (i<N) {
        R[i] = A[i] + B[i];
        ++i;
    }
    */    

 LoopBegin:
    if ( !(i<N) ) goto LoopEnd;
    /* R[i] = A[i] + B[i]; */
    int esi, edi;
    /*
    esi = *(A + i); // A[i]
    edi = *(B + i); // B[i]    
    esi += edi;
    *(R + i) = esi;
    */
    
    void* edx;
    edx = A;
    // Low-level representation of A[i]
    esi = *((int*)(edx+i*sizeof(int)));
    edx = B;
    edi = *((int*)(edx+i*sizeof(int)));

    esi += edi;
    edx = R;
    *((int*)(edx+i*sizeof(int))) = esi;
    
    ++i;
    goto LoopBegin;
 LoopEnd:
    ;
}

int main()
{
    N = 3;
    A = calloc(N, sizeof(*A));
    B = calloc(N, sizeof(int));
    R = calloc(N, sizeof(int));
    // Fill intial values
    A[0] = 1; B[0] = 2;
    A[1] = 3; B[1] = 4;
    A[2] = 5; B[2] = 6;

    //   summ_c();
    //    summ_asm();
    summ2_asm();

    for (int i=0; i<N; ++i) {
        printf("%d + %d = %d\n", A[i], B[i], R[i]);
    }
    
    free(A);
    free(B);
    free(R);
    return 0;
}
