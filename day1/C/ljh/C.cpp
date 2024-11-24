#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*f;
}
int T;
int a[1000007],n,x,p[1000007];
inline bool cmp2(int x,int y)
{
	return a[x]>a[y];
}
int main()
{
	T=read();
	while(T--)
	{
		n=read(),x=read();
		for(int i=1;i<=n;++i)
		a[i]=read(),p[i]=i;
		sort(p+1,p+n+1,cmp2);
		if(n==1)
		printf("%d\n",a[p[1]]);
		else if(n==2)
		printf("%d\n",a[p[1]]);
		else if(n==3)
		printf("%d\n",a[p[1]]);
		else if(n==4)
			printf("%d\n",a[p[2]]);
		else
		{
			if(x==1||x==n)
			{
				if(x==1)
				printf("%d\n",max(a[p[n-2]],min(a[1],a[2])));
				else
				printf("%d\n",max(a[p[n-2]],min(a[n],a[n-1])));
			}
			else
			{
				int b[3]={a[x-1],a[x],a[x+1]};
				
				sort(b,b+3);
				
				if(b[1]==a[p[n-1]])
				printf("%d\n",a[p[n-2]]);
				else
				printf("%d\n",b[1]);
			}
		}
	}
	return 0;
 } 
