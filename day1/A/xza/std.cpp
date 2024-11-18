// copyright @ Zhean Xu
#include <bits/stdc++.h>
using namespace std;

const int N = 155;
int f[N][N][N], g[N][N][N], h[N][N][N], cost[N][N], sum[N][N], s[N];
int n, m, c, mx;

void cmin(int &x, int y) {
    if (y < x) x = y;
}

int main() {
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; i ++) {
        scanf("%d" , s + i);
        mx = max(mx, s[i]);
    }
    for (int i = 1; i <= mx; i ++) {
        for (int j = 1; j <= n; j ++) {
            sum[i][j] = sum[i][j - 1] + max(0, s[j] - i + 1);
        }
    }

    memset(cost, 0x3f, sizeof cost);
    for (int i = 1; i <= m; i ++) {
        int w, d, t;
        scanf("%d%d%d", &w, &d, &t);
        cmin(cost[min(t, mx)][d], w);
    }
    for (int i = 1; i <= mx; i ++) {
        for (int j = n; j >= 1; j --) {
            cmin(cost[i][j], cost[i][j + 1]);
        }
    }

    memset(f, 0x3f, sizeof f);
    memset(g, 0x3f, sizeof g);
    memset(h, 0x3f, sizeof h);
    for (int i = mx; i >= 1; i --) {
        for (int l = n; l >= 1; l --) {
            for (int r = l; r <= n; r ++) {
                f[i][l][r] = g[i][l][r] = (sum[i][r] - sum[i][l - 1]) * c;
                for (int x = l; x <= r; x ++) {
                    int tmp = (l <= x - 1 ? f[i][l][x - 1] : 0);
                    tmp += min(cost[mx][r - x + 1], h[i + 1][x][r]);
                    cmin(g[i][l][r], tmp);
                }
                for (int y = l; y <= r; y ++) {
                    int tmp = (y + 1 <= r ? f[i][y + 1][r] : 0);
                    tmp += g[i][l][y];
                    cmin(f[i][l][r], tmp);
                }
                h[i][l][r] = min(h[i + 1][l][r],
                    + cost[i - 1][r - l + 1] + f[i][l][r]);                       
            }
        }
    }   
    cout << f[1][1][n] << endl;

    return 0;
}