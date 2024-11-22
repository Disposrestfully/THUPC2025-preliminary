#include<bits/stdc++.h>
using namespace std;

#define pii pair < int , int >
#define pb push_back
const int LIM = 7;
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
					swap(x[j], x[k]); cur.pop_back();
				}
		}
	}
	for(auto &t: ans) reverse(t.second.begin(), t.second.end());
}
int main(){
	ios::sync_with_stdio(0); init();
	for(cin >> T ; T ; --T){
		int n; vector < int > a; cin >> n;
		for(int i = 1 ; i <= n ; ++i){int x; cin >> x; a.pb(x);}
		if(n <= LIM){
			if(ans.find(a) == ans.end()) cout << -1 << '\n';
			else cout << ans[a].size() << "\n";
			continue;
		}
		a.insert(a.begin(), 0); vector < int > vis(a.size(), 0); 
		int cntnc = 0, step = n;
		for(int i = 1 ; i <= n ; ++i)
			if(!vis[i]){
				int cnt = 0; --step;
				while(!vis[i]){vis[i] = 1; cnt += abs(i - a[i]) > 1; i = a[i];}
				if(a[i] != i) cntnc += cnt <= 1;
			}
		cout << step + cntnc + (cntnc & 1) << '\n';
	}
	return 0;
}