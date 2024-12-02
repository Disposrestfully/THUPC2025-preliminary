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
	const int maxn=6e5+5;
	struct edge
	{
		int next,to;
	}e[maxn*2];
	struct node
	{
		ll v;
		int c;
		node(){}
		node(ll v,int c)
		{
			this->v=v,this->c=c;
		}
		node operator+(node b)
		{
			return node(v+b.v,c+b.c);
		}
		node &operator+=(node b)
		{
			return *this=*this+b;
		}
		friend bool operator<(const node a,const node b)
		{
			return a.v==b.v?a.c<b.c:a.v<b.v; 
		}
	}tmp[maxn*8],*f[maxn],*g[maxn],*tf[maxn],*tg[maxn],dp[maxn],*id=tmp,inf((ll)1e18,1e9);
	int n,k,m,h[maxn],cnt,d[maxn],b[maxn],maxd[maxn],son[maxn],dis[maxn],siz[maxn];
	queue<int> q;
	void addedge(int x,int y)
	{
		e[++cnt].next=h[x],e[cnt].to=y,h[x]=cnt;
	}
	void dfs1(int u,int fa)
	{
		siz[u]=b[u];
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==fa)continue;
			dfs1(v,u),siz[u]+=siz[v];
			if(maxd[v]>maxd[son[u]])son[u]=v;
		}
		maxd[u]=maxd[son[u]]+1;
