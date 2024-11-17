#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
const int M=998244353;
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
int t,n,m,a[100002],b[100002],fac[100002],inv[100002];
inline int C(re int x,re int y){
	if(x<y||y<0)return 0;
	return 1ll*fac[x]*inv[y]%M*inv[x-y]%M;
}
int main(){
	t=read(),n=1e5;
	for(re int i=fac[0]=1;i<=n;++i)fac[i]=1ll*fac[i-1]*i%M;
	inv[n]=ksm(fac[n],M-2);
	for(re int i=n-1;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%M;
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read(),b[i]=read();
		re bool ia=1;
		for(re int i=1;i<=n;++i)
			if(a[i]!=-1&&a[i]+b[i]!=i)
				ia=0;
		for(re int i=20;i<n;++i)
			if(abs(a[i]-b[i])>=2)
				ia=0;
		if(n>20&&n%2==1)ia=0;
		if(n<=20&&a[n]!=-1&&max(a[n],b[n])!=11)ia=0;
		if(n>20&&a[n]!=-1&&abs(a[n]-b[n])!=2)ia=0;
		if(!ia){
			puts("0");
			continue;
		}
		for(re int i=20;i<n;++i)a[i]=i>>1,b[i]=i-a[i];
		if(n<=20)a[n]=11,b[n]=n-11;
		else a[n]=n/2+1,b[n]=n/2-1;
		re int lst=0,ans=1;
		for(re int i=1;i<=n;++i)if(a[i]!=-1){
			re int s=0;
			add(s,C(i-lst,a[i]-a[lst]));
			if(a[i]^b[i])add(s,C(i-lst,b[i]-a[lst]));
			ans=1ll*ans*s%M,lst=i;
		}
		printf("%d\n",ans);
	}
}
