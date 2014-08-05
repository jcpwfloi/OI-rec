#include<cstdio>
#include<algorithm>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)

using namespace std;

int u[100001], n, ans = 0;

int calc(int x) {
    int ret = 1;
    for (int i = 2; i * i <= x; ++ i)
	if (x % i == 0) {
	    x /= i;
	    ret *= -1;
	    if (x % i == 0) return 0;
	}
    if (x != 1) ret *= -1;
    return ret;
}

int main() {
    rep(i, 1, 50000) u[i] = u[i - 1] + calc(i);
    scanf("%d", &n);
    int len, a, b, d;
    rep(i, 1, n) {
	scanf("%d%d%d", &a, &b, &d);
	if (a > b) swap(a, b);
	a /= d; b /= d; ans = 0;
	rep(pos, 1, a) {
	    len = min(a/(a/pos), b/(b/pos)) - pos;
	    ans += (a / pos) * (b / pos) * (u[pos + len] - u[pos - 1]);
	    pos += len;
	}
	printf("%d\n", ans);
    }
    return 0;
}

