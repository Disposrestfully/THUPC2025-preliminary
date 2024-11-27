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
	__int128_t sum,off;
	it(){}
	it(int x,int c): l(x-c/2),r(x+(c+1)/2),sum(1ll*x*c),off(sum-cnt()*(cnt()-1)/2){}
	__int128_t cnt() const{
		return (long long)(r-l);
	}
	it& operator+=(const it &rhs){
		__int128_t ncnt=cnt()+rhs.cnt();
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
    long long sumc=0;
	for(int i=1;i<=m;++i){
		int x=io::F(),c=io::F();
        sumc+=c;
		st[++tst]=it(x,c);
		while(tst>1&&st[tst-1].r>=st[tst].l){
			st[tst-1]+=st[tst];
			--tst;
		}
	}
	fprintf(stderr,"%lld\n",sumc);
	return 0;
}