#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int inf=1e9;
typedef long long ll;
inline int read(){
    int x=0,w=1;
    char ch=0;
    while (ch<'0' || ch>'9'){
        ch=getchar();
        if (ch=='-') w=-1;
    }
    while (ch<='9' && ch>='0'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*w;
}
struct edge{
	int next,to,w;
}a[N<<1];
int head[N],cur[N],cnt;
inline void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
inline void addedge(int u,int v){
	add(u,v,1),add(v,u,0);
}
int n,m,c,tot;
int s[N],t[N],p[N];
queue<int>q;
int l[N],vis[N],tim;
inline bool bfs(){
	q=queue<int>();
	l[1]=1,vis[1]=++tim;
	q.push(1);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		if (x==n) return 1;
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (vis[y]!=tim && a[i].w){
				vis[y]=tim;
				l[y]=l[x]+1;
				q.push(y);
			}
		}
	}
	return (vis[n]==tim);
}
int dfs(int x,int flow){
	if (x==n || !flow) return flow;
	int res=0;
	for (int &i=cur[x];i;i=a[i].next){
		int y=a[i].to;
		if (vis[y]==tim && l[y]==l[x]+1 && a[i].w){
			int val=dfs(y,min(flow-res,a[i].w));
			if (val) res+=val,a[i].w-=val,a[i^1].w+=val;
			else l[y]=-1;
			if (flow==res) return res;
		}
	} 	
	return res;
}
inline void solve(){
	int ans=0;
	while (bfs()){
		for (int i=1;i<=tot;++i) cur[i]=head[i];
		ans+=dfs(1,inf);
	}
	printf("%d\n",ans);
}
int main(){
    cnt=1;
    n=tot=read(),m=read(),c=read();
    for (int i=1;i<=c;++i){
        p[i]=read();
		assert(1<=p[i] && p[i]<=n);
        s[i]=++tot;
        t[i]=++tot;
		addedge(s[i],t[i]);
        addedge(p[i],s[i]);
		addedge(t[i],p[i]);
    }
    for (int i=1;i<=m;++i){
        int u=read(),v=read(),r=read();
		assert(1<=u && u<=n);
		assert(1<=v && v<=n);
		assert(1<=r && r<=c);
		assert(p[r]==u || p[r]==v);
        if (p[r]==u) addedge(t[r],v);
        else addedge(u,s[r]);
    }
    solve();
    return 0;
}