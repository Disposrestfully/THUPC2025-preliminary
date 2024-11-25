#include <bits/stdc++.h>
using namespace std;

int rnd(int x) {
    static mt19937 rng(time(NULL));
    return rng() % x + 1;
}

int rnd(int l, int r) {
    return l - 1 + rnd(r - l + 1);
}

int R(int n, int x) {
    return !x ? n : R(rnd(n), x - 1);
}

const int MAX = 150;
const int inf = 10000;
const int INF = 1e9;

int main() {

    for (int T = 1; T <= 40; T ++) {
        freopen((to_string(T)+".in").c_str(), "w", stdout);
        int n = (T > 30 ? MAX : T * 5 + rnd(0, MAX - T * 5));
        int mx = (T > 30 ? MAX : T * 5 + rnd(0, MAX - T * 5));
        int m = rnd(inf);
        int c = rnd(inf);
        printf("%d %d %d\n", n, m, c);
        for (int i = 1; i <= n; i ++) {
            printf("%d%c", rnd(mx), " \n"[i == n]);
        }
        for (int i = 1; i <= m; i ++) {
            int d = R(n, 3);
            int t = rnd(rnd(mx));
            int w = min(INF, R(9 * d * t * c, 3));
            while (w < d * t * c / 20) {
                w = min(INF, R(9 * d * t * c, 3));
            }
            w = min(w, rnd(d * t * c / 2, d * t * c));
            printf("%d %d %d\n", w, d, t);
        }
        fclose(stdout);

        system(("./std < " + to_string(T) 
              + ".in > " + to_string(T) + ".ans").c_str());
    }

    return 0;
}