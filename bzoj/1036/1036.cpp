#include<cstdio>
#include<algorithm>
#include<cstring>
#define T_MAX 120001
#define maxn 30001
#define maxm 30001
#define lson u << 1
#define rson u << 1 | 1
#define gi gI()
#define gs gS()
#define rep(i, l, r) for (int i = l; i <= r; i++)

using namespace std;

typedef long long ll;

inline ll gI() {
    int flag = 1, p = 0;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    while ('0' <= c && c <= '9') p = p * 10 + (c - '0'), c = getchar();
    return p * flag;
}

inline char* gS() {
    int cnt = 0;
    char *temp;
    char c = getchar();
    while (c == ' ' || c == '\n' || c == '\r') c = getchar();
    temp = new char[10];
    while (c != '\n' && c != ' ' && c != '\r') temp[cnt++] = c, c = getchar();
    return temp;
}

int first[maxn], nex[maxm], to[maxm], w[maxn], s[maxn];
int D[maxn], p[maxn];
int son[maxn], n, q;
int dfn[maxn];
int top[maxn];
int cnt = 0, depth = 0;

namespace sgt {
    struct ifo {
	int max, sum;
	ifo () : max(~0x7FFFFFFF), sum(0) {}
	ifo (int v) : max(v), sum(v) {}
	ifo (int max, int sum) : max(max), sum(sum) {}
	ifo merge(ifo x) {
	    return ifo(std::max(max, x.max), x.sum + sum);
	}
	void add(int C) {
	    max += C;
	    sum += C;
	}
    };
    struct Node {
	int L, R, tag;
	ifo info;
    } T[T_MAX];
    inline void Update(int u) {
	T[u].info = T[lson].info.merge(T[rson].info);
    }
    inline void Edit(int u, int x, int C) {
	if (T[u].L == T[u].R) {
	    T[u].info = ifo(C);
	    return;
	}
	if (x <= T[lson].R) Edit(lson, x, C); else Edit(rson, x, C);
	Update(u);
    }
    inline ifo Query(int u, int L, int R) {
	if (L <= T[u].L && T[u].R <= R) {
	    return T[u].info;
	}
	ifo ans;
	if (L <= T[lson].R) ans = ans.merge(Query(lson, L, R));
	if (R >= T[rson].L) ans = ans.merge(Query(rson, L, R));
	return ans;
    }
    inline void Build(int u, int L, int R) {
	T[u].L = L;
	T[u].R = R;
	if (L == R) {
	    T[u].info = ifo(0);
	    return;
	}
	int M = (L + R) >> 1;
	Build(lson, L, M);
	Build(rson, M + 1, R);
	Update(u);
    }
}

namespace treed {
    inline void addEdge(int u, int v) {
	nex[++cnt] = first[u];
	first[u] = cnt;
	to[cnt] = v;
    }
    inline void dfs1(int u, int father) {
	s[u] = 1;
	p[u] = father == -1 ? 1 : father;
	int maxs = 0, maxnum = 0;
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
    inline void dfs2(int u, int father) {
	D[u] = father != -1 ? D[father] + 1 : 1;
	dfn[u] = ++depth;
	if (!top[u]) top[u] = u;
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
    void readTree() {
	n = gi;
	sgt::Build(1, 1, n);
	rep(i, 1, n - 1) {
	    int u = gi, v = gi;
	    addEdge(u, v);
	    addEdge(v, u);
	}
	rep(i, 1, n) {
	    w[i] = gi;
	    sgt::Edit(1, dfn[i], w[i]);
	}
	dfs1(1, -1);
	dfs2(1, -1);
    }
    sgt::ifo getInfo(int u, int v) {
	sgt::ifo ans;
	while (top[u] != top[v]) {
	    int compu = top[u] == u ? p[u] : top[u];
	    int compv = top[v] == v ? p[v] : top[v];
	    if (D[compu] < D[compv]) swap(u, v);
	    else {
		if (D[compu] == D[compv] && D[u] < D[v]) swap(u, v);
	    }
	    if (u != top[u]) {
		ans.merge(sgt::Query(1, dfn[top[u]] + 1, dfn[u]));
		printf("Call sgt::Query(1, %d, %d) = {%d, %d}\n", dfn[top[u]] + 1, dfn[u], sgt::Query(1, dfn[top[u]] + 1, dfn[u]).max, 0);
		u = top[u];
	    } else {
		ans.merge(sgt::ifo(w[u]));
		u = p[u];
	    }
	}
	if (D[u] < D[v]) swap(u, v);
	if (u == v) {
	    ans.merge(sgt::ifo(w[top[u]]));
	    return ans;
	} else {
	    ans.merge(sgt::Query(1, dfn[v], dfn[u]));
	    return ans;
	}
    }
    int QMAX(int u, int v) {
	return getInfo(u, v).max;
    }
    int QSUM(int u, int v) {
	return getInfo(u, v).sum;
    }
    void CHANGE(int x, int C) {
	sgt::Edit(1, dfn[x], C);
    }
    void work() {
	q = gi;
	rep(i, 1, q) {
	    char *cmdt;
	    cmdt = gs;
	    int u = gi, v = gi;
	    if (cmdt[1] == 'M') { //QMAX
		printf("%d\n", QMAX(u, v));
	    } else if (cmdt[0] == 'C') { //CHANGE
		CHANGE(u, v);
	    } else if (cmdt[1] == 'S') { //QSUM
		printf("%d\n", QSUM(u, v));
	    }
	}
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1036.in", "r", stdin);
    //freopen("1036.out", "w", stdout);
#endif
    treed::readTree();
    treed::work();
    return 0;
}

