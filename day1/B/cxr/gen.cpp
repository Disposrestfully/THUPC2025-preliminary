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
int n,m,ans,k;
int a[N][N],b[N][N];
int p[N];
int main(){
    srand(time(0));
    n=500,m=500;
    
    for (int i=1;i<=n;++i){
        k=rand()%100+1;
        for (int i=0;i<k;++i)
            p[i]=rand()&1;
        for (int j=1;j<=m;++j)
            a[i][j]=b[i][j]=p[j%k];
    }
    
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