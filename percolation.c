#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define P     16             // 1/2^P, P=16
#define Z     27000          // iteraciones
#define N     30             // lado de la red simulada

void  llenar(int *red,int n,float prob);
void  imprimir(int *red,int *clase,int n);
void  etiqueta_falsa(int *red,int *clase,int s1,int s2,int frag);
void  corregir_etiqueta(int *red,int *clase,int n);
int   actualizar(int *red,int *clase,int s,int frag);
int   hoshen(int *red,int *clase,int n);
int   percola(int *red,int n);


int  main()
{
		
	int i;
	int per;
	int n;
	int *red;
	float prob;
	int *clase;
	int m;
	n=30;
	red=(int *)malloc(n*n*sizeof(int));
	clase=(int *)malloc(n*n*sizeof(int));


	printf("Enter proba:   ");
	scanf("%g", &prob);
	
		
	llenar(red,n,prob);
	hoshen(red,clase,n);
        imprimir(red,clase,n);
	per=percola(red,n);
	printf("%d\n",per);
	

  free(red);

  return 0;
}

void  llenar(int *red,int n,float prob){

	int i;
	int a;
	float b;
	float c;

	c = prob * 1000;
	srand(time(NULL));
	

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
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la red y asigna etiquetas 
    a cada fragmento de red. 
  */

 	int i,j,k,s1,s2,frag;
 	
  	frag=0;
  
    	for(k=0;k<n*n;k++) *(clase+k)=frag;
  
  // primer elemento de la red

  	s1=0;
  	frag=2;
  	if (*red) frag=actualizar(red,clase,s1,frag);
  
  // primera fila de la red

  	for(i=1;i<n;i++) 
    	{
      			if (*(red+i)) 
         		{
          		s1=*(red+i-1);  
           		frag=actualizar(red+i,clase,s1,frag);
         		}
    	}
  

  // el resto de las filas 

 	for(i=n;i<n*n;i=i+n)
    	{

      // primer elemento de cada fila

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


void imprimir(int *red,int *clase,int n){

	int i,j,k,l;
        int array[n][n];
	int arrayclase[n][n];
	int m,b;
	m=0;
	b=0;
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


