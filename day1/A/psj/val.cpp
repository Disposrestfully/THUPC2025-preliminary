#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int LIMN = 150, LIMM = 1e4, LIMC = 1e4, LIMS = 150, LIMW = 1e9, LIMT = 150;

int main(){
	registerValidation();
	int n = inf.readInt(1, LIMN, "n"); inf.readSpace();
	int m = inf.readInt(1, LIMM, "m"); inf.readSpace();
	int c = inf.readInt(1, LIMC, "c"); inf.readEoln();
	for(int i = 1 ; i <= n ; ++i){
		inf.readInt(1, LIMS, "s");
		if(i != n) inf.readSpace();
		else inf.readEoln();
	}
	for(int i = 1 ; i <= m ; ++i){
		inf.readInt(1, LIMW, "w"); inf.readSpace();
		inf.readInt(1, n, "d"), inf.readSpace();
		inf.readInt(1, LIMT, "t"); inf.readEoln();
	}
	inf.readEof();
	return 0;
}