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
