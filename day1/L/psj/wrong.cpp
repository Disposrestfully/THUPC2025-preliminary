#include<bits/stdc++.h>
using namespace std;

int n, m, c;

const int _ = 1e6 + 7; struct Edge{int end , upEd , f;}Ed[_];
int head[_] , cur[_] , dep[_] , cntEd = 1, cntc; queue < int > q;
void addEd(int x , int y , int c){Ed[++cntEd] = (Edge){y , head[x] , c}; head[x] = cntEd;}
void addE(int x , int y , int c = 1){addEd(x , y , c); addEd(y , x , 0);}

bool bfs(){
	memset(dep , 0 , sizeof(int) * (cntc + 1));
	memcpy(cur , head , sizeof(int) * (cntc + 1));
	while(!q.empty()) q.pop();
	q.push(1); dep[1] = 1;
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int i = head[t] ; i ; i = Ed[i].upEd)
			if(Ed[i].f && !dep[Ed[i].end]){
				dep[Ed[i].end] = dep[t] + 1; q.push(Ed[i].end);
				if(Ed[i].end == n) return 1;
			}
	}
	return 0;
}

int dfs(int x , int v){
	if(x == n) return v;
	int sum = 0;
	for(int &i = cur[x] ; i ; i = Ed[i].upEd)
		if(Ed[i].f && dep[Ed[i].end] == dep[x] + 1){
			int f = dfs(Ed[i].end , min(Ed[i].f , v - sum));
			sum += f; Ed[i].f -= f; Ed[i ^ 1].f += f;
			if(sum == v) break;
		}
	return sum;
}

int dinic(){int sum = 0; while(bfs()){sum += dfs(1 , n);} return sum;}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> c; 
	static int p[_]; for(int i = 1 ; i <= c ; ++i) cin >> p[i];
	static vector < int > in[_], out[_];
	for(int i = 1 ; i <= m ; ++i){int x, y, r; cin >> x >> y >> r; addE(x, y);}
	cntc = n; cout << dinic() << "\n";
	return 0;
}