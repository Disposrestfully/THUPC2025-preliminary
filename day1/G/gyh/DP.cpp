#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int f[22][42][22][42][42];
char v[22][42][22][42][42];
inline int dfs(re int a,re int b,re int c,re int d,re int e){
	if(v[a][b][c][d][e])return f[a][b][c][d][e];
	v[a][b][c][d][e]=1;re int s=-1;
	if(!a&&!b&&!c&&!d&&!e)return f[a][b][c][d][e]=0;
	if(!a&&!b&&!c&&!e)return f[a][b][c][d][e]=1;
	if(!a&&!c&&!d&&!e)return f[a][b][c][d][e]=-1;
	if(a)s=max(s,-dfs(c,d,a-1,b,e)),s=max(s,-dfs(c,d,a-1,b,e+1));
	if(b)s=max(s,-dfs(c,d,a,b-1,e));
	if(c)s=max(s,-dfs(c-1,d+1,a,b,e));
	if(e)s=max(s,-dfs(c,d+1,a,b,e-1));
	return f[a][b][c][d][e]=s;
}
int t,n,A0,B0,A1,B1,C,num[2];
char s[1000002];
int main(){
	t=read();
	while(t--){
		scanf("%s",s+1),n=strlen(s+1);
		A0=B0=A1=B1=C=num[0]=num[1]=0;
		re int fst=-1,lst=-1;
		for(re int i=1;i<=n;++i)
			if(s[i]=='X'){
				if(fst!=-1){
					if(fst!=lst)++C;
					else{
						if(fst==1&&num[0])++A1;
						else if(fst==1)++A0;
						else if(fst==0&&num[1])++B1;
						else ++B0;
					}
				}
				fst=lst=-1,num[0]=num[1]=0;
			}
			else{
				if(fst==-1)fst=s[i]=='W';
				lst=s[i]=='W';
				++num[s[i]=='W'];
			}
		if(fst!=-1){
			if(fst!=lst)++C;
			else{
				if(fst==1&&num[0])++A1;
				else if(fst==1)++A0;
				else if(fst==0&&num[1])++B1;
				else ++B0;
			}
		}
		re int s=dfs(A1,A0,B1,B0,C);
		if(s==1)puts("Water");
		else if(s==0)puts("Draw");
		else puts("Menji");
	}
}


