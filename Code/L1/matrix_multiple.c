#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
// #include <cilk.h>

#define n 4096
double A[n][n];
double B[n][n];
double C[n][n];

float tdiff(struct timeval *start,struct timeval *end ){
    return (end->tv_sec-start->tv_sec)+(1e-6)*(end->tv_usec-start->tv_usec);//TODO: 看一下这个是什么意思
}

int main(int argc,const char *argv[]){
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j){
            A[i][j]=(double)rand()/(double)RAND_MAX;//TODO: 看一下这个是什么意思
            B[i][j]=(double)rand()/(double)RAND_MAX;
            C[i][j]=0;
        }
    }

    struct timeval start,end;
    gettimeofday(&start,NULL); //TODO: 看一下这个是什么意思

    for (int i=0;i<n;++i){ //can use cilk_for in this layer
        for (int j=0;j<n;++j){
            for (int k=0;k<n;++k){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }

    gettimeofday(&end,NULL);
    printf("%0.6f\n",tdiff(&start,&end));
    return 0;
    
}