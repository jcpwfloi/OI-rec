#include<cstdio>
#include<algorithm>
#define gi gI()
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define repD(i, r, l) for (int i = r; i >= l; -- i)
#define lson u << 1
#define rson u << 1 | 1

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

const int INF = 0x7FFFFFFF;
const int T_MAX = 400001;
const int MAXN = 100001;

int v[MAXN], inv[MAXN];

struct info {
    int mx, sm;
    info() : mx(~INF), sm(0) {}
    info(int v) : mx(v), sm(v) {}
    info(int a, int b) : mx(a), sm(b) {}
    info operator + (info x) {
	return info(max(this -> mx, x.mx), this -> sm + x.sm);
    }
};

struct Node {
    int L, R, tag;
    info ifo;
} T[T_MAX];
inline void Update(int u) {
    T[u].ifo = T[lson].ifo + T[rson].ifo;
}
inline void Edit(int u, int x, int C) {
    if (T[u].L == T[u].R) {
	T[u].ifo = info(C, C);
	return;
    }
    if (x <= T[lson].R) Edit(lson, x, C); else Edit(rson, x, C);
    Update(u);
}
inline info Query(int u, int L, int R) {
    if (L <= T[u].L && T[u].R <= R) {
	return T[u].ifo;
    }
    info ans;
    if (L <= T[lson].R) ans = ans + Query(lson, L, R);
    if (R >= T[rson].L) ans = ans + Query(rson, L, R);
    return ans;
}
inline void Build(int u, int L, int R) {
    T[u].L = L;
    T[u].R = R;
    if (L == R) {
	T[u].ifo = info(v[inv[L]], v[inv[L]]);
	return;
    }
    int M = (L + R) >> 1;
    Build(lson, L, M);
    Build(rson, M + 1, R);
    Update(u);
}

int n, depth = 0;
int first[MAXN], nex[MAXN], to[MAXN], cnt = 0;
int s[MAXN], dfn[MAXN], son[MAXN], p[MAXN];
int D[MAXN], top[MAXN];

inline void addEdge(int u, int v) {
    nex[++cnt] = first[u];
    first[u] = cnt;
    to[cnt] = v;
}

void dfs1(int u, int father = -1) {
    int maxs = 0, maxnum = 0;
    s[u] = 1;
    for (int i = first[u]; i; i = nex[i]) {
	int v = to[i];
	if (v != father) {
	    dfs1(v, u);
	    s[u] += s[v];
	    if (s[v] > maxs) {
		maxs = s[v];
		maxnum = v;
	    }
	}
    }
    son[u] = maxnum;
}

void dfs2(int u, int father = -1) {
    D[u] = (father == -1 ? 0 : D[father]) + 1;
    p[u] = father == -1 ? 0 : father;
    dfn[u] = ++depth;
    inv[depth] = u;
    if (son[u]) {
	top[son[u]] = top[u];
	dfs2(son[u], u);
    }
    for (int i = first[u]; i; i = nex[i]) {
	int v = to[i];
	if (v != father && v != son[u]) {
	    dfs2(v, u);
	}
    }
}

inline void treediv() {
    dfs1(1);
    rep(i, 1, n) top[i] = i;
    depth = 0;
    dfs2(1);
    Build(1, 1, n);
}

inline info QueryTop(int u, int F) {
    info ans;
    while (top[u] != top[F]) {
	if (top[u] == u) {
	    ans = ans + info(v[u], v[u]);
	    u = p[u];
	} else {
	    int bot = dfn[u];
	    int tp = dfn[top[u]];
	    ans = ans + Query(1, tp, bot);
	    u = p[top[u]];
	}
    }
    int bot = dfn[u], tp = dfn[F];
    ans = ans + Query(1, tp, bot);
    return ans;
}

inline info QueryPath(int u, int x) {
    int uu = u, xx = x;
    while (top[u] != top[x]) {
	int getu = top[u] == u ? p[u] : top[u];
	int getx = top[x] == x ? p[x] : top[x];
	if (D[getu] > D[getx]) u = getu; else x = getx;
    }
    if (D[u] < D[x]) {
	info ans = QueryTop(uu, u) + QueryTop(xx, u);
	ans.sm -= v[u];
	return ans;
    }
    else {
	info ans = QueryTop(uu, x) + QueryTop(xx, x);
	ans.sm -= v[x];
	return ans;
    }
}

inline void changev(int u, int x) {
    v[u] = x;
    Edit(1, dfn[u], x);
}

int main() {
    n = gi;
    rep(i, 1, n - 1) {
	int u = gi, v = gi;
	addEdge(u, v);
	addEdge(v, u);
    }
    rep(i, 1, n) v[i] = gi;
    treediv();
    int Q = gi;
    char C[10];
    while (Q--) {
	int a, b;
	scanf("%s %d %d", C, &a, &b);
	if (C[1] == 'M') {
	    printf("%d\n", QueryPath(a, b).mx);
	} else if (C[1] == 'S') {
	    printf("%d\n", QueryPath(a, b).sm);
	} else {
	    changev(a, b);
	}
    }
    return 0;
}

