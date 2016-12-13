readParam()
{
	FILE *fp=fopen("input.param","r");
	fscanf(fp,"%s",Tfilename);
	printf("%s\n",Tfilename);
	fscanf(fp,"%d",&nof);
	printf("%d\n",nof);
	int i;
	for(i=0;i<nof;i++)
	{
		int j;
		fscanf(fp,"%s",QfilenameArray[i]);
		
		fscanf(fp,"%d",&NOCStringArray[i]);	
		for(j=0;j<NOCStringArray[i];j++)
		{
			fscanf(fp,"%d",&pciArray[i][j]);
		}

		fscanf(fp,"%d",&nofreq[i]);	
		for(j=0;j<NOCStringArray[i];j++)
		{
			fscanf(fp,"%d",&freqIndArray[i][j]);
		}
	}

	for(i=0;i<nof;i++)
	{
		int j;
		printf("%s\n",QfilenameArray[i]);
		
		printf("%d\n",NOCStringArray[i]);	
		for(j=0;j<NOCStringArray[i];j++)
		{
			printf("%d	",pciArray[i][j]);
		}

		printf("\n%d\n",nofreq[i]);	
		for(j=0;j<NOCStringArray[i];j++)
		{
			printf("%d	",freqIndArray[i][j]);
		}
		printf("\n");
	}
	
		
}
