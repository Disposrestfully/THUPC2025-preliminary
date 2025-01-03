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
int rev[N],fol[N],ord[N];
int a[N],b[N],sta[N],vis[N];
inline void print(){
    for (int i=1;i<=tot;++i){
        int x=b[i];
        if (!dep[x]){
            //printf("%d %d %d\n",x,rev[x],fol[x]);
            if (rev[x]){
                printf("*.");
                ++x;
            }else{
                putchar('.');
                while (fol[x]){
                    putchar('.');
                    ++x;
                }
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
                /*int d=dep[x],r=rk[x];
                if (r==1){
                    printf(".%d-%d",d,r);
                    while (rev[x]){
                        printf("*.");
                        ++x;
                    }
                }else{
                    if (rev[x]){
                        printf(".*");
                        ++x;
                    }
                    printf(".%d-%d",d,r);
                }*/
                printf("*.%d-%d",dep[x],rk[x]);
            }
        }
    }
    puts("");
}
int main(){
    n=read();
    assert(1<=n && n<=1000000);
    for (int i=1;i<=n;++i)
        p[op[i]=read()]=i;
    sort(op+1,op+n+1);
    for (int i=1;i<=n;++i) assert(op[i]==i);
    for (int i=1;i<n;++i){
        if (p[i+1]==p[i]+1) fol[p[i]]=1;
        if (p[i+1]==p[i]-1) rev[p[i]]=1;
    }
    for (int i=1;i<=n;++i)
        if (!fol[p[i-1]]) a[++tot]=p[i];
    for (int i=1;i<=tot;++i) ord[b[i]=a[i]]=i;
    sort(b+1,b+tot+1);
    for (int i=1;i<=tot;++i){
        int id,tmp,mx;
        //printf("%d %d\n",a[i],b[i]);
        if (rev[b[i]]){
            //puts("GO");
            id=1,tmp=top,mx=1;
            while (tmp>1 && ord[sta[tmp]]+1==ord[sta[tmp-1]]){
                //printf("[%d %d]\n",sta[tmp],id);
                rk[sta[tmp]]=id++;
                mx=max(mx,dep[sta[tmp]]);
                --tmp;
            }
            rk[sta[tmp]]=id++;
            mx=max(mx,dep[sta[tmp]]);
            if (tmp==top) mx=0;
            for (int i=tmp;i<=top;++i)
                dep[sta[i]]=mx,vis[sta[i]]=1;
            for (int i=1;i<tmp;++i)
                dep[sta[i]]=max(dep[sta[i]],mx+1);
            top=tmp-1;
        }
        while (now<tot && vis[a[now+1]]) ++now;
        sta[++top]=b[i];
        if (sta[top]==a[now+1]){
            //printf("[%d %d]\n",top,now);
            id=1,tmp=top,mx=1;
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
        while (now<tot && vis[a[now+1]]) ++now;
    }
    if (top || now<tot) return puts("-1"),0;
    print();
    return 0;
}