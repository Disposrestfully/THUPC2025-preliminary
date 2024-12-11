#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAX_LOG 30
#define INF 1000000009
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
struct Info {
	int pos, org, val;
	inline bool operator < (const Info &x) const {
		return val == x.val ? (org == x.org ? pos < x.pos : org > x.org) : val > x.val;
	}
} club[100008];
int u[100008], log[100008], ans[100008], cnt[36];
int main() {
	int t, h, i, j, tot = 0, tmp, sum, minlog = 30;
	scanf("%d %d", &t, &h);
	for (i = 1; i <= t; ++i) scanf("%d", &u[i]);
	
	for (i = 1; i <= t; ++i) {
		tmp = u[i];
		for (j = 0; tmp > 1; ++j, tmp >>= 1);
		cmin(minlog, j);
		++cnt[log[i] = j];
	}
	sum = tmp = 0;
	for (j = 29; j >= minlog; --j) {
		tmp += cnt[j];
		if (sum + tmp > h) break;
		sum += tmp;
	}
	
	if (j >= minlog) {
		for (i = 1; i <= t; ++i) {
			if (log[i] >= j) {
				club[++tot] = (Info) {i, log[i] == j ? INF : u[i], u[i] << MAX_LOG - log[i]};
				ans[i] = log[i] - j;
			}
		}
		tmp = h - sum;
	}
	else {
		tmp = (h - sum) / t;
		for (i = 1; i <= t; ++i) {
			club[i] = (Info) {i, u[i], u[i] << MAX_LOG - log[i]};
			ans[i] = log[i] - minlog + 1 + tmp;
		}
		tmp = h - sum - tmp * t;
		tot = t;
	}
	
	if (tmp) {
		sort(club + 1, club + tot + 1);
		for (i = 1; i <= tmp; ++i) ++ans[club[i].pos];
	}

	for (i = 1; i <= t; ++i) printf("%d%c", ans[i], " \n"[i == t]);
	return 0;
}