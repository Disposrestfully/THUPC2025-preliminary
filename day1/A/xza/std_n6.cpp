// copyright @ Zhean Xu
#include <bits/stdc++.h>
using namespace std;

const int N = 155;
int f[N][N][N], g[N][N], sum[N][N], s[N];
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

    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= m; i ++) {
        int w, d, t;
        scanf("%d%d%d", &w, &d, &t);
        cmin(g[min(t, mx)][d], w);
    }
    for (int i = 1; i <= mx; i ++) {
        for (int j = n; j >= 1; j --) {
            cmin(g[i][j], g[i][j + 1]);
        }
    }

    memset(f, 0x3f, sizeof f);
    for (int i = mx; i >= 1; i --) {
        for (int l = n; l >= 1; l --) {
            for (int r = l; r <= n; r ++) {
                f[i][l][r] = (sum[i][r] - sum[i][l - 1]) * c;
                for (int x = l; x <= r; x ++) {
                    for (int y = x; y <= r; y ++) {
                        int tmp = 0;
                        if (l <= x - 1) tmp += f[i][l][x - 1];
                        if (y + 1 <= r) tmp += f[i][y + 1][r];
                        for (int j = i; j <= mx; j ++) {
                            int nw = tmp + g[j][y - x + 1] + (j == mx ? 0 : f[j + 1][x][y]);
                            cmin(f[i][l][r], nw);
                        }
                    }
                }
                // printf("%d %d %d  %d\n", i, l, r, f[i][l][r]);                           
            }
        }
    }   
    cout << f[1][1][n] << endl;

    return 0;
}