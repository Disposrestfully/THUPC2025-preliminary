#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t;
string S;
map<string,int>F;
inline string simplify(string A){
	string B="";
	for(re int i=0;i<A.size();++i){
		if(i==0)B+=A[i];
		else if(A[i]!='X')B+=A[i];
		else if(A[i]!=A[i-1])B+=A[i];
	}
	return B;
}
inline string reverse(string A){
	for(auto &z:A)
		if(z!='X'){
			if(z=='M')z='W';
			else z='M';
		}
	return A;
}
inline int dfs(string A){
	if(F.count(A))return F[A];
	re int iw=0,im=0;
	for(auto z:A)if(z=='M')im=1;else if(z=='W')iw=1;
	if(iw==0&&im==0)return F[A]=0;
	if(iw==0)return F[A]=1;
	if(im==0)return F[A]=-1;
	re int s=-1;
	for(re int l=0;l<A.size();++l)
		for(re int r=l;r<A.size();++r){
			if(A[r]=='X')break;
			string tmp="";
			for(re int i=0;i<l;++i)tmp+=A[i];
			for(re int i=r+1;i<A.size();++i)tmp+=A[i];
			s=max(s,-dfs(reverse(simplify(tmp))));
		}
	return F[A]=s;
}
int main(){
	t=read();
	while(t--){
		cin>>S;
		re int s=dfs(simplify(S));
		if(s==1)puts("Water");
		else if(s==0)puts("Draw");
		else puts("Menji");
	}
}



