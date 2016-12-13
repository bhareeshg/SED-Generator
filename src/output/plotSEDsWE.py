from numpy import *
from pylab import *
import matplotlib.pyplot as plt

x = [-1] * 30
y = [-1] * 30
ye = [-1] * 30
clr=['b']*30
xi=0;
yi=0;
yei=0;
on=0;	
flag=0;
f=plt.figure();
plt.autoscale(enable=True, axis='both', tight=None)
awbc=[89500.0, 65170.0, 25930.0, 13570.0];
sdsc=[851900.0, 622000.0, 479900.0, 392700.0, 332400.0];
first=[1.4];
pi=1;np=1;
ax=None;ax1=None;ax2=None;ax3=None;ax4=None;
with open('SEDoutputsorted.tsv')	as fl:
	curStr=''
	for line in fl:	
		if on<=567:
			line=line.rstrip();
			values=line.split("\t");
			print values[0]
			if curStr==values[0]:		
				i=0;
				for v in values:
					if(i>0):
						if i%3==2:
							if float(v) not in x:
								flag=0;
								x[xi]=float(v);
								if float(v) in awbc:
									clr[xi]='r';
								if float(v) in sdsc:
									clr[xi]='y';
								if float(v) in first:
									clr[xi]='k';	
								xi=xi+1;
							else:
								flag=1
						elif i%3==1:
							if flag==0:
								y[yi]=float(v);
								yi=yi+1;
						else: 
							if flag==0:
								ye[yei]=float(v);			
								yei=yei+1;
					i=i+1;
			else:
				if on>0:
					if xi>5:
						print x
						print y
						print ye
						y=[a*b*1e-17 for a,b in zip(x,y)];
						ye=[a*b*1e-17 for a,b in zip(x,ye)];
						x=[3e5/a for a in x];
						#################################################################
						if pi<5:
							if pi==1:
								f, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, sharex='col', sharey='row');
								ax=ax1;	
								ax.set_ylabel(r'$\nu F(\nu)(Wm^{-2})$');
							if pi==2:
								ax=ax2;
							if pi==3:
								ax=ax3;
								ax.set_xlabel(r'Wavelength($\mu$m)');
								ax.set_ylabel(r'$\nu F(\nu)(Wm^{-2})$');
							if pi==4:
								ax=ax4;
								ax.set_xlabel(r'Wavelength($\mu$m)');
								#ax.set_ylabel(r'$\nu F(\nu)(Wm^{-2})$');
							ax.set_title(curStr,fontsize=7);
							ax.set_xscale('log');
							ax.set_yscale('log');
							ax.grid(True);					
							ax.scatter(x,y,c=clr,s=26);
							ax.errorbar(x,y,yerr=ye,linestyle="None",c='k');
							pi=pi+1;					
						else:
							f.savefig('SEDMultiplots/SED'+str(np)+'WE.pdf');
							np=np+1;						
							close(f);
							pi=1;
							f, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, sharex='col', sharey='row');						
							ax=ax1;
							ax=f.add_subplot(2,2,pi);
							ax.set_title(curStr,fontsize=7);
							#ax.set_xlabel(r'Wavelength($\mu$m)');
							ax.set_xscale('log');
							ax.set_ylabel(r'$\nu F(\nu)(Wm^{-2})$');
							ax.set_yscale('log');
							ax.grid(True);					
							ax.scatter(x,y,c=clr,s=26);
							ax.errorbar(x,y,yerr=ye,linestyle="None",c='k');
							pi=pi+1;
						####################################################################				
				#on=on+1;
				curStr=values[0]
				x=[-1] * 30;
				y=[-1] * 30;
				ye=[-1] * 30;
				clr=['b']*30;
				on=on+1;
				xi=0;yi=0;yei=0;
				i=0;
				flag=0;
				for v in values:
					if(i>0):
						if i%3==2:
							x[xi]=float(v);
							if float(v) in awbc:
								clr[xi]='r';
							if float(v) in sdsc:
								clr[xi]='y';
							if float(v) in first:
								clr[xi]='k';	
							xi=xi+1;
						elif i%3==1:
							y[yi]=float(v);
							yi=yi+1;
						else: 
							ye[yei]=float(v);			
							yei=yei+1;
					i=i+1;	
		else:
			break;

f.savefig('SEDMultiplots/SED'+str(np)+'WE.pdf');						
close(f);
#fnames=['hist2massXpqsWE','histallwiseXpqsWE','histsdssXpqsWE']
fnames=['histSDSSUniq','histallwiseUniq','hist2massUniq']
for n in fnames:
	h6 = loadtxt(n+'.tsv');
	h,l=histogram(h6,bins=100);
	print h
	print l
	#print m;
	plt.hist(h6,bins=80);
	#plt.title('Histogram of angular seperation :'+n[4:-6]);
	plt.title('Histogram of angular seperation :'+n[4:-4]);
	plt.xlabel('angular distance(arc seconds)');
	txt='Mean :'+(str)(mean(h6))+'\nStandard Deviation :'+(str)(std(h6))+'\n'
	#plt.text(1,m,txt);
	plt.xlim([0,3]);
	plt.ylabel('number of objects');	
	plt.savefig('SEDMultiplots/HIST'+n+'.pdf');
	plt.clf();
	h6=[None];						
	
