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
int n,tot,now,top;
int op[N],p[N],dep[N],rk[N];
int rev[N],fol[N];
int a[N],b[N],sta[N];
inline void print(){
    for (int i=1;i<=tot;++i){
        int x=b[i];
        if (!dep[x]){
            //printf("%d %d %d\n",x,rev[x],fol[x]);
            putchar('.');
            while (fol[x]){
                putchar('.');
                ++x;
            }
            while (rev[x]){
                printf("*.");
                ++x;
            }
        }else if (rk[x]==1 && fol[x]){
            int d=dep[x];
            while (fol[x]){
                putchar('.');
                ++x;
            }
            printf(".%d-1",d);
        }else{
            if (!rev[x]){
                printf(".%d-%d",dep[x],rk[x]);
                while (fol[x]){
                    printf("#.");
                    ++x;
                }
            }else{
                int d=dep[x],r=rk[x];
                if (r==1){
                    printf(".%d-%d",d,r);
                    while (rev[x]){
                        printf("*.");
                        ++x;
                    }
                }else{
                    while (rev[x]){
                        printf(".*");
                        ++x;
                    }
                    printf(".%d-%d",d,r);
                }
            }
        }
    }
    puts("");
}
int main(){
    n=read();
    for (int i=1;i<=n;++i)
        p[op[i]=read()]=i;
    sort(op+1,op+n+1);
    for (int i=1;i<=n;++i) assert(op[i]==i);
    for (int i=1;i<n;++i){
        if (p[i+1]==p[i]+1) fol[p[i]]=1;
        if (p[i+1]==p[i]-1) rev[p[i]]=1;
    }
    for (int i=1;i<=n;++i)
        if (!fol[p[i-1]] && !rev[p[i-1]]) a[++tot]=p[i];
    for (int i=1;i<=tot;++i) b[i]=a[i];
    sort(b+1,b+tot+1);
    for (int i=1;i<=tot;++i){
        //printf("%d %d\n",b[i],a[i]);
        sta[++top]=b[i];
        if (sta[top]==a[now+1]){
            int id=1,tmp=top,mx=1;
            while (tmp && sta[tmp]==a[now+1]){
                ++now;
                rk[sta[tmp]]=id++;
                mx=max(mx,dep[sta[tmp]]);
                --tmp;
            }
            if (tmp+1==top) mx=0;
            for (int i=tmp+1;i<=top;++i)
                dep[sta[i]]=mx;
            for (int i=1;i<=tmp;++i)
                dep[sta[i]]=max(dep[sta[i]],mx+1);
            top=tmp;
        }
    }
    if (top || now<tot) return puts("-1"),0;
    print();
    return 0;
}