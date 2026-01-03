#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<sys/time.h>
#define num 10000
int *a;
int *b;
int *c;
int main(){
    struct timeval s_start,s_end,p_start,p_end;

gettimeofday(&s_start,NULL);
a = malloc(num *sizeof(int));
b = malloc(num *sizeof(int));
c = malloc(num *sizeof(int));


for(int i=0;i<num;i++){
    a[i] = rand() % 10000;
     b[i] = rand() % 10000;
     c[i] = 0;

}
gettimeofday(&s_end,NULL);
double s_time=(s_end.tv_sec-s_start.tv_sec )  + ( s_end.tv_usec-s_start.tv_usec)/10000.0;
gettimeofday(&p_start,NULL);
#pragma omp parallel num_threads (4)
{
long int sum =0;
for (int i=0; i<num;i++){
    c[i]=a[i]*b[i];

    sum =sum+c[i];
}
}

gettimeofday(&p_end,NULL);
long int sum =0;
double p_time=(p_end.tv_sec-p_start.tv_sec )  + ( p_end.tv_usec-p_start.tv_usec)/10000.0;
 printf("Sum is %ld\nS time: %f sec\nP time: %f sec\nTotal time: %f sec\n",
       sum, s_time, p_time, s_time + p_time);

}