#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int B=300,mod=998244353;
int n,q,op,l,r,c,x,ks,a[250005],rs[250005],cd[250005],cv[250005],tag[1005];
int cnt,p[250005];bool v[250005];set<int> s[250005];
template<typename T> void Read(T &x)
{
	x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
}
void init(int n)
{
	for(int i=2;i<=n;i++)
		if(!v[i])
		{
			p[++cnt]=i;
			for(int j=i*2;j<=n;j+=i) v[j]=1;
		}
}
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
void upd(int l,int r,int cs,int cp)
{
	auto be=s[cp].lower_bound(l);
	while(be!=s[cp].end()&&*be<=r)
	{
		int now=*be;int nr=now/rs[now],cc=0;
		while(nr%cp==0&&cc<cs) nr/=cp,rs[now]*=cp,cc++;
		int bl=(now-1)/B+1,L=(bl-1)*B+1,R=min(n,bl*B);int nto=now+rs[now];
		if(nto>n) cd[now]=n+1,cv[now]=a[now];
		else if(nto>R) cd[now]=nto,cv[now]=a[now];
		else cd[now]=cd[nto],cv[now]=(a[now]+cv[nto])%mod;
		for(int i=now-1;i>=L;i--)
		{
			int to=i+rs[i];
			if(to>n) cd[i]=n+1,cv[i]=a[i];
			else if(to>R) cd[i]=to,cv[i]=a[i];
			else cd[i]=cd[to],cv[i]=(a[i]+cv[to])%mod;
		}
		if(nr%cp) be=s[cp].erase(be);
		else be++;
	}
}
void rb(int x,int l,int r,int c)
{
	int L=(x-1)*B+1,R=min(n,x*B);
	for(int i=L;i<=R;i++)
	{
		a[i]=1ll*a[i]*tag[x]%mod;
		if(l<=i&&i<=r) a[i]=1ll*a[i]*c%mod;
	}
	for(int i=R;i>=L;i--)
	{
		int to=i+rs[i];
		if(to>n) cd[i]=n+1,cv[i]=a[i];
		else if(to>R) cd[i]=to,cv[i]=a[i];
		else cd[i]=cd[to],cv[i]=(a[i]+cv[to])%mod;
	}
	tag[x]=1;
}
int main()
{
	Read(n);Read(q);
	for(int i=1;i<=n;i++) Read(a[i]),rs[i]=gcd(i,a[i]);
	init(n);
	for(int i=1;i<=n;i++)
	{
		int tmp=i/rs[i];
		for(int j=1;p[j]*p[j]<=tmp;j++)
			if(tmp%p[j]==0)
			{
				s[p[j]].insert(i);
				while(tmp%p[j]==0) tmp/=p[j];
			}
		if(tmp>1) s[tmp].insert(i);
	}
	ks=(n-1)/B+1;
	for(int i=ks;i>=1;i--)
	{
		int L=(i-1)*B+1,R=min(n,i*B);
		for(int j=R;j>=L;j--)
		{
			int to=j+rs[j];
			if(to>n) cd[j]=n+1,cv[j]=a[j];
			else if(to>R) cd[j]=to,cv[j]=a[j];
			else cd[j]=cd[to],cv[j]=(a[j]+cv[to])%mod;
		}
		tag[i]=1;
	}
	while(q--)
	{
		Read(op);
		if(op==1)
		{
			Read(l);Read(r);Read(c);
			int tc=c;
			for(int j=1;p[j]*p[j]<=tc;j++)
				if(tc%p[j]==0) 
				{
					int cs=0;while(tc%p[j]==0) tc/=p[j],cs++;
					upd(l,r,cs,p[j]);
				}
			if(tc>1) upd(l,r,1,tc);
			int bl=(l-1)/B+1,br=(r-1)/B+1;
			for(int i=bl+1;i<=br-1;i++) tag[i]=1ll*tag[i]*c%mod;
			if(bl==br) rb(bl,l,r,c);
			else rb(bl,l,bl*B,c),rb(br,(br-1)*B+1,r,c);
		}
		if(op==2)
		{
			Read(x);
			int ans=0,dq=x;
			while(dq<=n)
			{
				int bl=(dq-1)/B+1;
				ans=(ans+1ll*tag[bl]*cv[dq])%mod;
				dq=cd[dq];
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
