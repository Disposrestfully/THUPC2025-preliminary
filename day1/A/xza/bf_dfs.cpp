#include <bits/stdc++.h>
using namespace std;

const int N = 85;
int a[N], w[N], d[N], t[N], s[N];
int n, m, c, ans = 1e9;

void dfs(int k, int total) {
    if (total >= ans) return;
    if (k == n + 1) {
        ans = min(ans, total);
        return;
    }
    for (int i = 0; i <= m; i ++) {
        a[k] = i;
        int mx = 0;
        for (int j = 1; j <= k; j ++) {
            if (a[j] && k < j + d[a[j]]) {
                mx = max(mx, t[a[j]]);
            }
        }
        dfs(k + 1, total + c * max(0, s[k] - mx) + w[i]);
    }
}

int main() {
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
    }
    for (int i = 1; i <= m; i ++) {
        cin >> w[i] >> d[i] >> t[i];
    }
    dfs(1, 0);
    cout << ans << endl;

    return 0;
}