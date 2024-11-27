#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int LIMM = 2e6, LIMV = 1e9, LIMQ = 2e6;

int main(){
	registerValidation();
	int m = inf.readInt(1, LIMM); inf.readEoln();
	int prex = 0; long long sumc = 0;
	for(int i = 1 ; i <= m ; ++i){
		int x = inf.readInt(prex + 1, LIMV); inf.readSpace();
		int c = inf.readInt(1, LIMV); inf.readEoln();
		prex = x; sumc += c;
	}
	int q = inf.readInt(1, LIMQ); inf.readEoln();
	long long prek = 0;
	for(int i = 1 ; i <= q ; ++i){
		long long k = inf.readLong(prek + 1, sumc); inf.readEoln();
		prek = k;
	}
	inf.readEof();
	return 0;
}