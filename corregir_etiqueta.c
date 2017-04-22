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
