#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


void  llenar(int *red,int n,float prob);
void  imprimir(int *red,int *clase,int n);
void  etiqueta_falsa(int *red,int *clase,int s1,int s2,int frag);
void  corregir_etiqueta(int *red,int *clase,int n);
int   actualizar(int *red,int *clase,int s,int frag);
int   hoshen(int *red,int *clase,int n);
int   percola(int *red,int n);
float average(float *pc,int z);
float sigm(float *pc,float s,int r);


int  main()
{
	//int per;
	int n, i, j, m, z;
	int *red;
	float *pc;
	float prob, d;
	int *clase;
	n=30;
	m=0;
	
	red=(int *)malloc(n*n*sizeof(int));
	clase=(int *)malloc(n*n*sizeof(int));


	printf("How many iterations?   ");
	scanf("%d", &z);
	float array[z];
	pc=(float *)malloc(z*sizeof(float));


	//printf("Enter proba:   ");
	//scanf("%g", &prob);
	
		for(j = 0;j < z; j++)
		{

		prob=0.5;
		d=2.0;
		FILE *fp;

		fp = fopen("Probabilidades p convergientes.txt", "a");
		
		srand(time(NULL) + j);
 
			for(i = 0;i < 40; i++)
			{

			llenar(red,n,prob);
			hoshen(red,clase,n);
			d=2.0*d;
    		//imprimir(red,clase,n);
    			if (percola(red,n))
    			{ 
             	prob+=(-1.0/d);
             	} 
            	else
            	{
            	prob+=(1.0/d);
            	}
    		//per=percola(red,n);
			//printf("%d\n%g\n",per,prob);
			
			}
		pc[j]=prob;
		array[j] = pc[m++];
        fprintf(fp, "%f\n", array[j]);
		}
	
	printf("\n%g\n" , average(pc,z));

  free(red);

  return 0;
}

void  llenar(int *red,int n,float prob){

	int i;
	int a;
	float b;
	float c;

	c = prob * 100000;
	

	for(i = 0; i < n*n; i++){

		b=0;
		a= rand() % 100000;

			if(a>=c)
			{
				b=0;
			}
			else
			{
				b=1;
			}
		red[i] = b;
	}
}

int hoshen(int *red,int *clase, int n)
{


 	int i,j,k,s1,s2,frag;
 	
  	frag=0;
  
    	for(k=0;k<n*n;k++) *(clase+k)=frag;
  

  	s1=0;
  	frag=2;
  	if (*red) frag=actualizar(red,clase,s1,frag);
  

  	for(i=1;i<n;i++) 
    	{
      			if (*(red+i)) 
         		{
          		s1=*(red+i-1);  
           		frag=actualizar(red+i,clase,s1,frag);
         		}
    	}
  

  
 	for(i=n;i<n*n;i=i+n)
    	{

      
      		if (*(red+i)) 
         	{
           	s1=*(red+i-n); 
           	frag=actualizar(red+i,clase,s1,frag);
         	}

      		for(j=1;j<n;j++)
		{
			if (*(red+i+j))
	  		{
	    		s1=*(red+i+j-1); 
            		s2=*(red+i+j-n);

	    			if (s1*s2>0)
	     			{
				etiqueta_falsa(red+i+j,clase,s1,s2,frag);
	      			}
	    			else 
	      			{
					 if (s1!=0) frag=actualizar(red+i+j,clase,s1,frag);
					 else  frag=actualizar(red+i+j,clase,s2,frag);
				}
	  		}
		 }
	}

  corregir_etiqueta(red,clase,n);
/*
  free(clase);
*/
  return 0;
}

float sigm(float *p,float s,int r)
{
	int i;
	float o;
	float sig;
	o=0.0;
	for(i=0;i<r;i++)
	{
		o=o+p[i]*p[i];
	}
	
	sig=(o/r)-s*s;

return(sig);

}

int   actualizar(int *sitio,int *clase,int s,int frag)
{
	while(clase[s]<0)
	{
		s=-clase[s];
	}
	clase[s]=s;

	if(s==frag)
	{
		sitio[0]=frag;
		clase[frag]=frag;
	}
	else if(s==0)
	{
		frag=frag + 1;
		sitio[0]=frag;
		clase[frag]=frag;
	}
	else
	{
		frag=frag + 1;
		sitio[0]=frag;
		clase[frag]=-s;
	}
   return(frag);
}

int   percola(int *red,int n)
{
	int i;
	int j;
	int per;
	int a;
	int b;
	int c;
	per=0;
	c=0;
	
	while(c==0)
	{
		for(i=0;i<n;i++)
		{
			if(red[i]>0)
			{
				a=red[i];
					for(j=0;j<n;j++)
					{
						b=red[n*(n-1)+j];
						if(a==b)
						{
							per=1;
							c=2;
						}
						else
						{
							per=per;
						}
					}
			}
		c=2;
		}
	}
return(per);
}

void  etiqueta_falsa(int *red,int *clase,int s1,int s2,int frag)
{
	while(clase[s1]<0)
	{
		s1=-clase[s1];
	}
	while(clase[s2]<0)
	{
		s2=-clase[s2];
	}
	
	if(s2<s1)
	{
		clase[s1]=-s2;
		clase[s2]=s2;
		red[0]=s2;
	}
	else
	{
		clase[s2]=-s1;
		clase[s1]=s1;
		red[0]=s1;
	}
}

void  corregir_etiqueta(int *red,int *clase,int n)
{
	int i;
	int s;
	for(i=0;i<n*n;i++)
	{
		s=red[i];
		while(clase[s]<0)
		{
			s=-clase[s];
		}
		red[i]=s;
	}
}

float average(float *pc,int z)
{
	int i;
	float avg;
	avg=0;
	for(i=0;i<z;i++)
	{
		avg=avg+pc[i];
	}
return(avg/z);
}

void imprimir(int *red,int *clase,int n){    //print del vector clase comentado

	int i,j;
	//int k,l,b;
        int array[n][n];
	//int arrayclase[n][n];
	int m;
	m=0;
	//b=0;
	for(j=0;j<n;j++) 
	{
        	for(i=0;i<n;i++)
        	{
            	array[j][i] = red[m++];
            	printf("%d " , array[j][i]);
       		}
	printf("\n");
	}
	/*for(k=0;k<n;k++) 
	{
        	for(l=0;l<n;l++)
        	{
            	arrayclase[k][l] = clase[b++];
            	printf("%d " , arrayclase[k][l]);
       		}
        printf("\n");
	}*/
}


