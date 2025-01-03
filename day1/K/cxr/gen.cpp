#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int n,top,m,tot,now;
int p[N],a[N],b[N];
int sta[N],len[N];
int main(){
    srand(time(0));
    n=1000000;
    for (int i=1;i<=n;++i)
        p[i]=i;
    now=1;
    while (now<=n){
        //printf("%d %d\n",now,n);
        len[now]=rand()%min(10,n-now+1)+1;
        if (rand()%5==0 && now+len[now]<=n){
            int l=len[now];
            for (int i=now;i<=now+l-1;++i)
                len[i]=1;
            for (int i=now+l-1;i>=now;--i)
                b[++m]=i;
            now+=l;
            continue;
        }
        sta[++top]=now;
        now=now+len[now];
        int tmp=rand()%min(top+1,5);
        if (top<15) tmp=0;
        else tmp=rand()%4+2;
        if (now>n) tmp=top;
        for (int i=1;i<=tmp;++i)
            b[++m]=sta[top--];
    }
    for (int i=1;i<=m;++i)
        for (int j=0;j<len[b[i]];++j)
            a[++tot]=b[i]+j;
    for (int i=1;i<=n;++i) p[a[i]]=i;
    printf("%d\n",n);
    for (int i=1;i<=n;++i)
        printf("%d%c",p[i],i==n?'\n':' ');
    return 0;
}