#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;
int n,m,k,x,y,vis[3005];int tot,fir[3005],nxt[6005],to[6005];
int md[3005],siz[3005],dis[3005],rd[3005];queue<int> q;
struct nd{ll v;int c;} f[3005][3005],g[3005][3005],res[3005];nd inf={1ll<<60,1<<30};
bool operator <(const nd &x,const nd &y)
{
	if(x.v!=y.v) return x.v<y.v;
	return x.c<y.c;
}
nd operator +(const nd &x,const nd &y){return {x.v+y.v,x.c+y.c};}
nd& operator +=(nd &x,const nd &y){return x=x+y;}
void ins(int x,int y)
{
	nxt[++tot]=fir[x];
	fir[x]=tot;
	to[tot]=y;
}
void dfs1(int now,int fa)
{
	siz[now]=vis[now];md[now]=0;
	for(int i=fir[now];i;i=nxt[i])
		if(to[i]!=fa)
		{
			dfs1(to[i],now);
			siz[now]+=siz[to[i]];
			md[now]=max(md[now],md[to[i]]+1);
		}
}
void dfs2(int now,int fa,ll cv)
{
	res[now]={n,1};
	if(!vis[now]){for(int i=0;i<=rd[now];i++) f[now][i]={cv,0};}
	else f[now][0]=g[now][0]=inf;
	for(int i=fir[now];i;i=nxt[i])
		if(to[i]!=fa)
		{
			int v=to[i];dfs2(v,now,cv);
			nd zf=min(res[v],f[v][rd[v]]);res[now]+=zf;
			if(vis[now]||!siz[v]) continue;
			for(int j=0;j<=min(rd[now],rd[v]);j++)
			{
				nd cur=min(f[now][rd[now]],g[now][j]);
				nd ex=min(zf,j<rd[v]?g[v][j+1]:inf);
				f[now][j]+=ex;g[now][j]+=ex;
				if(j) f[now][j]=min(f[now][j],f[v][j-1]+cur);
				if(j<rd[v]) g[now][j]=min(g[now][j],g[v][j+1]+cur);
			}
			for(int j=1;j<=min(rd[now],rd[v]);j++) f[now][j]=min(f[now][j],f[now][j-1]);
			for(int j=rd[v]+1;j<=rd[now];j++)
			{
				if(j==rd[v]+1)
				{
					nd c1=f[now][rd[v]],c2=f[v][rd[v]]+min(f[now][rd[now]],g[now][j]);
					f[now][j]=min(f[now][j]+res[v],min(c1,c2));
				}
				else f[now][j]+=res[v];
				g[now][j]+=res[v];
			}
			for(int j=min(rd[now]-1,rd[v]);j>=0;j--) g[now][j]=min(g[now][j],g[now][j+1]);
		}
}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++) scanf("%d",&x),vis[x]=1,q.push(x);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	dfs1(1,0);
	while(!q.empty())
	{
		int now=q.front();q.pop();
		for(int i=fir[now];i;i=nxt[i])
			if(!vis[to[i]]&&!dis[to[i]])
			{
				dis[to[i]]=dis[now]+1;
				q.push(to[i]);
			}
	}
	for(int i=1;i<=n;i++) rd[i]=min(dis[i],md[i]);
	ll l=1,r=1ll*n*n,fn=0;
	while(l<=r)
	{
		ll mid=(l+r)/2;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=rd[i];j++) f[i][j]=g[i][j]={0,0};
		dfs2(1,0,mid);
		nd mn=res[1];for(int i=0;i<=rd[1];i++) mn=min(mn,f[1][i]);
		if(mn.c<=m) fn=mid,l=mid+1;
		else r=mid-1;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=rd[i];j++) f[i][j]=g[i][j]={0,0};
	dfs2(1,0,fn);
	int ans=(res[1].c<=m?(res[1].v-1ll*m*n+fn-1)/fn:n-k);
	for(int i=0;i<=rd[1];i++)
		if(f[1][i].c<=m) ans=min(1ll*ans,(f[1][i].v-1ll*m*n+fn-1)/fn);
	printf("%d",ans);
	return 0;
}
