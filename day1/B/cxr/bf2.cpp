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
int n,m;
char str[N];
int a[N][N],b[N][N],c[N][N];
int len[N][N],L[N],R[N];
stack<int>sta;
inline bool check(){
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            if (~c[i][j] && b[i][j]!=c[i][j])
                return 0;
    return 1;
}
inline bool move(int lx,int rx,int ly,int ry,int d){
    if (ly-d<=0) return 0;
    if (ry<ly || rx<lx) return 0;
    for (int i=lx;i<=rx;++i)
        for (int j=ly;j<=ry;++j)
            c[i][j]=-1;
    for (int i=lx;i<=rx;++i)
        for (int j=ly;j<=ry;++j)
            c[i][j-d]=a[i][j];
    bool res=check();
    for (int i=lx;i<=rx;++i)
        for (int j=ly;j<=ry;++j)
            c[i][j]=a[i][j],c[i][j-d]=a[i][j-d];
    return res;
}
inline int solve(int d){
    int ans=-1;
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            if (j>d && b[i][j-d]==a[i][j])
                len[i][j]=len[i-1][j]+1;
            else len[i][j]=0;
        }
    }
    for (int i=1;i<=n;++i){
        sta=stack<int>();
        for (int j=1;j<=m;++j){
            while (!sta.empty() && len[i][sta.top()]>=len[i][j]) sta.pop();
            if (!sta.empty()) L[j]=sta.top()+1;
            else L[j]=1;
            sta.push(j);
        }
        sta=stack<int>();
        for (int j=m;j>=1;--j){
            while (!sta.empty() && len[i][sta.top()]>=len[i][j]) sta.pop();
            if (!sta.empty()) R[j]=sta.top()-1;
            else R[j]=m;
            sta.push(j);
        }
        for (int j=1;j<=m;++j){
            //printf("%d %d %d %d %d\n",i,j,len[i][j],L[j],R[j]);
            if (!len[i][j]) continue;
            int up=i-len[i][j]+1;
            int nowl=max(L[j],d+1),nowr=R[j];
            if (nowl>nowr) continue;
            int S=(nowr-nowl+1)*len[i][j];
            if (!S || S<ans) continue;
            if (move(up,i,nowl,nowr,d)){
                printf("%d %d %d %d\n",up,i,nowl,nowr);
                ans=S;
            }
        }
    }
    return ans;
}
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;++i){
        scanf("%s",str+1);
        for (int j=1;j<=m;++j)
            a[i][j]=c[i][j]=str[j]-'0';
    }
    for (int i=1;i<=n;++i){
        scanf("%s",str+1);
        for (int j=1;j<=m;++j)
            b[i][j]=str[j]-'0';
    }
    printf("%d\n",solve(40));
    //for (int i=1;i<m;++i)
    //    printf("%d%c",solve(i),i==m-1?'\n':' ');
    return 0;
}