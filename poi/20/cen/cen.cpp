#include<cstdio>
#include<algorithm>
#include<queue>
#define maxn 100001
#define maxm 100001

using namespace std;

int first[maxn], nex[maxn], to[maxm], D[maxn];
int n, m, a, b, k;
int cnt = 0;

queue<int> Q;

void addEdge(int u, int v) {
    nex[++cnt] = first[u];
    first[u] = cnt;
    to[cnt] = v;
}

void BFS(int S) {
    memset(D, 0, sizeof(D));
    D[S] = 1;
    Q.push(S);
    while (!Q.empty()) {
	int u = Q.front(); Q.pop();
	for (int i = first[u]; i; i = nex[i]) {
	    int v = to[i];
	    if (!D[v]) {
		D[v] = D[u] + 1;
		Q.push(v);
	    }
	}
    }
}

void work() {
    BFS(k);
    for (int i = 1; i <= n; i++) {
	int dist = D[i] - 1;
	if (!dist) {
	    puts("0");
	    continue;
	} else {
	    int ans = 0;
	    if ((dist & 1) == 1) {
		ans += a;
		--dist;
	    }
	    if (b < 2 * a) {
		ans += b * dist / 2;
	    } else {
		ans += dist * a;
	    }
	    printf("%d\n", ans);
	}
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &k, &a, &b);
    for (int i = 1; i <= m; i++) {
	int u, v;
	scanf("%d%d", &u, &v);
	addEdge(u, v);
	addEdge(v, u);
    }
    work();
    return 0;
}

