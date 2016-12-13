#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "header.h"
#include "sort.c"
#include "readparam.c"
#include "string.h"

copy2temp(int crnd)
{
	long i;
	for(i=0;i<size;i++)
	{
		temp[i]=data[i][crnd];
	}
}

node * newNode(long index)
{
	node *nn=(node *)malloc(sizeof(node));
	nn->index=index;
	nn->left=NULL;
	nn->right=NULL;

}

node * split(long start,long end,long crnd)
{
	long mid=(start+end)/2;
	long cpi=ind[mid][crnd];
	node *nn=newNode(cpi);	
	long i,j,k=0,l=mid+1;

	for(j=0;j<3;j++)
	{
		if(j!=crnd)
		{
			k=start;l=mid+1;

			for(i=start;i<=end;i++)
			{
				long cni=ind[i][j];
				
				if(data[cni][crnd]<data[cpi][crnd])
				{
					if(k==mid)
						printf("lol\n");
					li[k]=cni;
					k++;									
				}
				else if(data[cni][crnd]>data[cpi][crnd])
				{
					li[l]=cni;
					l++;
				}
				else if(cni==cpi)
				{                                                                                             
					li[mid]=cni;
				}
				else
				{
					long m;
					char flag='a';
					for(m=start;m<=end;m++)
					{
						if(ind[m][crnd]==cni && m>mid)
							flag='b';	
						if(ind[m][crnd]==cni && m<mid) 
							break;
					}
					if(flag=='a')
					{
						li[k]=cni;
						k++;
					}
					else
					{
						li[l]=cni;
						l++;
					}
				}
			}
			for(i=start;i<=end;i++)
			{

				ind[i][j]=li[i];				
			}	
		}		
	}
	return nn;
}

node * buildTree(long start,long end,long crnd)
{
	if(end-start+1>=3)
	{
		node *nn=split(start,end,crnd);
		crnd=(crnd+1)%NOD;
		long mid=(start+end)/2;

		nn->left=buildTree(start,mid-1,crnd);
		nn->right=buildTree(mid+1,end,crnd);

		return nn;
	}
	else if(end-start+1==2)
	{	
		long i;
		long ci1=ind[start][crnd];
		node *nn1=newNode(ci1);		
				
		long ci2=ind[end][crnd];
		node *nn2=newNode(ci2);
		nn1->right=nn2;
		return nn1;
	}
	else if(end-start+1==1)
	{
		long ci=ind[start][crnd];
		node *nn=newNode(ci);
		return nn;
	}
	else 
		return NULL;

}

getDataSpherical()
{
	FILE *finput;
	finput=fopen(Tfilename,"r");
		
	long i,j;
	double dat[2];
	double x,y,z;
	
	for(i=0;i<size;i++)
	{
		fscanf(finput,"%s	%lf	%lf",dataString[i],&dat[0],&dat[1]);
		z=sin(dat[1]*M_PI/180);
		y=cos(dat[1]*M_PI/180)*sin(dat[0]*M_PI/180);
		x=cos(dat[1]*M_PI/180)*cos(dat[0]*M_PI/180);
		data[i][0]=x;data[i][1]=y;data[i][2]=z;
		data[i][3]=dat[0];data[i][4]=dat[1];
		
		for(j=0;j<NOD;j++)
			ind[i][j]=i;
	}
	fclose(finput);
}

