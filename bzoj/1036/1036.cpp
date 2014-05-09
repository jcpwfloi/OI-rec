#include<cstdio>
#include<algorithm>
#define T_MAX 120001
#define maxn 30001
#define maxm 30001
#define lson u << 1
#define rson u << 1 | 1
#define gi gI()
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

int first[maxn], nex[maxm], to[maxm], w[maxn], s[maxn];

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
/*
namespace treed {
    inline void addEdge(int u, int v) {
	nex[++cnt] = first[u];
	first[u] = cnt;
	to[cnt] = v;
    }
    inline void dfs1(int u, int father) {
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
    inline void dfs2(int u, int father) {
    }
    void readTree() {
	n = gi;
	rep(i, 1, n - 1) {
	    int u = gi, v = gi;
	    addEdge(u, v);
	    addEdge(v, u);
	}
	rep(i, 1, n) w[i] = gi;
    }
    void work() {
    }
}*/

int main() {
    //treed::readTree();
    //treed::work();
    return 0;
}

