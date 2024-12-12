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
int a[N][N],b[N][N],c[N][N];
inline void move(int lx,int rx,int ly,int ry,int d){
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j){
            if (i>=lx && i<=rx && j>=ly && j<=ry) c[i][j]=-1;
            else c[i][j]=a[i][j];
        }
    for (int i=lx;i<=rx;++i)
        for (int j=ly;j<=ry;++j)
            c[i][j-d]=a[i][j];
}
inline bool check(){
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            if (~c[i][j] && b[i][j]!=c[i][j])
                return 0;
    return 1;
}
inline void solve(int d){
    for (int lx=1;lx<=n;++lx){
        for (int rx=lx;rx<=n;++rx){
            for (int ly=d+1;ly<=n;++ly){
                for (int ry=ly;ry<=n;++ry){
                    int now=(rx-lx+1)*(ry-ly+1);
                    if (now<ans) continue;
                    move(lx,rx,ly,ry,d);
                    if (check()){
                        ans=now;
                        //printf("%d %d %d %d %d\n",lx,rx,ly,ry,d);
                    }
                }
            }
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