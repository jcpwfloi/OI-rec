#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define maxn 50001

using namespace std;

int n, m;
int M;

struct Query {
    int l, r;
    long long ans;
    bool operator < (Query &x) {
	if (this -> l / M == x.l / M) return this -> r < x.r;
	return this -> l / M < x.l / M;
    }
};

long long C[50001];
int A[maxn];
int numof[maxn];
Query Querys[maxn];
int id[maxn];
int nowl, nowr;
long long ans = 0;

inline void getC() {
    for (int i = 1; i <= 50000; i++) {
	C[i] = C[i - 1] + i - 1;
    }
}

inline bool comp(int i, int j) {
    return Querys[i] < Querys[j];
}

inline void init(int x) {
    memset(numof, 0, sizeof(numof));
    ++numof[A[x]];
    nowl = nowr = x;
    ans = 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("2038.in", "r", stdin);
    freopen("2038.out", "w", stdout);
#endif
    getC();
    scanf("%d%d", &n, &m);
    M = sqrt(n + 0.0);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= m; i++) {
	int l, r;
	scanf("%d%d", &l, &r);
	Querys[i] = (Query){l, r, 0};
	id[i] = i;
    }
    sort(id + 1, id + m + 1, comp);
    Querys[0].l = -10000;
    for (int k = 1; k <= m; k++) {
	int i = id[k];
	if (Querys[i].l / M != Querys[id[k - 1]].l / M) {
	    init(Querys[i].l);
	}
	while (nowr < Querys[i].r) {
	    ++nowr;
	    ans -= C[numof[A[nowr]]];
	    ++numof[A[nowr]];
	    ans += C[numof[A[nowr]]];
	}
	    while (nowl < Querys[i].l) {
		ans -= C[numof[A[nowl]]];
		--numof[A[nowl]];
		ans += C[numof[A[nowl]]];
		++nowl;
	    }
	    while (nowl > Querys[i].l) {
		--nowl;
		ans -= C[numof[A[nowl]]];
		++numof[A[nowl]];
		ans += C[numof[A[nowl]]];
	    }
	//if (k == 1) printf("ans: %d\n", ans);
	Querys[i].ans = ans;
    }
    for (int i = 1; i <= m; i++) {
	long long divisee = Querys[i].ans, divisor = C[Querys[i].r - Querys[i].l + 1];
	if (divisee == 0 || divisor == 0) printf("0/1\n");
	else {
	    long long gcd = __gcd(divisee, divisor);
	    divisee /= gcd;
	    divisor /= gcd;
	    printf("%lld/%lld\n", divisee, divisor);
	}
    }
    return 0;
}

