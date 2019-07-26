/*
Count data
Not tested
 */
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
struct fz
{
	union
	{
		unsigned int i_beg;
		double d_beg;
	};
	union
	{
		unsigned int i_js;
		double d_js;
	};
	unsigned int z_nu;
};
bool sel_id;
bool dy;
void *jx,*max,*min,*sum,*zz;
double ss_pzz,fc,bzc;
unsigned int alnum=0,zs=0,ys_num=1;
fz *gfz;
void *inp;
void *cla;
double sc,*ps;
unsigned int sel;
vector<unsigned int> num;
void *lsnum[5];
unsigned int n=0;
inline double qf(double a,unsigned int b,bool c)
{
	unsigned int d;
	if(c)
	{
		for(d=0;d<=b;d++)
		{
			a=a*10;
		}
	}
	else
	{
		for(d=0;d<=b;d++)
		{
			a=a/10;
		}
	}
	return a;
}
void fzf()
{
	void *ls;
	unsigned int *cl;
	unsigned int l[3];
	cout<<"Enter group number"<<endl;
	cin>>zz;
	cout<<"-0.5(j) or =<"<<endl;
	l[0]=n;
	lsnum[n]=new bool;
	n++;
	l[1]=n;
	lsnum[n]=new char;
	cin>>lsnum[n];
	if(*(char*)lsnum[n]=='j')
	{
		*(bool*)lsnum[l[0]]=true;
		sel_id=true;
		dy=false;
	}
	else
	{
		dy=true;
	}
	delete lsnum[n];
	if(sel==2)
	{
		cout<<"How many decimal places to keep"<<endl;
		cin>>ys_num;
	}
	else
	{
		sel_id=false;
	}
	jx=max-min;
	zz=(*jx)/zs;
	if(sel==1)
	{
		if((*zz)*zs!=jx)
		{
			(*zz)++;
		}
  gfz=new fz[zs];
	}
	else
	{
		if((*zz)*zs!=jx)
		{
			(double*)ls=new double;
			cl=new unsigned int;
			for(unsigned int tim=0;tim<=ys_num;tim++)
			{
				*(double*)zz=(*(double*)zz)*10;
			}
			*cl=(unsigned int)zz;
			(*cl)++;
			*(double*)ls=(double)*cl;
			for(unsigned int ti=0;ti<=ys_num;ti++)
			{
				*ls=*(double*)ls/10;
			}
			*zz=*ls;
			if(((*jx)/(*zz))%1!=0)
			{
				zs++;
			}
			gfz=new fz[zs];
			delete ls;
			delete cl;
		}
	}
	if(sel_id)
	{
		gfz[0].d_beg=min;
	}
	else
	{
		gfz[0].i_beg=min;
	}
	if(lsnum[l[0]])
	{
		lsnum[n]=new double;
		l[2]=n;
		n++;
		*(double*)lsnum[l[2]]=qf(0.5,ys_num+1,false);
		gfz[0].d_beg=gfz[0].d_beg-*(double*)lsnum[l[2]];
		delete lsnum[l[2]];
		n--;
	}
	for(unsigned int lsa=0;lsa<zs;lsa++)
	{
		if(lsa==0)
		{
			if(sel_id)
			{
				gfz[lsa].d_js=gfz[lsa].d_beg+*(double*)zz;
			}
			else
			{
				gfz[lsa].i_js=gfz[lsa].i_beg+*(unsigned int*)zz;
			}
			continue;
		}
		if(sel_id)
		{
			gfz[lsa].d_beg=gfz[lsa-1].d_js;
			gfz[lsa].d_js=gfz[lsa].d_beg+*(double*)zz;
		}
		else
		{
			gfz[lsa].i_beg=gfz[lsa-1].i_js;
			gfz[lsa].i_js=gfz[lsa].i_beg+*(unsigned int*)zz;
		}
	}
	for(unsigned int lsb=0;lsb<alnum;lsb++)
		{
			for(unsigned int lsc=0;lsc<zs;lsc++)
			{
				if(sel_id)
				{
					if((*(*vector<unsigned int>)inp[lsb]>gfz[lsc].i_beg| ((* (*vector<unsigned int>) inp[lsb]==gfz[lsc].i_beg)&&dy) )&&*(*vector<unsigned int>) inp[lsb]<gfz[lsc].i_js)
					{
						gfz[lsc].z_nu++;
						break;
					}
				}
				else
				{
					 if((* (*vector<double>) inp[lsb]>gfz[lsc].d_beg| ((inp[lsb]==gfz[lsc].d_beg)&&dy) )&&inp[lsb]<gfz[lsc].d_js)
					{
						gfz[lsc].z_nu++;
						break;
					}
				}
				sc=sc+pow(abs(inp[lsb]-ss_pzz),2);
			}
		}
	
}
int main()
{
	unsigned int *cl=new unsigned int;
	void *ls;
	err:;
	cout<<"Character (s),decimal(d) or integer(i) "<<endl;
	cin>>*cl;
	switch(*cl)
	{
		case 's':
			(vector<string>*)inp=new vector<string>;
			cla=new vector<string>;
			ls=new string;
			sel=0;
			break;
		case 'i':
			(*vector<unsigned int> )inp=new vector<unsigned int>;
			cla=NULL;
			ls=new unsigned int;
			jx=new unsigned int;
			max=new unsigned int;
			min=new unsigned int;
			sum=new unsigned int;
			zz=new unsigned int;
			sel=1;
			break;
		case 'd':
			(*vector<double> )inp=new vector<double>;
			jx=new double;
			max=new double;
			min=new double;
			sum=new double;
			zz=new double;
			sel=2;
			break;
		default:
			cout<<"input error"<<endl;
			goto err;
			break;
	}
	delete cl;
	cl=NULL;
	if(cla==NULL)
	{
		goto xn;
	}
	cout<<"Enter categories"<<endl;
	while(cin>>*ls)
	{
		cla->push_back(*ls);
		num->push_back(0);
	}
	xn:;
	cout<<"Input data"<<endl;
	while(cin>>*ls)
	{
		inp->push_back(*ls);
	}
	delete ls;
	ls=NULL;
	alnum=lsn->size();
	ps=new double[alnum];
	if(sel==0)
	{
		cl=new unsigned int;
		*cl=cla->size();
	}
	for(unsigned int bl=0;bl<alnum;bl++)
	{
		if(sel)
		{
			isn[bl]>max? max=bl:0;
			isn[bl]<min? min=isn[bl]:0;
			sum=sum+isn[bl];
		}
		else
		{
			for(unsigned int clal=0;cpal<*cl,clal++)
			{
				if(isn[bl]==cla[clal])
				{
					num[clal]++;
					break;
				}
			}
		}
	}	
	if(sel!=0)
	{
		fzf()
		ss_pzz=sum/alnum;
		fc=sc/alnum;
		bzc=sqrt(fc);
	}
	else
	{
		for(auto lt=0;lt<=alnum;lt++)
		{
			ps[lt]=num[lt]/alnum;
		}
	}
	cout<<endl<<endl;
	cout<<"The number of data:"<<alnum<<endl;
	cout<<"Type of data:";
	switch(sel)
	{
		case 0:
			cout<<"character"<<endl;
			break;
		case 1:
			cout<<"Integer"<<endl;
			break;
		case 2:
			cout<<"Decimal"<<endl;
			break;
	}
	cout<<endl;
	cout<<"频数分布"<<endl;
	if(sel!=0)
	{
		if(dy)
		{
			lsnum[lsn]=new char[2];
			lsnum[lsn]={"<="}
		}
		cout<<"Number of groups :"<<zs<<endl;
		cout<<"Group spacing:"<<*zz<<endl;
		else
		{
			lsnum[lsn]=new char;
			lsnum[lsn]='<';
		}
		if(sel_id)
		{
			for(t=0;t<zs;t++)
			{
				cout<<gfz[t].i_beg<<lsnum[lsn];
				cout<<"x<"<<gfz[t].i_js;
				cout<<" "<<gfz[t].z_nu;
				cout<<" "<<ps;
			}
		}
		else
		{
			for(t=0;t<zs;t++)
			{
				cout<<gfz[t].d_beg<<lsnum[lsn];
				cout<<"x<"<<gfz[t].d_js;
				cout<<" "<<gfz[t].z_nu;
				cout<<" "<<ps;
			}
		}
		delete lsnum[lsn];
	}
	else
	{
		lsnum[lsn]=new unsigned int;
		lsnum[lsn]=cla->size();
		for(auto v=0;v<lsnum[lsn];v++)
		{
			cout<<cla[v]<<" "<<num[v]<<" ";
			cout<<ps[v]<<endl;
		}
	}
	cout<<endl;
	if(sel==0)
	{
		cout<<"Press Enter to exit"<<endl;
		cin.get();
		cin.get();
		return 0;
	}
	cout<<"Maximum:"<<*max<<endl;
	cout<<"Min:"<<*min<<endl;
	cout<<"Range:"<<*jx<<endl;
	cout<<"Sum:"<<*sum<<endl;
	cout<<"Arithmetic mean:"<<ss_pzs<<endl;
	cout<<"Variance:"<<fc<<endl;
	cout<<"Standard deviation:"<<bzc<<endl;
	cout<<endl;
	cout<<"Press Enter to exit"<<endl;
 delete gfz;
 delete inp;
 delete cla;
 delete ps;
 delete max;
 delete min;
 delete jx;
 delete sum;
 delete zz;
	cin.get();
	cin.get();
	return 0;
}