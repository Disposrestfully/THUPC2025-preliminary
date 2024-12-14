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
int main(){
    srand(time(0));
    //n=rand()%20+2;
    //n=20;
    n=500;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            a[i][j]=b[i][j]=rand()&1;
    int lx=rand()%n+1,rx=rand()%n+1;
    int ly=rand()%n+1,ry=rand()%n+1;
    if (lx>rx) swap(lx,rx);
    if (ly>ry) swap(ly,ry);
    while (ly==1){
        ly=rand()%n+1,ry=rand()%n+1;
        if (ly>ry) swap(ly,ry);
    }
    for (int i=lx;i<=rx;++i)   
        for (int j=ly;j<=ry;++j)
            b[i][j]=rand()&1;
    int d=rand()%(ly-1)+1;
    for (int i=lx;i<=rx;++i)   
        for (int j=ly;j<=ry;++j)
            b[i][j-d]=a[i][j];
    
    printf("%d\n",n);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            printf("%d%c",a[i][j],j==n?'\n':' ');
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            printf("%d%c",b[i][j],j==n?'\n':' ');
    //printf("%d %d %d %d %d %d\n",(rx-lx+1)*(ry-ly+1),lx,rx,ly,ry,d);
    return 0;
}