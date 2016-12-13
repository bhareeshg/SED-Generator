void qusort(long p,long r,long crnd)
{

	if(p<r)
	{
		int q=partition(p,r,crnd);
		qusort(p,q-1,crnd);
		qusort(q+1,r,crnd);
	}	
}


int partition(long p,long r,long crnd)
{
	double x=temp[r];
	long i=p-1;
	long j;
	double td;
	long ti;
	for(j=p;j<=(r-1);j++)
	{
		if(temp[j]<=x)
		{
			i++;
			td=temp[i];
			temp[i]=temp[j];
			temp[j]=td;

			ti=ind[i][crnd];
			ind[i][crnd]=ind[j][crnd];
			ind[j][crnd]=ti;
		}
	}
	td=temp[i+1];
	temp[i+1]=temp[r];
	temp[r]=td;

	ti=ind[i+1][crnd];
	ind[i+1][crnd]=ind[r][crnd];
	ind[r][crnd]=ti;

	return i+1;
}
