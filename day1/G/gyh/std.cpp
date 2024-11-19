#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
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
		while(A0&&B0)--A0,--B0;
		if(A0+A1<B0+B1)puts("Water");
		else if(A0+A1>B0+B1+1)puts("Menji");
		else if(A0+A1==B0+B1&&B1==0)puts("Water");
		else if(A1==0&&A0+A1==B0+B1+1)puts("Menji");
		else puts("Draw");
	}
}



