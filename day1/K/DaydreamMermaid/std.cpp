#include <cstdio>
#include <vector>
using namespace std;
#define MAXK 1000008
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
char buf[15000003], *bufend = buf;
int hflag[MAXK], perm[MAXK], pn[MAXK], qn[MAXK], reten[MAXK], concat[MAXK], vis[MAXK], top, head;
struct Haruka {
	vector<int> pos;
	int depth;
	inline void clear() {
		pos.clear();
		depth = 0;
		return ;
	}
	int pop_all() {
		int ret = depth + 1;
		for (int i = pos.size() - 1, cnt = 1; i >= 0; --i, ++cnt) {
			hflag[pos[i]] = vis[perm[pos[i]]] = 1;
			pn[pos[i]] = ret;
			qn[pos[i]] = cnt;
		}
		return ret;
	}
	inline void init(const int x) {
		clear();
		pos.push_back(x);
		return ;
	}
	inline void push(const int x) {
		pos.push_back(x);
		return ;
	}
	inline int finalize(const int x) {
		push(x);
		return pop_all();
	}
	inline int top_order() const {
		return perm[pos.back()];
	}
	inline void update_depth(int d) {
		cmax(depth, d);
		return ;
	}
} stk[MAXK];
inline void finalize_top(const int x) {
	int depth = stk[top].finalize(x);
	if (--top) stk[top].update_depth(depth);
	return ;
}
inline bool push_stack(const int x) {
	if (stk[top].top_order() < perm[x]) return false;
	stk[++top].init(x);
	return true;
}
inline bool add_haruka(const int x, const int order) {
	if (top && stk[top].top_order() == order + 1) stk[top].push(x);
	else if (top == 0 || stk[top].top_order() > order) stk[++top].init(x);
	else return false;
	return true;
}
int main() {
	int k, i, j;
	scanf("%d", &k);
	for (i = 1; i <= k; ++i) scanf("%d", &perm[i]);
	
	perm[0] = perm[k + 1] = -1;
	for (i = 1; i <= k; ++i) {
		// Read immediately
		// fprintf(stderr, "Working on %d, current top = %d\n", i, top); fflush(stderr);
		if (perm[i] == head + 1) {
			// Clear current stack
			if (top && stk[top].top_order() == perm[i] + 1) {
				finalize_top(i);
				while (vis[head + 1]) ++head;
			}
			else vis[++head] = 1;
		}
		else {
			// Check reten
			if (perm[i + 1] + 1 == perm[i]) {
				j = i;
				do {
					reten[j] = vis[perm[j]] = 1;
					++j;
				} while (perm[j] == perm[j + 1] + 1);
				if (top && perm[i] == stk[top].top_order() - 1) {
					finalize_top(i);
				}
				// head  -| ... perm[i] <- ... <- perm[j] <-|
				if (perm[j] == head + 1) {
					vis[perm[i]] = vis[perm[j]] = 1;
					while (vis[head + 1]) ++head;
				}
				else {
					if (!push_stack(j)) {
						puts("-1");
						return 0;
					}
				}
			}
			else {
				// Check hyphen & add a range
				if (perm[i + 1] - 1 == perm[i]) {
					concat[i] = 1;
					for (j = i + 1; perm[j] + 1 == perm[j + 1]; ++j) {
						concat[j] = 1;
						vis[perm[j]] = 1;
					}
					vis[perm[j]] = 1;
				}
				// No hyphen, add a single character
				else j = i;
				if (!add_haruka(i, perm[j])) {
					puts("-1");
					return 0;
				}
			}
			i = j;
		}
	}

	if (head != k) {
		puts("-1");
		return 0;
	}

	for (i = 1; i <= k; ++i) {
		*(bufend++) = '.';
		if (hflag[i]) {
			bufend += sprintf(bufend, "%d-%d", pn[i], qn[i]);
		}
		if (reten[i]) {
			*(bufend++) = '*';
		}
		else if (concat[i]) {
			*(bufend++) = '#';
		}
	}
	puts(buf);
	return 0;
}