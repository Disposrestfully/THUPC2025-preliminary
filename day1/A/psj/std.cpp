#include<bits/stdc++.h>
using namespace std;

const int _ = 153, INF = 0x3f3f3f3f;
int n, m, c, s[_], mnplan[_][_], f[_][_][_], g[_][_][_], h[_][_][_];

int sf(int l, int r, int v);
int sg(int l, int r, int v);
int sh(int l, int r, int v);

int sf(int l, int r, int v){
	if(l > r) return 0;
	if(v >= _) return INF;
	if(f[l][r][v] != INF) return f[l][r][v];
	--f[l][r][v];
	for(int i = l ; i <= r + 1 ; ++i)
		f[l][r][v] = min(f[l][r][v], sf(l, i - 1, v + 1) + sg(i, r, v));
	return f[l][r][v];
}
int sg(int l, int r, int v){
	if(l > r) return 0;
	if(g[l][r][v] != INF) return g[l][r][v];
	--g[l][r][v];
	for(int i = l ; i <= r && mnplan[v][i - l + 1] != INF ; ++i)
		g[l][r][v] = min(g[l][r][v], sh(l, i, v) + mnplan[v][i - l + 1] + sf(i + 1, r, v));
	return g[l][r][v];
}
int sh(int l, int r, int v){
	if(l > r) return 0;
	if(h[l][r][v] != INF) return h[l][r][v];
	if(l == r) return h[l][r][v] = max(0, s[l] - v) * c;
	--h[l][r][v];
	for(int i = l + 1 ; i <= r ; ++i)
		h[l][r][v] = min(h[l][r][v], sf(l + 1, i - 1, v + 1) + sh(i, r, v) + max(0, s[l] - v) * c);
	return h[l][r][v];
}

int main(){
	cin >> n >> m >> c; for(int i = 1 ; i <= n ; ++i) cin >> s[i];
	memset(mnplan, 0x3f, sizeof(mnplan)); mnplan[0][n] = 0;
	for(int i = 1 ; i <= m ; ++i){int w, d, t; cin >> w >> d >> t; mnplan[t][d] = min(mnplan[t][d], w);}
	for(int i = 0 ; i < _ ; ++i)
		for(int j = n ; j ; --j)
			mnplan[i][j] = min(mnplan[i][j], mnplan[i][j + 1]);
	memset(f, 0x3f, sizeof(f)); memset(g, 0x3f, sizeof(g)); memset(h, 0x3f, sizeof(h));
	cout << sf(1, n, 0) << "\n";
	return 0;
}