//		if(maxd[u]<maxd[u+1])abort();
	}
	void bfs()
	{
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=h[u];i;i=e[i].next)
			{
				int v=e[i].to;
				if(!dis[v]&&!b[v])dis[v]=dis[u]+1,q.push(v);
			}
		}
		for(int i=1;i<=n;i++)dis[i]=min(dis[i],maxd[i]-1);
	}
	void dp1(int u,int fa,int mid)
	{
		int w=son[u];
		if(w)
		{
			dp[u]=node(1,1),f[w]=f[u]+1,g[w]=g[u]-1,tf[w]=tf[u]+1,tg[w]=tg[u]-1,dp1(w,u,mid),dp[u]+=min(f[w][dis[w]],dp[w]);
			if(b[u])/*,cout<<u<<' '<<w<<' '<<dis[w]<<' '<<f[w][dis[w]].v<<' '<<f[w][dis[w]].c<<' '<<dp[u].v<<' '<<dp[u].c<<"!\n"*/f[u][0]=g[u][0]=inf;
			else 
			{
				if(siz[w])
				{
					node lg=min(f[w][dis[w]],dp[w]);
					f[u][0]=node(mid,0)+min(lg,dis[w]?g[w][1]:inf);
					if(b[w])f[u][1]=f[u][0];
					if(dis[u]>=dis[w])g[u][dis[u]]=lg;
					if(dis[u]>dis[w])g[u][dis[u]-1]=lg;
				}
				else f[u][0]=node(mid,0);
			}
		}
		else dp[u]=node(1,1),b[u]?(f[u][0]=g[u][0]=inf):f[u][0]=node(mid,0);
		for(int i=h[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==fa||v==son[u])continue;
			f[v]=id,id+=2*maxd[v]+1,g[v]=id,id+=maxd[v]+1,tf[v]=id,id+=2*maxd[v]+1,tg[v]=id,id+=maxd[v]+1,dp1(v,u,mid);
			dp[u]+=min(f[v][dis[v]],dp[v]);
			if(b[u]||!siz[v])continue;
//			cout<<u<<' '<<v<<"#\n";
			for(int j=0;j<=min(dis[u],dis[v]+1);j++)
			{
				if(j<dis[v])tf[v][j+1]+=tf[v][j],tg[v][j+1]+=tg[v][j];
				if(j<=dis[v])g[v][j]+=tg[v][j];
				if(j!=dis[u])tf[u][j+1]+=tf[u][j],tg[u][j+1]+=tg[u][j];
				g[u][j]+=tg[u][j];
				if(j&&j<dis[v])f[v][j]=min(f[v][j]+tf[v][j],f[v][j-1]);
				if(j&&j!=dis[u])f[u][j]=min(f[u][j]+tf[u][j],f[u][j-1]);
				tf[u][j]=tg[u][j]=node(0,0);
				node now=min(f[u][dis[u]],g[u][j]),lg=j>=dis[v]?inf:g[v][j+1];
//				cout<<j<<' '<<now.v<<' '<<lg.v<<' '<<min(dp[v],min(f[v][dis[v]],lg)).v<<'\n';
				f[u][j]=min(f[u][j]+min(dp[v],min(f[v][dis[v]],lg)),j?f[v][j-1]+now:inf);
				g[u][j]=min(g[u][j]+(min(dp[v],min(f[v][dis[v]],lg))),lg+now);
				if(j)f[u][j]=min(f[u][j],f[u][j-1]);
			}
			if(dis[u]>dis[v]+1)
			{
				node tag=min(dp[v],f[v][dis[v]]);
				if(dis[u]==dis[v]+2)f[u][dis[u]]=min(f[u][dis[u]]+tag,f[u][dis[u]-1]),tf[u][dis[u]]=node(0,0);
				else f[u][dis[u]]=min(f[u][dis[u]]+tag,f[u][dis[u]-1]),tf[u][dis[v]+2]+=tag;
				tg[u][dis[v]+2]+=tag;
			}
		}
//		cout<<u<<' '<<dp[u].v<<' '<<dp[u].c<<' '<<dis[u]<<"*\n";
//		node sum=node(0,0),now=inf;
//		for(int i=0;i<=dis[u];i++)sum+=tf[u][i],now=min(now,f[u][i]+(i==dis[u]?node(0,0):sum)),cout<<now.v<<' '<<now.c<<'\n';
//		puts("-"),sum=node(0,0),now=inf;
//		for(int i=0;i<=dis[u];i++)sum+=tg[u][i],now=min(now,g[u][i]+sum),cout<<now.v<<' '<<now.c<<'\n';
//		cout<<f[u][dis[u]].v<<' '<<f[u][dis[u]].c<<"*\n";
	}
	bool check(int mid)
	{
		memset(tmp,0,sizeof(tmp)),id=tmp;
		f[1]=id,id+=2*maxd[1]+1,g[1]=id,id+=maxd[1]+1,tf[1]=id,id+=2*maxd[1]+1,tg[1]=id,id+=maxd[1]+1;
		dp1(1,0,mid);
		node now=min(dp[1],f[1][dis[1]]);
		for(int i=0;i<dis[1];i++)tf[1][i+1]+=tf[1][i],tg[1][i+1]+=tg[1][i],f[1][i]+=tf[1][i],g[1][i]+=tg[1][i],now=min(now,f[1][i]+tf[1][i]);
		g[1][dis[1]]+=tg[1][dis[1]];
		return now.c<=m;
	}
	int main() {
//		freopen("22.in","r",stdin);
//		freopen("22.out","w",stdout);
		int x,y;
		n=read(),m=read(),k=read();
		for(int i=1;i<=k;i++)x=read(),b[x]=1,q.push(x);
		for(int i=1;i<n;i++)
		{
			x=read(),y=read();
			addedge(x,y),addedge(y,x);
		}
		dfs1(1,0),bfs();
//		cerr<<maxd[1]<<'\n';
		int l=1,r=n,w=1;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid))w=mid,l=mid+1;
			else r=mid-1;
		}
		check(w);
//		cout<<w<<'\n';
//		check(2);
		ll ans=dp[1].c<=m?(dp[1].v-m+w-1)/w:n;
		for(int i=0;i<=dis[1];i++)if(f[1][i].c<=m)ans=min(ans,(f[1][i].v-m+w-1)/w);
		printf("%lld",ans);
		return 0;
	}
}
int main() {
	return tokido_saya::main();
}

