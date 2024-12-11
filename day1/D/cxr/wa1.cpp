#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int inf=1e9;
const double eps=1e-9;
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
int n,m,ans,sum;
int a[N],lg[N],cnt[N],p[N];
inline bool cmp(int x,int y){
    double lgx=log2((double)a[x]);
    double lgy=log2((double)a[y]);
    lgx-=(int)lgx,lgy-=(int)lgy;
    if (fabs(lgx-lgy)<eps){
        //if ((cnt[x]==1)^(cnt[y]==1))
        //    return cnt[x]>cnt[y];
        if (a[x]!=a[y])
            return a[x]<a[y];
        return x>y;
    }
    return lgx<lgy;
}
inline bool check(int x){
    int tmp=m;
    for (int i=1;i<=n;++i){
        if (x>lg[i]) continue;
        tmp-=lg[i]-x+1;
        if (tmp<=0) return 1;
    }
    return 0;
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;++i){
		a[i]=read();
		while ((1<<lg[i])<=a[i])
            ++lg[i];
        --lg[i];
	}
    int l=-m,r=40;
    while (l<=r){
        int mid=(l+r)/2;
        if (check(mid))
            l=mid+1,ans=mid;
        else r=mid-1;
    }
    for (int i=1;i<=n;++i){
        if (ans>lg[i]) continue;
        sum+=(cnt[i]=lg[i]-ans+1);
        //printf("%d ",lg[i]);
    }
    //printf("%d %d\n",ans,sum);
    for (int i=1;i<=n;++i) p[i]=i;
    sort(p+1,p+n+1,cmp);
    for (int i=1;i<=n && sum>m;++i){
        if (ans>lg[p[i]]) continue;
        --cnt[p[i]],--sum;
    }
    for (int i=1;i<=n;++i)
        printf("%d ",cnt[i]);
    puts("");
    return 0;
}