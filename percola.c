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
