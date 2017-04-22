void imprimir(int *red,int *clase,int n){    

	int i,j;
        int array[n][n];
	int m;
	m=0;
	
	for(j=0;j<n;j++) 
	{
        	for(i=0;i<n;i++)
        	{
            	array[j][i] = red[m++];
            	printf("%d " , array[j][i]);
       		}
	printf("\n");
	}
}

