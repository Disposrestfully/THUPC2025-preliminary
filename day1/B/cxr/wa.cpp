#include<bits/stdc++.h>
using namespace std;
const int N=1005;
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
int n,ans;
int a[N][N],b[N][N];
int c[N][N],s[N][N],p[N][N];
int L[N],R[N];
stack<int>sta;
inline void debug(){
    for (int i=1;i<=n;++i){
        for (int j=1;j<=n;++j)
            printf("%d ",a[i][j]);
        puts("");
    }
}
inline int calc(int lx,int ly,int rx,int ry){
    if (lx>rx || ly>ry) return 0;
    return s[rx][ry]+s[lx-1][ly-1]-s[lx-1][ry]-s[rx][ly-1];
}
inline void solve(int d){
    int lx=n+1,rx=0,ly=n+1,ry=0,sum=0;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j){
            p[i][j]=0;
            if (a[i][j]==b[i][j]) p[i][j]|=2;
            if (j+d<=n && a[i][j+d]==b[i][j]) p[i][j]|=1,c[i][j]=c[i-1][j]+1;
            else c[i][j]=0;
            if (!p[i][j]){
                lx=min(lx,i),rx=max(rx,i);
                if (j-d<=0) return;
                ly=min(ly,j-d),ry=max(ry,j-d);
                if (ry-ly+1>d) return;
            }
            s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+(p[i][j]==1);
            sum+=(p[i][j]==1);
        }
    //printf("%d %d %d %d\n",lx,rx,ly,ry);
    for (int i=1;i<=n;++i){
        if (i<rx) continue;
        sta=stack<int>();
        for (int j=1;j<=n;++j){
            while (!sta.empty() && c[i][sta.top()]>=c[i][j]) sta.pop();
            if (sta.empty()) L[j]=1;
            else L[j]=sta.top()+1;
            sta.push(j);
        }
        sta=stack<int>();
        for (int j=n;j>=1;--j){
            while (!sta.empty() && c[i][sta.top()]>=c[i][j]) sta.pop();
            if (sta.empty()) R[j]=n;
            else R[j]=sta.top()-1;
            sta.push(j);
        }
        for (int j=1;j<=n;++j){
            //printf("%d %d %d %d\n",i,j,L[j],R[j]);
            if (i-c[i][j]+1>lx) continue;
            int nowl=L[j],nowr=min(n-d,R[j]);
            if (nowl>ly || nowr<ry) continue; 
            int resl=max(nowr+1,nowl+d),resr=nowr+d;
            //if (calc(i-c[i][j]+1,resl,i,resr)+calc(i-c[i][j]+1,nowl,i,nowr)!=sum) continue;   
            ans=max(ans,(nowr-nowl+1)*c[i][j]);
        }
    }
}
int main(){
    n=read();
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            a[i][j]=read();
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            b[i][j]=read();
    for (int i=1;i<=n;++i)
        solve(i);
    printf("%d\n",ans);
    return 0;
}