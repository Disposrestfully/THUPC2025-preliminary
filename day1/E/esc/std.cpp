#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
struct it{
	long long l,r;
	long long sum,off;
	it(){}
	it(int x,int c): l(x-c/2),r(x+(c+1)/2),sum(1ll*x*c),off(sum-cnt()*(cnt()-1)/2){}
	long long cnt() const{
		return (long long)(r-l);
	}
	it& operator+=(const it &rhs){
		long long ncnt=cnt()+rhs.cnt();
		sum+=rhs.sum;
		off=sum-ncnt*(ncnt-1)/2;
		if(off>=0){
			l=off/ncnt;
		}
		else{
			l=(off-ncnt+1)/ncnt;
		}
		r=l+ncnt;
		return *this;
	}
}st[2222222];
int tst;
int main(){
	int m=io::F();
	for(int i=1;i<=m;++i){
		int x=io::F(),c=io::F();
		st[++tst]=it(x,c);
		while(tst>1&&st[tst-1].r>=st[tst].l){
			st[tst-1]+=st[tst];
			--tst;
		}
	}
	int q=io::F();
	long long now=1,sum=0;
	for(int i=1;i<=q;++i){
		long long k=io::G();
		while(k>sum+st[now].cnt()){
			sum+=st[now].cnt();
			++now;
		}
		long long d=k-sum;
		long long res=(st[now].off%st[now].cnt()+st[now].cnt())%st[now].cnt();
		long long ans=st[now].l+d-1+(d+res>st[now].cnt());
		printf("%lld\n",ans);
	}
	return 0;
}