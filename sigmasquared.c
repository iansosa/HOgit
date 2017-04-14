#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

float average(float *p,int r);
float sigma(float *p,float s,int r);

int main()
{
	int i, r;
	float *p, pro;
	printf("How many rows?   ");
	scanf("%d", &r);
	
	
	p=(float *)malloc(r*sizeof(float));

	FILE *fp;
	fp = fopen("Probabilidades p con PP=0.5.txt", "r");


	for(i=0;i<r;i++)
	{

		fscanf(fp,"%f\n", &pro);
		p[i]=pro;
	}

	printf("%g\n", sigma(p,average(p,r),r));




	return(0);
}



float average(float *p,int r)
{
	int i;
	float avg;
	avg=0;
	for(i=0;i<r;i++)
	{
		avg=avg+p[i];
	}
	return(avg/r);
}

float sigma(float *p,float s,int r)
{
	int i;
	float o;
	float sigm;
	o=0.0;
	for(i=0;i<r;i++)
	{
		o=o+p[i]*p[i];
	}
	
	sigm=(o/r)-s*s;

return(sigm);

}