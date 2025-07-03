#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <cilk.h>

void mm_dac(double *restrict C,int n_C,
            double *restrict A,int n_A,
            double *restrict B,int n_B,
            int n){
    // C+=A*B
    assert((n&(-n))==n);
    if(n<=1){
        *C+=*A * *B;
    }else{
        #define X(M,r,c) ((M+r*(n_ ## M)+c)*(n/2))
        cilk_spawn mm_dac(X(C,0,0),n_c,X(A,0,0),n_A,X(B,0,0),n_B,n/2);
        cilk_spawn mm_dac(X(C,0,1),n_c,X(A,0,0),n_A,X(B,0,1),n_B,n/2);
        cilk_spawn mm_dac(X(C,1,0),n_c,X(A,1,0),n_A,X(B,0,0),n_B,n/2);
        mm_dac(X(C,1,1),n_c,X(A,1,0),n_A,X(B,0,1),n_B,n/2);
        
        cilk_sync;
        cilk_spawn mm_dac(X(C,0,0),n_c,X(A,0,0),n_A,X(B,0,0),n_B,n/2);
        cilk_spawn mm_dac(X(C,0,1),n_c,X(A,0,0),n_A,X(B,0,1),n_B,n/2);
        cilk_spawn mm_dac(X(C,1,0),n_c,X(A,1,0),n_A,X(B,0,0),n_B,n/2);
        mm_dac(X(C,1,1),n_c,X(A,1,0),n_A,X(B,0,1),n_B,n/2);
        cilk_sync;

    }


}