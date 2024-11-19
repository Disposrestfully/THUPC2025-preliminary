#include<bits/stdc++.h>
#define re register
using namespace std;
mt19937 Rnd(1145141);
int ID,a[100002];
char s[100002];
inline void genrand(re int N){
	for(re int i=1;i<=N;++i){
		re int v=Rnd()%3;
		if(v==0)s[i]='W';
		else if(v==1)s[i]='M';
		else s[i]='X';
	}
}
inline void gensmallX(re int N){
	for(re int i=1;i<=N;++i){
		if(Rnd()%(N/2)==0)s[i]='X';
		else if(Rnd()&1)s[i]='W';
		else s[i]='M';
	}
}
inline bool chk(re int N){
	re int iw=0,im=0;
	for(re int i=1;i<=N;++i){
		if(s[i]=='W')iw=1;
		if(s[i]=='M')im=1;
	} 
	return iw&&im;
}
void Genrnd(int T,int LN,int RN){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		while(1){
			re int n=Rnd()%(RN-LN+1)+LN;
			genrand(n);
			if(chk(n)){
				for(re int i=1;i<=n;++i)putchar(s[i]);
				puts("");
				break;
			}
		}
	} 
}

void GensmallX(int T,int LN,int RN){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		while(1){
			re int n=Rnd()%(RN-LN+1)+LN;
			gensmallX(n);
			if(chk(n)){
				for(re int i=1;i<=n;++i)putchar(s[i]);
				puts("");
				break;
			}
		}
	} 
}

void Genspecial1(int T,int N){
	++ID;
	cerr<<"Generating test "<<ID<<"\n";
	string tmp=to_string(ID)+".in";
	freopen(tmp.c_str(),"w",stdout);
	printf("%d\n",T);
	while(T--){
		string S="";
		for(re int i=1;i<=N;++i)S+="WMWX";
		if(Rnd()&1)S+="WMWX";
		for(re int i=1;i<=N;++i)S+="WWX";
		if(Rnd()&1)S+="WWX";
		for(re int i=1;i<=N;++i)S+="MXMX";
		if(Rnd()&1)S+="MXMX";
		for(re int i=1;i<=N;++i)S+="MMX";
		if(Rnd()&1)S+="MMX";
		for(re int i=1;i<=N;++i)S+="WMX";
		if(Rnd()&1)S+="WMX";
		cout<<S<<'\n';
	} 
}
int main(){
	ID=1;
	Genrnd(50000,2,9);
	Genrnd(50000,10,10);
	Genrnd(33333,15,15);
	Genrnd(25000,15,20);
	Genrnd(25000,20,20);
	Genrnd(10000,40,50);
	Genrnd(10000,50,50);
	Genrnd(500,996,1000);
	Genrnd(50,9996,10000);
	Genrnd(5,99996,100000);
	GensmallX(10000,50,50);
	GensmallX(500,996,1000);
	GensmallX(50,9996,10000);
	GensmallX(5,99996,100000);
	Genspecial1(50,490);
	Genspecial1(5,4990);
	for(re int i=1;i<=ID;++i){
		string tmp="std.exe < "+to_string(i)+".in > "+to_string(i)+".ans";
		cerr<<tmp<<endl;
		system(tmp.c_str());
	}
}
