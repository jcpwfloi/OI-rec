#include<cstdio>
#include<algorithm>
#define gi gI()
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define repD(i, l, r) for (int i = r; i; i--)

using namespace std;

typedef long long ll;

inline ll gI() {
    ll p = 0, flag = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    while ('0' <= c && c <= '9') p = p * 10 + (c - '0'), c = getchar();
    return p * flag;
}

int n, V[MAXN], first[MAXN], nex[MAXN * 2], to[MAXN * 2];
int dep = 0, dfn[MAXN];

namespace sgt {
    struct info {
	int Max, Sum;
    };
    struct Node {
	int L, R;
	info inf;
    } T[T_MAX];
    info merge(info a, info b) {
	return (info){max(a.Max, b.Max), a.Sum + b.Sum};
    }
    inline void Update(int u) {
	T[u].inf = merge(T[lson].inf, T[rson].inf);
    }
    inline void Cover(int u, int C) {
	T[u].inf = merge(T[u].inf, (info){C, C});
    }
    inline void Edit(int u, int x, int C) {
	if (T[u].L == T[u].R) {
	    Cover(u, C);
	    return;
	}
	if (T[lson].L <= x && x <= T[lson].R) Edit(lson, x, C);
	else Edit(rson, x, C);
	Update(u);
    }
    inline inf Query(int u, int L, int R) {
	if (T[u].L <= L && L <= T[u].R) return T[u].inf;
	info ans = (info){0, 0};
	if (L <= T[lson].R) ans = merge(ans, Query(lson, L, R));
	if (R >= T[rson].L) ans = merge(ans, Query(rson, L, R));
	return ans;
    }
    inline void Build(int u, int L, int R) {
	T[u].L = L;
	T[u].R = R;
	if (L == R) {
	    T[u].inf = (info){0, 0};
	    return;
	}
    }
}

void dfs1(int u, int father) {
    s[u] = 1;
    int maxs = 0, maxnum = 0;
    for (int i = first[u]; i; i = nex[i]) {
	int v = to[i];
	if (v != father) {
	    dfs1(v);
	    s[u] += s[v];
	    if (s[v] > maxs) {
		maxs = s[v];
		maxnum = v;
	    }
	}
    }
    son[u] = maxnum;
}

void dfs2(int u, int father) {
    dfn[u] = ++dep;
    if (son[u]) {
	top[son[u]] = top[u];
	dfs2(u);
    }
    for (int i = first[u]; i; i = nex[i]) {
	int v = to[i];
	if (v != father && v != son[u]) {
	    dfs2(v);
	}
    }
}

int main() {
    n = gi;
    sgt::Build(1, 1, n);
    rep(i, 1, n - 1) {
	int u = gi, v = gi;
	addEdge(u, v);
	addEdge(v, u);
    }
    rep(i, 1, n) top[i] = i;
    rep(i, 1, n) V[i] = gi;
    dfs1(1, -1);
    dfs2(1, -1);
    return 0;
}

