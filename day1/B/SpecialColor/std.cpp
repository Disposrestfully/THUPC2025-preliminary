#include <cstdio>
#include <cstring>
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define INF 999999999
struct Info {
	int pos, val;
} stk[504];
char w[504][504], y[504][504];
int stay[504][504], mvfr[504][504], mvto[504][504];
int topmv[504], ans[504];
int main(){
	int n, m, clim, d, i, j, lmin, lmax, rmin, rmax, mmin, mmax, tbd, dbd, llbd, lrbd, rlbd, rrbd, stop, height, weight, area, lpos, open = 1;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%s", w[i] + 1);
	for (i = 1; i <= n; ++i) scanf("%s", y[i] + 1);

	for (d = 1; d < m; ++d) {
		clim = m - d;
		lmin = rmin = mmin = tbd = INF;
		lmax = rmax = mmax = dbd = 0;
		
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= clim; ++j) {
				stay[i][j] = (w[i][j] == y[i][j] ? 1 : 0);
				mvfr[i][j + d] = mvto[i][j] = (w[i][j + d] == y[i][j] ? 1 : 0);
				if (j <= d) mvfr[i][j] = 0;

				if (stay[i][j] == 0) {
					if (mvfr[i][j] == 0) {
						if (mvto[i][j] == 0) {
							ans[d] = -1;
							break;
						}
						// only to is 1, must move from (j + d) to j, being leftmost
						// fprintf(stderr, "<< %d %d (%d -> [%d])\n", d, i, j + d, j);
						cmin(lmin, j);
						cmax(lmax, j);
					}
					else {
						if (mvto[i][j] == 0) {	// must from j to (j - d), being rightmost
							// fprintf(stderr, ">> %d %d ([%d] -> %d)\n", d, i, j, j - d);
							cmin(rmin, j - d);
							cmax(rmax, j - d);
						}
						else {
							// fprintf(stderr, "<> %d %d (%d -> [%d] -> %d)\n", d, i, j + d, j, j - d);
							cmin(mmin, j);
							cmax(mmax, j - d);
						}
					}
					cmin(tbd, i);
					cmax(dbd, i);
				} 
				
			}
			if (ans[d] == -1) break;
			for (; j <= m; ++j) {
				if (w[i][j] != y[i][j]) {
					if (mvfr[i][j] == 0) {
						ans[d] = -1;
						break;
					}
					// fprintf(stderr, ">> %d %d ([%d] -> %d)\n", d, i, j, j - d);
					cmin(rmin, j - d);
					cmax(rmax, j - d);
					cmin(tbd, i);
					cmax(dbd, i);
				}
			}
			if (ans[d] == -1) break;
		}
		if (ans[d] == -1) continue;
		
		// Leftmost / rightmost must move width must < d
		if (lmax - lmin > d || rmax - rmin > d) {
			ans[d] = -1;
			break;
		}
		// Check middle?

		// Set boundary; tbd = top max, dbd = down min
		// fprintf(stderr, "<<%d %d | %d %d | %d %d>>\n", lmin, lmax, mmin, mmax, rmin, rmax);
		llbd = dmax(1, lmax - d + 1);
		lrbd = dmin(lmin, rmin);
		lrbd = dmin(lrbd, mmin);
		lrbd = dmin(lrbd, m - d);
		rlbd = dmax(lmax, rmax);
		rlbd = dmax(rlbd, mmax);
		rlbd = dmax(rlbd, 1);
		rrbd = dmin(m - d, rmin + d - 1);
		// fprintf(stderr, "<%d %d | %d %d | %d %d>\n", llbd, lrbd, rlbd, rrbd, tbd, dbd);
		memset(topmv, -1, sizeof(topmv));
		ans[d] = -1;
		for (i = 1; i <= n; ++i) {
			stop = 0;
			open = (i >= dbd ? 1 : 0);
			for (j = llbd; j <= rrbd; ++j) {
				if (mvto[i][j] == 0) topmv[j] = -1;
				else if (i <= tbd && topmv[j] == -1) {
					topmv[j] = i;
				}
				if (open) {
					if (topmv[j] > 0) {
						height = i - topmv[j] + 1;
					}
					else height = 0;
					// fprintf(stderr, "@ %d %d %d h = %d\n", d, i, j, height);
					if (stop == 0) {
						if (j <= lrbd) stk[++stop] = (Info) {j, height};
					}
					else {
						lpos = j;
						while (stop && stk[stop].val > height) {
							if (i >= dbd && j > rlbd) {
								area = (j - stk[stop].pos) * stk[stop].val;
								// if (d == 40) fprintf(stderr, "| %d %d [%d, %d) %d = %d\n", d, i, stk[stop].pos, j, stk[stop].val, area);
								cmax(ans[d], area);
							}
							lpos = stk[stop].pos;
							--stop;
						}
						if (lpos <= lrbd && height) {
							stk[++stop] = (Info) {lpos, height};
						}
					}
					// fprintf(stderr, "top @ %d: (%d, %d)\n", stop, stk[stop].pos, stk[stop].val);
				}
				if (height == 0 && j > lrbd) open = 0;
			}
			if (i >= dbd && open) {
				while (stop) {
					area = (rrbd - stk[stop].pos + 1) * stk[stop].val;
					// if (d == 40) fprintf(stderr, "| %d %d [%d, %d] %d = %d\n", d, i, stk[stop].pos, rrbd, stk[stop].val, area);
					cmax(ans[d], area);
					--stop;
				}
			}
		}
	}

	for (i = 1; i < m; ++i) printf("%d%c", ans[i], " \n"[i == m - 1]);
	return 0;
}