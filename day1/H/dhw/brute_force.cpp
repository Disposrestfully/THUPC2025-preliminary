#include<iostream>
#include<cstdio>
using namespace std;
const int mod=998244353;
int n,q,a[250005],rs[250005];int op,l,r,c,x;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),rs[i]=gcd(i,a[i]);
	while(q--)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&l,&r,&c);
			for(int i=l;i<=r;i++)
			{
				int cur=i/rs[i];
				int d=gcd(c,cur);
				rs[i]*=d;a[i]=1ll*a[i]*c%mod;
			}
		}
		if(op==2)
		{
			scanf("%d",&x);
			int ans=0;
			while(x<=n)
			{
				ans=(ans+a[x])%mod;
				x+=rs[x];
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
