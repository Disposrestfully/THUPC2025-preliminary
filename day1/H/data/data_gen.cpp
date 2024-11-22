#include<iostream>
#include<cstdio>
#include<algorithm>
#include<random>
#include<chrono>
#include<cmath>
using namespace std;
int n,q;int cnt,p[250005],vis[250005];
int id[250005],op[250005],ql[250005],qr[250005],qc[250005],qx[250005],a[250005];
void init(int n)
{
	for(int i=2;i<=n;i++)
		if(!vis[i])
			for(int j=2*i;j<=n;j+=i) vis[j]=1;
	for(int i=2;i<=n;i++)
		if(!vis[i]) p[++cnt]=i;
}
int main()
{
	init(250000);
	unsigned seed=chrono::system_clock::now().time_since_epoch().count();
	mt19937 gen(seed);
	uniform_int_distribution<> sm(0,999);
	uniform_int_distribution<> gc(2,250000);
	uniform_int_distribution<> rnd(1,998244352);
	for(int T=1;T<=30;T++)
	{
		char nam[101];
		sprintf(nam,"%d.in",T);
		freopen(nam,"w",stdout);
		if(1<=T&&T<=8)
		{
			n=1000-sm(gen)%10,q=5000-sm(gen)%50;
			uniform_int_distribution<> ps(1,n);
			printf("%d %d\n",n,q);
			if(1<=T&&T<=2)
			{
				for(int i=1;i<=n;i++) printf("%d ",rnd(gen));printf("\n");
				for(int i=1;i<=q;i++)
				{
					int cz=sm(gen)%5;
					if(cz<=2||(T==2&&cz==3))
					{
						int l=ps(gen)%(n*(T==1?1:2)/3)+1,r=l+ps(gen)%(n-l+1);
						int c=gc(gen);
						printf("1 %d %d %d\n",l,r,c);
					}
					else
					{
						int x=ps(gen);
						printf("2 %d\n",x);
					}
				}
			}
			else
			{
				// sqrt n以上的质数可以大规模砍掉；
				// sqrt n以下的质数慢慢的砍掉，每次少做一点，把重构复杂度卡满。
				// 一部分数据负责卡满修改，需要每次都在乘质数；
				// 一部分数据负责检验正确性，允许乘合数；
				// 查询时大部分集中在前面卡满复杂度，小部分随机乱撒检验正确性。 
				// 除了卡满复杂度的必要修改，修改的比例也要设置梯度。 
				// 初始的 a，一部分随机，一部分全 1。 
				if(3<=T&&T<=5)
					for(int i=1;i<=n;i++) a[i]=1;
				else
					for(int i=1;i<=n;i++) a[i]=rnd(gen);
				int mp=sqrt(n);
				int cq=0;
				for(int i=1;i<=cnt;i++)
					if(mp<p[i]&&p[i]<=n)
					{
						int l=ps(gen)%p[i]+1,r=max(l+(n-l)/2,n-(ps(gen)%p[i]+1));
						cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=p[i];
					}
				for(int i=1;i<=cnt;i++)
					if(p[i]<=mp)
					{
						int cs=0,tmp=1;while(tmp<=n) tmp*=p[i],cs++;
						int rc=cs+rnd(gen)%(cs+1);
						for(int j=1;j<=rc;j++)
						{
							int l=ps(gen)%(n*(T<=5?1:2)/3)+1,r=l+ps(gen)%(n-l+1);
							cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=p[i];
						}
					}
				int tq=0;
				if(T==3||T==6) tq=max(cq,q*3/10);
				if(T==4||T==7) tq=max(cq,q*2/5);
				if(T==5||T==8) tq=max(cq,q/2);
				for(int i=cq+1;i<=tq;i++)
				{
					int l=ps(gen),r=l+ps(gen)%(n-l+1);
					int c=gc(gen);
					cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=c;
				}
				for(int i=tq+1;i<=q;i++)
				{
					int cur=rnd(gen)%10;int x;
					if(cur==0) x=ps(gen);
					else x=ps(gen)%(n/10)+1;
					cq++;op[cq]=2;qx[cq]=x;
				}
				for(int i=1;i<=q;i++) id[i]=i;
				for(int i=1;i<=q*2;i++)
				{
					int x=rnd(gen)%q+1,y=rnd(gen)%q+1;
					swap(id[x],id[y]);
				}
//				random_shuffle(id+1,id+1+q);
				for(int i=1;i<=n;i++) printf("%d ",a[i]);printf("\n");
				for(int i=1;i<=q;i++)
				{
					printf("%d ",op[id[i]]);
					if(op[id[i]]==2) printf("%d\n",qx[id[i]]);
					else printf("%d %d %d\n",ql[id[i]],qr[id[i]],qc[id[i]]);
				}
			}
		}
		else
		{
			n=250000-sm(gen),q=250000-sm(gen);
			uniform_int_distribution<> ps(1,n);
			printf("%d %d\n",n,q);
			if(9<=T&&T<=12)
			{
				uniform_int_distribution<> rnd(1,998244352);
				for(int i=1;i<=n;i++) printf("%d ",rnd(gen));printf("\n");
				for(int i=1;i<=q;i++)
				{
					int cz=sm(gen)%5;
					if(cz<=1||(T==12&&cz==2)||(T>=10&&cz==3))
					{
						int l=ps(gen)%(n*(T<=10?1:2)/3)+1,r=l+ps(gen)%(n-l+1);
						int c=gc(gen);
						printf("1 %d %d %d\n",l,r,c);
					}
					else
					{
						int x=ps(gen);
						printf("2 %d\n",x);
					}
				}
			}
			else
			{
				if(13<=T&&T<=21)
					for(int i=1;i<=n;i++) a[i]=1;
				else
					for(int i=1;i<=n;i++) a[i]=rnd(gen);
				int mp=sqrt(n);
				int cq=0;
				for(int i=1;i<=cnt;i++)
					if(mp<p[i]&&p[i]<=n)
					{
						int l=ps(gen)%p[i]+1,r=max(l+(n-l)/2,n-(ps(gen)%p[i]+1));
						cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=p[i];
					}
				for(int i=1;i<=cnt;i++)
					if(p[i]<=mp)
					{
						int cs=0,tmp=1;while(tmp<=n) tmp*=p[i],cs++;
						int rc=cs+rnd(gen)%(cs+1);
						for(int j=1;j<=rc;j++)
						{
							int l=ps(gen)%(n*(T<=21?1:2)/3)+1,r=l+ps(gen)%(n-l+1);
							cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=p[i];
						}
					}
				int tq=0;
				if(T==13||T==22) tq=max(cq,q*25/100);
				if(T==14||T==23) tq=max(cq,q*3/10);
				if(T==15||T==24) tq=max(cq,q*35/100);
				if(T==16||T==25) tq=max(cq,q*4/10);
				if(T==17||T==26) tq=max(cq,q*45/100);
				if(T==18||T==27) tq=max(cq,q/2);
				if(T==19||T==28) tq=max(cq,q*6/10);
				if(T==20||T==29) tq=max(cq,q*7/10);
				if(T==21||T==30) tq=max(cq,q*8/10);
				for(int i=cq+1;i<=tq;i++)
				{
					int l=ps(gen),r=l+ps(gen)%(n-l+1);
					int c=gc(gen);
					cq++;op[cq]=1;ql[cq]=l;qr[cq]=r;qc[cq]=c;
				}
				for(int i=tq+1;i<=q;i++)
				{
					int cur=rnd(gen)%((13<=T&&T<=16)||(26<=T&&T<=30)?5:10);int x;
					if(cur==0) x=ps(gen);
					else x=ps(gen)%(n/10)+1;
					cq++;op[cq]=2;qx[cq]=x;
				}
				for(int i=1;i<=q;i++) id[i]=i;
				for(int i=1;i<=q*2;i++)
				{
					int x=rnd(gen)%q+1,y=rnd(gen)%q+1;
					swap(id[x],id[y]);
				}
//				random_shuffle(id+1,id+1+q);
				for(int i=1;i<=n;i++) printf("%d ",a[i]);printf("\n");
				for(int i=1;i<=q;i++)
				{
					printf("%d ",op[id[i]]);
					if(op[id[i]]==2) printf("%d\n",qx[id[i]]);
					else printf("%d %d %d\n",ql[id[i]],qr[id[i]],qc[id[i]]);
				}
			}
		}
	}
	return 0;
}
