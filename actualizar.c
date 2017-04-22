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
