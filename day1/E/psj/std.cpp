//2hd
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int _ = 2e6 + 7, INF = 1e9; int n, q;
int sum2(int l, int r){return (l + r) * (r - l + 1) / 2;}
struct dat{
	int l, cnt, sum;
	dat(int x = 0, int c = 0){cnt = c; sum = x * c; l = x - (c >> 1);}
	int r(){return l + cnt;}
	void operator +=(dat &q){cnt += q.cnt; sum += q.sum; l = (sum - sum2(-INF, -INF + cnt - 1)) / cnt - INF;}
	int qpos(int x){return l + x - (x <= cnt - sum + sum2(l, l + cnt - 1));}
}stk[_]; int top;

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1 ; i <= n ; ++i){
		int x, c; cin >> x >> c; stk[++top] = dat(x, c);
		while(top > 1 && stk[top - 1].r() >= stk[top].l){stk[top - 1] += stk[top]; --top;}
	}
	int tot = 0, q, pos = 1; cin >> q;
	while(q--){
		int x; cin >> x; while(tot + stk[pos].cnt < x) tot += stk[pos++].cnt;
		cout << stk[pos].qpos(x - tot) << "\n";
	}
	return 0;
}