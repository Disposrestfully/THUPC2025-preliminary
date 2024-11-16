#include<bits/stdc++.h>
#define re register
using namespace std;
mt19937 Rnd(1145141);
int ID,a[100002];
void Genrnd(int T,int LN,int RN,int V){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		re int n=Rnd()%(RN-LN+1)+LN;
		printf("%d %d\n",n,Rnd()%n+1);
		for(re int i=1;i<n;++i)printf("%d ",Rnd()%(V+1));
		printf("%d\n",Rnd()%(V+1));
	} 
}
void Genrnd1(int T,int LN,int RN,int V){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		re int n=Rnd()%(RN-LN+1)+LN,x=Rnd()%n+1;
		if(Rnd()%3==0)x=Rnd()%2?1:n;
		printf("%d %d\n",n,x);
		for(re int i=1;i<=n;++i)a[i]=Rnd()%(V+1);
		for(re int i=max(1,x-1);i<=min(n,x+1);++i)
			for(re int j=1;j<=n;++j)
				if(abs(j-x)>1&&a[j]<a[i])
					swap(a[i],a[j]);
		for(re int i=1;i<n;++i)printf("%d ",a[i]);
		printf("%d\n",a[n]);
	} 
}
int main(){
	ID=1;
	Genrnd(100000,1,5,1);
	Genrnd(100000,1,5,1000000000);
	Genrnd(5000,96,100,1);
	Genrnd(5000,96,100,1000000000);
	Genrnd(5,99996,100000,1);
	Genrnd(5,99996,100000,1000000000);
	Genrnd1(5000,96,100,1000000000);
	Genrnd1(500,996,1000,1000000000);
	Genrnd1(5,99996,100000,1000000000);
}
