#include<bits/stdc++.h>
#define re register
using namespace std;
mt19937 Rnd(1145141);
int ID,a[100002],b[100002];
void Genrnd(int T,int LN,int RN,int V1,int V2){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		re int n=Rnd()%(RN-LN+1)+LN;
		for(re int i=1;i<=n;++i){
			if(Rnd()%100<V1){
				if(Rnd()%100<V2)a[i]=Rnd()%(i+2),b[i]=Rnd()%(i+2);
				else a[i]=Rnd()%(i+1),b[i]=i-a[i];
			}
			else a[i]=b[i]=-1;
		}
		printf("%d\n",n);
		for(re int i=1;i<=n;++i)printf("%d %d\n",a[i],b[i]);
	} 
}
inline void GenLong(int T,int LN,int RN,int V){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		re int s1=0,s2=0,n=Rnd()%(RN-LN+1)+LN;
		for(re int i=1;i<=n;++i){
			if(max(s1,s2)<10){
				if(Rnd()%2==1)++s1;else ++s2;
			}
			else if(i!=n){
				if(s1<s2)++s1;
				else ++s2;
			}
			else{
				if(s1>s2)++s1;
				else ++s2;
			}
			if(Rnd()&1)swap(s1,s2);
			if(Rnd()%100<V)a[i]=s1,b[i]=s2;
			else a[i]=b[i]=-1;
		}
		printf("%d\n",n);
		for(re int i=1;i<=n;++i)printf("%d %d\n",a[i],b[i]);
	}
}
void VP(int T,int mxn,int V){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		re int s1=0,s2=0,n=0;
		for(re int i=1;i<=mxn;++i){
			n=i;
			if(Rnd()%2==1)++s1;else ++s2;
			if(Rnd()&1)swap(s1,s2);
			if(Rnd()%100<V)a[i]=s1,b[i]=s2;
			else a[i]=b[i]=-1;
			if(max(s1,s2)>=11&&abs(s1-s2)>=2)break;
		}
		printf("%d\n",n);
		for(re int i=1;i<=n;++i)printf("%d %d\n",a[i],b[i]);
	}
}
int main(){
	ID=2;
	Genrnd(20000,1,25,1,1);
	Genrnd(20000,1,25,1,10);
	Genrnd(20000,1,25,5,1);
	Genrnd(20000,1,25,5,10);
	Genrnd(20000,1,25,10,1);
	Genrnd(20000,1,25,30,1);
	VP(20000,25,50);
	VP(20000,25,5);
	VP(10000,50,50);
	VP(10000,50,5);
	GenLong(500,995,1000,50);
	GenLong(500,995,1000,5);
	GenLong(5,99995,100000,50);
	GenLong(5,99995,100000,5);
}
