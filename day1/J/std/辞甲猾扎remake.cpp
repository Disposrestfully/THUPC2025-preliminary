#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace tokido_saya {
	const int maxn=1e6+5;
	struct edge
	{
		int next,to;
	}e[maxn*2];
	int h[maxn],cnt,f[maxn][4],n,k,b[maxn],nr[maxn],ans;
	void addedge(int x,int y)
	{
		e[++cnt].next=h[x],e[cnt].to=y,h[x]=cnt;
	}
	void dfs(int u,int fa)
	{
		if(b[u])f[u][0]=f[u][1]=f[u][2]=1e9;
		else f[u][0]=1,f[u][1]=1e9;
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==fa)continue;
			dfs(v,u);
			if(!b[u])f[u][0]+=min(min(f[v][0],f[v][1]),min(f[v][2],f[v][3])),f[u][0]=min(f[u][0],(int)1e9);
			if(!b[u])f[u][1]=min(f[u][3]+f[v][0],f[u][1]+min(min(f[v][0],f[v][1]),f[v][3])),f[u][1]=min(f[u][1],(int)1e9);
			if(!b[u])f[u][2]+=min(f[v][1],f[v][3]),f[u][2]=min(f[u][2],(int)1e9);
			f[u][3]+=min(min(f[v][0],f[v][1]),f[v][3]),f[u][3]=min(f[u][3],(int)1e9);
		}
		if(nr[u]&&!b[u])f[u][3]=1e9;
//		cout<<u<<' '<<b[u]<<' '<<nr[u]<<' '<<f[u][0]<<' '<<f[u][1]<<' '<<f[u][2]<<' '<<f[u][3]<<'\n';
	}
	int main() {
//		freopen("12.in","r",stdin);
//		freopen("12.ans","w",stdout);
		int x,y;
		n=read(),k=read();
		for(int i=1;i<=k;i++)x=read(),b[x]=1;
		for(int i=1;i<n;i++)
		{
			x=read(),y=read();
			addedge(x,y),addedge(y,x);
		}
		for(int u=1;u<=n;u++)
			if(b[u])for(int i=h[u];i;i=e[i].next)
			{
				int v=e[i].to;
				nr[v]=1;
			}
		dfs(1,0);
		printf("%d",min(min(f[1][0],f[1][1]),f[1][3]));
		return 0;
	}
}
int main() {
	return tokido_saya::main();
}

