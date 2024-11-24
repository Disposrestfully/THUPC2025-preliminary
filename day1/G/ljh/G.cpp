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
char a[1000007];
int main()
{
	T=read();
	while(T--)
	{
		scanf("%s",a+1);
		int n=strlen(a+1);
		a[0]=a[n+1]='X';
		int num[2]={0,0};
		int l=1;
		while(l<=n)
		{
			if(a[l]=='X')
			{
				++l;
				continue;
			}
			
			int r=l;
			while(a[r]==a[l])
			++r;
			if(a[l]=='W')
			++num[0];
			else
			++num[1];
			
			l=r;
		}
		if(num[0]-1>num[1])
		puts("Menji");
		else if(num[0]<num[1])
		puts("Water");
		else if(num[0]-1==num[1])
		{
			bool ans=0;
			int l=1;
			while(l<=n)
			{
				if(a[l]=='X')
				{
					++l;
					continue;
				}
				
				int r=l;
				while(a[r]!='X')
				++r;
				
				--r;
				if(a[l]=='W'&&a[r]=='W')
				{
					for(int i=l+1;i<=r-1;++i)
					ans|=(a[i]=='M');
				}
				
				l=r+2;
			}
			if(ans)
			puts("Draw");
			else
			puts("Menji");
		}
		else
		{
			bool ans=0;
			int l=1;
			while(l<=n)
			{
				if(a[l]=='X')
				{
					++l;
					continue;
				}
				
				int r=l;
				while(a[r]!='X')
				++r;
				
				--r;
				if(a[l]=='M'&&a[r]=='M')
				{
					for(int i=l+1;i<=r-1;++i)
					ans|=(a[i]=='W');
				}
				
				l=r+2;
			}
			if(ans)
			puts("Draw");
			else
			puts("Water");
		}
	}
	return 0;
 } 