long nofds=0;
double avgsep=0;
searchRad(node *nn,double p[3],double radius,long crnd,char *line)
{
	if(nn==NULL)
		return;

	long i;
	double sum=0;
	for(i=0;i<NOD;i++)
		sum+=(p[i]-(data[nn->index][i]))*(p[i]-(data[nn->index][i]));
	sum=sqrt(sum);

	if(sum<=radius)
	{
		int cbytes=0;
		int k=0,h=0;
		int tbytes=0;
		int bbytes=0;int ci;
		char str[100];
		char stre[100];
		fprintf(fsed,"%s(Ra:%lf,Dec%lf)	",dataString[nn->index],data[nn->index][3],data[nn->index][4]);
		fprintf(fhist,"%e\n",2*asin(sum/2)*180*3600/M_PI);
		for(ci=0;ci<NOCString;ci++)
		{
			if(ci==pci[k])
			{
				sscanf(line+tbytes,"%[^\t\n]%n\t%[^\t\n]",str,&cbytes,stre);
				if(ci==freqInd[h])
				{
					
					double f=atof(str);
					double me=atof(stre);
					if(f0Mag[ci]!=-1)
					{
						f=f0Mag[ci]*pow(10,-0.4*f);
						me=f*0.4*2.3025*me;
					}
					if(frequency[i]==1.49)
					{	
						me*=1e-3;
						f*=1e-3;
					}
					fprintf(fsed,"%e	%e	%e	",f,frequency[ci],me);
					h++;
					
				}
				sprintf(buffer+bbytes,"%s",str);
				tbytes+=(cbytes+1);
				bbytes+=(cbytes+1);
				
				buffer[bbytes-1]='\t';
				k++;
			}
			else
			{
				sscanf(line+tbytes,"%*[^\t\n]%n",&cbytes);
				tbytes+=(cbytes+1);
			}
		}
		buffer[bbytes-1]='\0';

		avgsep+=2*asin(sum/2)*180*3600/M_PI;

		nofds++;
		fprintf(fsed,"\n");
		fprintf(foutput,"%e	%s	%lf	%lf	%s\n",2*asin(sum/2)*180*3600/M_PI,dataString[nn->index],data[nn->index][3],data[nn->index][4],buffer);
		//return;
	}

	if(p[crnd] < data[nn->index][crnd])
	{
		long crnd1=crnd;
		crnd=(crnd+1)%NOD;
		searchRad(nn->left,p,radius,crnd,line);
		if(fabs(p[crnd1]-(data[nn->index][crnd1]))<radius)
		{
			searchRad(nn->right,p,radius,crnd,line);
		}
	}
	else if(p[crnd] > data[nn->index][crnd])
	{
		long crnd1=crnd;
		crnd=(crnd+1)%NOD;
		searchRad(nn->right,p,radius,crnd,line);
		if(fabs(p[crnd1]-(data[nn->index][crnd1]))<radius)
		{
			searchRad(nn->left,p,radius,crnd,line);
		}
	}
	else
	{
		crnd=(crnd+1)%NOD;
		searchRad(nn->right,p,radius,crnd,line);
		searchRad(nn->left,p,radius,crnd,line);
	}

}

query()
{
	double arcsec=2.0;
	double deg=arcsec/3600;
	double rad=deg*M_PI/180;
	double d=2*sin(rad/2);
	node *nn=buildTree(0,size-1,0);

	FILE *finput;	
	finput=fopen(Qfilename,"r");
	long i;	
	double x,y,z;
	double p[3],dat[2];

	for(i=0;i<NOCString;i++)
	{
		fscanf(finput,"%lf",&frequency[i]);
	}	

	for(i=0;i<NOCString;i++)
	{
		fscanf(finput,"%lf",&f0Mag[i]);
	}

	while(getline(&line, &len, finput)!=-1)
	{	
		sscanf(line,"%lf	%lf",&dat[0],&dat[1]);
		z=sin(dat[1]*M_PI/180);
		y=cos(dat[1]*M_PI/180)*sin(dat[0]*M_PI/180);
		x=cos(dat[1]*M_PI/180)*cos(dat[0]*M_PI/180);
		p[0]=x;p[1]=y;p[2]=z;
		searchRad(nn,p,d,0,line);	
	}
	fclose(finput);
}
main()
{
	readParam();
	clock_t begin, end;
	double time_spent;
	begin = clock();

	getDataSpherical();
	int k;
	for(k=0;k<NOD;k++)
	{
		copy2temp(k);
		qusort(0,size-1,k);	
	}
		
	sprintf(Sedfilename,"output/SEDoutput.tsv");
	fsed=fopen(Sedfilename,"w");

	int i;
	for(i=0;i<nof;i++)
	{
		NOCString=NOCStringArray[i];
		Qfilename=QfilenameArray[i];
		freqInd=freqIndArray[i];

		printf("INPUT FILE NAME: %s\n",Qfilename);
		pci=pciArray[i];
		k=0;

		sprintf(Ofilename,"output/output");
		sprintf(Histfilename,"output/hist");
		sscanf(Qfilename,"Catalogues/%s",Ofilename+13);
		sscanf(Qfilename,"Catalogues/%s",Histfilename+11);

		foutput=fopen(Ofilename,"w");
		fhist=fopen(Histfilename,"w");
		query();

		fclose(foutput);
		fclose(fhist);

		printf("NOFSS:::::%ld AverageSep:%lf\n",nofds,avgsep/nofds);
		nofds=0;
		avgsep=0;
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("TOTAL TIME SPENT::%lf\n",time_spent);
}
