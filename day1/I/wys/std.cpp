#include <cstdio>
#include <cassert>
#include <algorithm>

const int MOD = 998244353;

static void solve(int n) {
    int _f[30], _f_last[30];
    int _g[30];
    int *f = _f + 15, *f_last = _f_last + 15;
    int *g = _g + 15;
    
    for (int i = -12; i <= 12; i++) {
        f[i] = 0;
        g[i] = 1;
    }
    f[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        int a, b;
        assert(2 == scanf("%d%d", &a, &b));
        if (!(a == -1 && b == -1)) {
            assert(0 <= a && a <= n);
            assert(0 <= b && b <= n);
        }
        
        std::swap(f, f_last);
        
        for (int j = -12; j <= 12; j++) {
            f[j] = 0;
            f_last[j] = f_last[j] * g[j];
            g[j] = 1;
        }
        
        int L, R;
        if (i <= 11) {
            L = -i;
            R = i;
        } else if (i <= 21) {
            L = -11 + (i - 11);
            R = 11 - (i - 11);
        } else {
            L = -2;
            R = 2;
        }
        
        
        
        for (int j = L; j <= R; j++) {
            f[j] = (f_last[j - 1] + f_last[j + 1]) % MOD;
        }
        
        if (i <= 20) {
            if ((i - L) / 2 == 11) {
                g[L] = 0;
            }
            if ((i + R) / 2 == 11) {
                g[R] = 0;
            }
        } else if (i % 2 == 0) {
            g[-2] = g[2] = 0;
        }
        
        if (a != -1) {
            int d = a - b;
            if (a + b != i) {
                d = 233;
            }
            for (int j = L; j <= R; j++) {
                f[j] = j == d || j == -d ? f[j] : 0;
            }
        }
    }
    
    int sum = 0;
    for (int i = -11; i <= 11; i++) {
        sum = (sum + f[i] * (1 - g[i])) % MOD;
    }
    printf("%d\n", sum);
}

int main() {
    int T;
    assert(1 == scanf("%d", &T));
    assert(1 <= T && T <= 100000);
    int sum_n = 0;
    
    while (T--) {
        int n;
        assert(1 == scanf("%d", &n));
        assert(1 <= n && n <= 100000);
        sum_n += n;
        assert(sum_n <= 500000);
        
        solve(n);
    }
}