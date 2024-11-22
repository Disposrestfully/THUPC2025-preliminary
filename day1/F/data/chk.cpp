#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int LIM = 1e5;
int main(int argc, char **argv){
	registerTestlibCmd(argc, argv);
	int T = inf.readInt(1, LIM, "T"), sumn = 0;
	for(int i = 1 ; i <= T ; ++i){
		int n = inf.readInt(1, LIM, "n"); sumn += n;
		vector < int > A = inf.readInts(n); A.insert(A.begin(), 0);
		int ansstep = ans.readInt(), outstep = ouf.readInt(-1, 5 * n);
		if(ansstep == -1 && outstep == -1) continue;
		if(ansstep != -1 && outstep == -1)
			quitf(_wa, "Testcase %d: You report no solution but jury has a solution.", i);
		for(int j = 1 ; j <= outstep ; ++j){
			int x = ouf.readInt(1, n, "i"), y = ouf.readInt(1, n, "j");
			ensuref(abs(x - y) > 1, "Testcase %d operation %d: |i - j| <= 1.", i, j);
			swap(A[x], A[y]);
		}
		for(int j = 1 ; j <= n ; ++j)
			ensuref(A[j] == j, "Testcase %d: The result is not sorted as A[%d] = %d.", i, j, A[j]);
		if(ansstep < outstep)
			quitf(_wa, "Testcase %d: Your step is larger than the optimal.", i);
		if(ansstep > outstep)
			quitf(_fail, "Testcase %d: Your step is smaller than the optimal??? Please contact admin.", i);
	}
	ensuref(sumn <= LIM, "sum of n exceeds %d", LIM);
	quitf(_ok, "orz U R the sorting master.");
}