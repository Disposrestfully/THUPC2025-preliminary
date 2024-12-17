#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
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
	int next,to;
}a[N<<1];
int head[N],cur[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int n,m;
int c[N],p[N],dp[N][3];
void dfs(int x,int fa){
    dp[x][0]=0;
    dp[x][2]=(p[x]==2)?inf:1;
    dp[x][1]=inf;
    for (int i=head[x];i;i=a[i].next){
        int y=a[i].to;
        if (y==fa) continue;
        dfs(y,x);
        if (p[x]!=2) dp[x][2]+=min(dp[y][0],min(dp[y][1],dp[y][2]));
        if (p[y]==1) dp[x][1]=min(dp[x][1]+min(dp[y][1],dp[y][2]),dp[x][0]+dp[y][2]);
        else dp[x][1]=min(dp[x][1]+min(dp[y][0],min(dp[y][1],dp[y][2])),dp[x][0]+dp[y][2]);
        if (p[y]==1) dp[x][0]+=dp[y][1];
        else dp[x][0]+=min(dp[y][0],dp[y][1]);
    }
    dp[x][1]=min(dp[x][1],dp[x][2]);
    if (p[x]==2) dp[x][2]=inf;
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=m;++i)
        p[c[i]=read()]=2;
    for (int i=1;i<n;++i){
        int u=read(),v=read();
        add(u,v),add(v,u);
        if (p[u]==2 && !p[v]) p[v]=1;
        if (p[v]==2 && !p[u]) p[u]=1;
    }
    dfs(1,0);
    int ans=min(dp[1][1],dp[1][2]);
    if (p[1]!=1) ans=min(ans,dp[1][0]);
    printf("%d\n",ans);
    return 0;
}