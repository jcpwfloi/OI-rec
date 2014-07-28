#include<cstdio>
#include<algorithm>
#define gi gI()
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define repD(i, r, l) for (int i = r; i >= l; -- i)

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

int const MAXN = 2000001;

int n, m;
int col[10001], lab[10001];
int first[MAXN], nex[MAXN], to[MAXN];
int cnt = 0, ans = 0;

inline void addEdge(int u, int v) {
    nex[++cnt] = first[u];
    first[u] = cnt;
    to[cnt] = v;
}

int main() {
    n = gi, m = gi;
    rep(i, 1, m) {
	int u = gi, v = gi;
	addEdge(u, v);
	addEdge(v, u);
    }
    repD(i, n, 1) {
	int k = 0;
	rep(j, 1, n) if (!lab[j] && col[j] >= col[k]) k = j;
	lab[k] = i;
	for (int j = first[k]; j; j = nex[j]) {
	    int v = to[j];
	    if (!lab[v]) ans = max(ans, ++col[v]);
	}
    }
    printf("%d\n", ans + 1);
    return 0;
}

