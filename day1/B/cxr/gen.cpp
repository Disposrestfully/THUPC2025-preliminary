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
int n,m,ans;
int a[N][N],b[N][N];
int main(){
    srand(time(0));
    //n=rand()%20+2;
    //n=rand()%100+1,m=rand()%100+2;
    n=500,m=100;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            a[i][j]=b[i][j]=0;
    for (int i=1;i<=50;++i){
        int x=rand()%n+1,y=rand()%m+1;
        a[x][y]=b[x][y]=1;
    }
    int lx=rand()%n+1,rx=rand()%n+1;
    int ly=rand()%m+1,ry=rand()%m+1;
    if (lx>rx) swap(lx,rx);
    if (ly>ry) swap(ly,ry);
    //while (rx-lx+1>10){
    //    lx=rand()%n+1,rx=rand()%n+1;
    //    if (lx>rx) swap(lx,rx);
    //}
    while (ly==1 || ry-ly+1>10){
        ly=rand()%m+1,ry=rand()%m+1;
        if (ly>ry) swap(ly,ry);
    }
    //for (int i=lx;i<=rx;++i)   
    //    for (int j=ly;j<=ry;++j)
    //        b[i][j]=rand()&1;
    int d=rand()%(ly-1)+1;
    for (int i=lx;i<=rx;++i)   
        for (int j=ly;j<=ry;++j)
            b[i][j-d]=a[i][j];
    
    printf("%d %d\n",n,m);
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j)
            printf("%d",a[i][j]);
        puts("");
    }
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j)
            printf("%d",b[i][j]);
        puts("");
    }
    //printf("%d %d %d %d %d %d\n",(rx-lx+1)*(ry-ly+1),lx,rx,ly,ry,d);
    return 0;
}