#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5;
const int B=505;
const int P=22050;
const int Mod=998244353;
#define b(x) ((x)/500+1)
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
int gcd(int x,int y){
    if (!y) return x;
    return gcd(y,x%y);
}
int pid[N],prime[N],p[N],ptot;
inline void init(){
    p[1]=1;
    for (int i=2;i<=250000;++i){
        if (!p[i]) prime[pid[i]=++ptot]=i;
        for (int j=1;j<=ptot && i*prime[j]<=250000;++j){
            p[i*prime[j]]=1;
            if (i%prime[j]==0) break;
        }
    }
    //printf("%d\n",ptot);
}
int n,q;
int L[B],R[B],tag[B];
int a[N];
int g[N],sum[N],to[N];
bitset<P>pm[B];
inline void build(int x){
    for (int i=R[x];i>=L[x];--i){
        if (i+g[i]>R[x]){
            to[i]=i+g[i];
            sum[i]=a[i];
        }else{
            to[i]=to[i+g[i]];
            sum[i]=a[i]+sum[i+g[i]];
            if (sum[i]>=Mod) sum[i]-=Mod;
        }
    }
    pm[x].reset();
    for (int i=L[x];i<=R[x];++i){
        int tmp=i/g[i];
        for (int j=2;j*j<=tmp;++j)
            if (tmp%j==0){
                while (tmp%j==0) tmp/=j;
                pm[x].set(pid[j]);
            }
        if (tmp!=1) pm[x].set(pid[tmp]);
    }
}
inline void upd(int x,int c){
    int flag=0,tmp=c;
    for (int i=2;i*i<=tmp;++i){
        if (tmp%i==0){
            if (pm[x].test(pid[i])){
                flag=1;
                break;
            }
            while (tmp%i==0) tmp/=i;
        }
    }
    if (tmp>1 && pm[x].test(pid[tmp])) flag=1;
    if (!flag){
        tag[x]=1ll*tag[x]*c%Mod;
        return;
    }
    for (int i=L[x];i<=R[x];++i){
        a[i]=1ll*a[i]*c%Mod;
        g[i]*=gcd(c,i/g[i]);
    }
    build(x);
}
inline int query(int x){
    int ans=0;
    for (int i=x;i<=n;i=to[i]){
        //if (i!=to[i]) printf("%d %d\n",i,to[i]);
        ans+=1ll*tag[b(i)]*sum[i]%Mod;
        if (ans>=Mod) ans-=Mod;
    }
    return ans;
}
int main(){
    init();
    n=read(),q=read();
    for (int i=1;i<=n;++i) R[b(i)]=i;
    for (int i=n;i>=1;--i) L[b(i)]=i;
    for (int i=1;i<=n;++i){
        a[i]=read();
        g[i]=gcd(i,a[i]);
    }
    for (int i=1;i<=b(n);++i)
        tag[i]=1,build(i);
    while (q--){
        int opt=read();
        if (opt&1){
            int l=read(),r=read(),c=read();
            int bl=b(l),br=b(r);
            if (bl!=br){
                for (int i=bl+1;i<br;++i)
                    upd(i,c);
                for (int i=l;i<=R[bl];++i){
                    a[i]=1ll*a[i]*c%Mod;
                    g[i]*=gcd(c,i/g[i]);
                }
                for (int i=L[br];i<=r;++i){
                    a[i]=1ll*a[i]*c%Mod;
                    g[i]*=gcd(c,i/g[i]);
                }
                build(bl),build(br);
            }else{
                for (int i=l;i<=r;++i){
                    a[i]=1ll*a[i]*c%Mod;
                    g[i]*=gcd(c,i/g[i]);
                }
                build(bl);
            }
        }else{
            int x=read();
            printf("%d\n",query(x));
        }
    }
    return 0;
}