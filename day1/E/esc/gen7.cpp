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
void file(){
	char ss[111];
	int ta=1;
	while(1){
		sprintf(ss,"%d.in",ta);
		FILE* fp=fopen(ss,"r");
		if(!fp){
			break;
		}
		else fclose(fp);
		++ta;
	}
	freopen(ss,"w",stdout);
}
std::random_device device;
std::mt19937_64 gen(device());
long long R(long long l, long long r){
	return std::uniform_int_distribution<long long>(l,r)(gen);
}
long long P(int len, bool zero=false, bool neg=false){
	int x=R(1,len);
	if(zero&&x==1)return R(neg?-1:0,1);
	return (neg&&R(0,1)?-1:1)*R(1ll<<x-1,(1ll<<x)-1);
}
double expe(int len){
	double ans=0;
	for(int i=1;i<=len;++i){
		ans+=((1ll<<i-1)+(1ll<<i)-1)/2.0;
	}
	return ans/len;
}
int main(){
	for(int i=1;i<=20;++i){
		printf("%2d %lf\n",i,expe(i));
	}
	file();
	int m=2000000;
	printf("%d\n",m);
	int now=1;
	long long sum=0;
	for(int i=1;i<=m;++i){
		long long cnt=P(9);
		printf("%d %lld\n",now,cnt);
		assert(now<=1000000000);
		now+=P(9);
		sum+=cnt;
	}
	int q=2000000;
	printf("%d\n",q);
	std::set<long long> qu;
	for(int i=1;i<=q;++i){
		long long k;
		do{
			k=R(1,sum);
		}
		while(qu.count(k));
		qu.insert(k);
	}
	for(long long k: qu){
		printf("%lld\n",k);
	}
	return 0;
}