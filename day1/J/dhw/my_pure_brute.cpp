#include<iostream>
#include<cstdio>
using namespace std;
int n,m,k,x,y,bl;int tot,fir[21],nxt[41],to[41],vis[21],nv[21];
void ins(int x,int y)
{
	nxt[++tot]=fir[x];
	fir[x]=tot;
	to[tot]=y;
}
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("data.ans","w",stdout);
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++) cin>>x,bl|=(1<<(x-1));
	for(int i=1;i<n;i++)
	{
		cin>>x>>y;
		ins(x,y);ins(y,x);
	}
	for(int gs=0;gs<=n-k;gs++)
		for(int i=0;i<(1<<n);i++)
			if(__builtin_popcount(i)==gs&&((bl&i)==0))
			{
				int dq=k+gs,sl=k;
				for(int j=1;j<=n;j++)
					if(bl&(1<<(j-1))) vis[j]=2;
					else if(i&(1<<(j-1))) vis[j]=1;
					else vis[j]=0;
				for(int ls=1;ls<=n-(k+gs);ls++)
				{
					for(int j=1;j<=n;j++)
						if(!vis[j])
						{
							int fl=0;
							for(int l=fir[j];l;l=nxt[l])
								if(vis[to[l]]==2){fl=2;break;}
							for(int l=fir[j];l;l=nxt[l])
								if(vis[to[l]]==1){fl=1;break;}
							if(fl==2) nv[j]=2,sl++,dq++;
							else if(fl==1) nv[j]=1,dq++;
						}
					for(int j=1;j<=n;j++)
						if(nv[j]&&!vis[j]) vis[j]=nv[j],nv[j]=0;
					if(dq==n) break;
				}
				if(sl<=m)
				{
					cout<<gs;
					return 0;
				}
			}
	return 0;
}
