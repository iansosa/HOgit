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

