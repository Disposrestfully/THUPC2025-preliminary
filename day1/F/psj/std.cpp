#include<bits/stdc++.h>
using namespace std;

#define pii pair < int , int >
#define pb push_back
const int LIM = 4;
int T, n; map < vector < int > , vector < pii > > ans;
void init(){
	queue < vector < int > > q;
	for(int i = 1 ; i <= LIM ; ++i){
		vector < int > x; for(int j = 1 ; j <= i ; ++j) x.pb(j);
		ans[x] = {}; q.push(x);
		while(!q.empty()){
			x = q.front(); q.pop(); vector < pii > cur = ans[x];
			for(int j = 0 ; j < i ; ++j)
				for(int k = j + 2 ; k < i ; ++k){
					swap(x[j], x[k]); cur.pb(pii(j + 1, k + 1));
					if(ans.find(x) == ans.end()){ans[x] = cur; q.push(x);}
					if(x[0] == 1 && x[1] == 3 && x[2] == 4){
						int p = 1;
					}
					swap(x[j], x[k]); cur.pop_back();
				}
		}
	}
	for(auto &t: ans) reverse(t.second.begin(), t.second.end());
}
void output(vector < pii > seq){
	cout << seq.size() << '\n';
	for(auto t : seq) cout << t.first << ' ' << t.second << '\n';
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); init();
	for(cin >> T ; T ; --T){
		int n; vector < int > a; cin >> n;
		for(int i = 1 ; i <= n ; ++i){int x; cin >> x; a.pb(x);}
		if(n <= LIM){
			if(ans.find(a) == ans.end()) cout << -1 << '\n';
			else output(ans[a]);
			continue;
		}
		a.insert(a.begin(), 0); vector < int > vis(a.size(), 0); 
		vector < pii > seq; vector < int > twoc;
		auto addop = [&](vector < int > pos, vector < pii > op){
			for(auto t: op) seq.pb(pii(pos[t.first], pos[t.second]));
		};
		for(int i = 1 ; i <= n ; ++i)
			if(!vis[i]){
				int mx = 0, mn = i; vector < int > cyc;
				while(!vis[i]){vis[i] = mn; cyc.pb(i); i = a[i]; mx = max(mx, i);}
				if(mn == mx) continue;
				auto sep = [&](){
					int p = mn; while(vis[p] == mn) ++p;
					bool flg = cyc.back() > p; int q = 0; while((cyc[q] > p) == flg) ++q;
					rotate(cyc.begin(), cyc.begin() + q, cyc.end());
					for(int i = 0, pre = -1 ; i + 1 < cyc.size() ; ++i)
						if((cyc[i] > p) == flg) seq.pb(pii(pre, cyc[i]));
						else pre = cyc[i];
					for(auto t : cyc) if((t > p) != flg) seq.pb(pii(t, cyc.back()));
				};
				if(mx - mn > cyc.size() - 1){sep(); continue;}
				int cnt = 0;
				for(int i = 0 ; i < cyc.size() && cnt >= 0; ++i){
					int nxt = i + 1 == cyc.size() ? 0 : i + 1;
					if(abs(cyc[nxt] - cyc[i]) > 1)
						if(cyc[nxt] != mx && cyc[nxt] != mn){
							cnt = -1; seq.pb(pii(cyc[i], cyc[nxt]));
							vis[cyc[nxt]] = -1; cyc.erase(cyc.begin() + nxt); sep();
						}else ++cnt;
				}
				if(cnt == 0 || cnt == 1){
					while(mx - mn > 1){
						seq.pb(pii(mn, mx)); swap(a[mn], a[mx]);
						if(a[mn] == mn) ++mn; else --mx;
					}
					twoc.pb(mn);
				}else if(cnt == 2){
					int p = mn; while(a[p] != mx) ++p;
					while(p - mn > 1){seq.pb(pii(mn, p + 1)); ++mn;}
					while(mx - p > 2){seq.pb(pii(p, mx)); --mx;}
					addop({mn, mn+1, mn+2, mn+3}, {pii(0, 3), pii(0, 2), pii(1, 3)});
				}
			}
		while(twoc.size() > 1){
			int q = twoc.back(); twoc.pop_back();
			int p = twoc.back(); twoc.pop_back();
			addop({p, p+1, q, q+1}, {pii(0, 3), pii(0, 2), pii(1, 3), pii(0, 3)});
		}
		if(twoc.size()){
			int p = twoc[0], q = p + 3 <= n ? p + 3 : p - 2;
			addop({p, p+1, q}, {pii(0, 2), pii(1, 2), pii(0, 2)});
		}
		output(seq);
	}
	return 0;
}