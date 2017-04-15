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
void   percola(int *red,int n, float *size);
float average(float *pc,int z);


int  main()
{
	//int per;
	int n, i, j, z, l, t, k, r, y, h, s, q;
	int *red;
	float prob, *sc, *size, c;
	int *clase;
	n=30;
	y=0;
	float array[n*n+1];
	
	
	red=(int *)malloc(n*n*sizeof(int));
	size=(float *)malloc((n*n+1)*sizeof(float));
	clase=(int *)malloc(n*n*sizeof(int));
	sc=(float *)malloc((n*n+1)*sizeof(float));

	printf("How many iterations lvl1(#matrixes)?   ");
	scanf("%d", &l);
	printf("How many iterations lvl 2?(#averages of diferent seeds)   ");
	scanf("%d", &z);
	printf("Want to iterate on p?(1 for yes)   ");
	scanf("%d", &s);
	

	if(s!=1)
	{
		printf("Enter proba:   ");
		scanf("%g", &prob);

		FILE *fp;
		fp = fopen("Masas.txt", "a");

			for(t = 0;t <= n*n;t++)
			{
				sc[t]=0.0;
			}
	
			for(j = 0;j < z; j++)
			{

			
				srand(time(NULL) + j);
 
					for(i = 0;i < l; i++)
					{

						llenar(red,n,prob);
						hoshen(red,clase,n);
			
    					imprimir(red,clase,n);
    		
    					percola(red,n,size);
    						for(k = 0;k <= n*n;k++)
    						{
    							sc[k]=sc[k]+size[k]/(l*z);
    						}
    		
					
					}
			
			}
			for(r=0;r<=n*n;r++)
			{
				array[r]=sc[y++];
				printf("%g\n",array[r]);
				fprintf(fp, "%f %d %f\n", array[r], r, prob);
			}
	}
	else
	{
		printf("What's the resolution of p?   ");
		scanf("%g", &c);
		h=ceil(1.0/c);
		FILE *fp;
		fp = fopen("Masas.txt", "a");
			for(q = 0;q <= h; q++)
			{
				prob=0.0+ c*q;
				y=0;
				
					for(t = 0;t <= n*n;t++)
					{
						sc[t]=0.0;
						array[r]=0.0;
					}
	
					for(j = 0;j < z; j++)
					{

			
						srand(time(NULL) + j +q*z);
 
							for(i = 0;i < l; i++)
							{

								llenar(red,n,prob);
								hoshen(red,clase,n);
			
    							imprimir(red,clase,n);
    		
    							percola(red,n,size);
    								for(k = 0;k <= n*n;k++)
    								{
    									sc[k]=sc[k]+size[k]/(l*z);
    								}
    		
					
							}
			
					}
					for(r=0;r<=n*n;r++)
					{
						array[r]=sc[y++];
						printf("%g\n",array[r]);
						fprintf(fp, "%f %d %f\n", array[r], r, prob);
					}




			}
	}
  free(red);

  return 0;
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

void   percola(int *red,int n, float *size)
{
	int i, j,k, a, b, o, t, v, count;
	
	
	int *smart, *ssize;
	smart=(int *)malloc((n*n+1)*sizeof(int));
	ssize=(int *)malloc((n*n+1)*sizeof(int));
		for(o=0;o<=n*n;o++)
		{
			smart[o]=0;
			size[o]=0;
			ssize[o]=0;
		}
		for(k=0;k<n*n;k++)
		{
			v=red[k];
			smart[v]=v;
		}		
		for(i=0;i<n*n;i++)
		{
			count=0;
			if(smart[i]>0)
			{
				a=smart[i];
					for(j=0;j<n*n;j++)
					{
						b=red[j];
						if(a==b)
						{
							
							count=count+1;
							
						}
						else
						{
							count=count;
						}
					}
				ssize[i]=count;
			}
		
		}

		for(t=0;t<n*n;t++)
		{
			if(ssize[t]>0)
			{
				size[ssize[t]] = size[ssize[t]]+1;
        	}
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



