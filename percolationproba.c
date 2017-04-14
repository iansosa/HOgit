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
int   percola(int *red,float *mass,int n, int s, int i,int l);
float average(float *pc,int z);


int  main()
{
	float per;
	int n, i, j, z, l, k, h, b, d, r, s, y;
	int *red;
	float *perproba, *perprobap, *masa, *masap, *pc, q, *mass;
	float prob, c;
	int *clase;
	y=0;
	n=30;
	b=0;
	q=2.0;
	
	red=(int *)malloc(n*n*sizeof(int));
	clase=(int *)malloc(n*n*sizeof(int));
	


	printf("How many iterations lvl 1?(#matrixes)   ");
	scanf("%d", &l);
	printf("How many iterations lvl 2?(#averages of diferent seeds)   ");
	scanf("%d", &z);
	printf("Want to converge on pp=0.5?(1 for yes)   ");
	scanf(" %d", &d);
	mass=(float *)malloc(l*sizeof(float));
		
	if(d!=1)
	{
		
		printf("Want to get pdensity?(1 for yes)   ");
		scanf(" %d", &s);
		printf("What's the resolution of p?   ");
		scanf("%g", &c);
		perproba=(float *)malloc(z*sizeof(float));
		masa=(float *)malloc(z*sizeof(float));
		prob=0;
		h=ceil(1.0/c);
		perprobap=(float *)malloc(h*sizeof(float));
		masap=(float *)malloc(h*sizeof(float));
		float arrayp[h];
		float arraymp[h];
		//printf("Enter proba:   ");
		//scanf("%g", &prob);
		FILE *fp;

		fp = fopen("Probabilidad de percolacion vs Probabilidad p.txt", "a");


			for(k = 0;k <= h; k++)
			{
				prob=0.0 + c*k;
	
				for(j = 0;j < z; j++)
				{

					per=0.0;
				
					srand(time(NULL) + j);

						for(i = 0;i < l; i++)
						{

						llenar(red,n,prob);
						hoshen(red,clase,n);
						//imprimir(red,clase,n);
    		
    					per=per+percola(red, mass, n, s, i, l);
						//printf("%d\n%g\n",per,prob);
						}

					perproba[j]=per/l;
					if (s==1) 
					{
						masa[j]=average(mass,l);
				    }    		
				}
				
				perprobap[k]=average(perproba,z);
				arrayp[k]=perprobap[b++];
				if (s==1)
				{
					masap[k]=average(masa, z);
					arraymp[k]=masap[y++];
					printf("p=%g pp=%g mass=%g\n" , prob, arrayp[k], arraymp[k]);
					fprintf(fp, "%f %f %f\n", arrayp[k], arraymp[k], prob);
				}
				else
				{
				printf("p=%g pp=%g\n" , prob, arrayp[k]);
				fprintf(fp, "%f %f\n", arrayp[k], prob);
				}
			}
	



	}
	else
	{
		s=0;
		printf("How many iterations lvl 3?(#probabilities untill finish)   ");
		scanf("%d", &r);
		FILE *fp;

		fp = fopen("Probabilidades p con PP=0.5.txt", "a");
				
		perproba=(float *)malloc(z*sizeof(float));
		perprobap=(float *)malloc(r*sizeof(float));
		pc=(float *)malloc(r*sizeof(float));
		float array[r];
		//printf("Enter proba:   ");
		//scanf("%g", &prob);

			

			for(k = 0;k <= r; k++)
			{
				
				prob=1;
				q=2.0;
	
				for(j = 0;j < z; j++)
				{

					per=0.0;
					
				
					srand(time(NULL) + j + k*z);

						for(i = 0;i < l; i++)
						{

						llenar(red,n,prob);
						hoshen(red,clase,n);
						//imprimir(red,clase,n);
    		
    					per=per+percola(red, mass, n, s, i, l);
						//printf("%d\n%g\n",per,prob);
						}

					perproba[j]=per/l;
				       q=2.0*q;

					if (perproba[j] <= 0.5)
					{ 
						prob+=(1.0/q);
					} 
            		else
            		{
            			prob+=(-1.0/q);
            		}
            	
				}

				pc[k]=prob;
				array[k] = pc[b++];
        		printf("%g\n" , array[k]);
        		fprintf(fp, "%f\n", array[k]);
			}
					
		 printf("\n%g\n" , average(pc,r));				

	}
	
	
			
		
			

		
	

//  free(red);

return (0);
}

void  llenar(int *red,int n,float prob){

	int i;
	int a;
	float b;
	float c;

	c = prob * 1000;
	

	for(i = 0; i < n*n; i++){

		b=0;
		a= rand() % 1000;

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


int   percola(int *red,float *mass, int n, int s, int v, int l)
{
	int i;
	int j,k,count;
	int per;
	int a;
	int b;
	int c;
	count=0;
	per=0;
	c=0;

	if(s==1)
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
							for(k=0;k<n*n;k++)
							{	
								if(red[k]==a)
								{
									count=count+1;

								}
								else
								{
									count=count;
								}

							}
								per=1;
								
						}
						else
						{
							per=per;
						}
					}
			}
			
		}

		mass[v]= sqrt(count);

		
	return(per);
	}
	else
	{
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



