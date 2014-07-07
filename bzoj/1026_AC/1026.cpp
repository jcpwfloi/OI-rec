#include<cstdio>
#include<algorithm>
#include<cstring>
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define repD(i, r, l) for (int i = r; i; i--)
#define gi gI()
#define abs(x) ((x) > 0 ? (x) : -(x))

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

int a, b;

int dp[12][10]; //f[i][j] i位数第1位是j多少个windy数
int bits[12];
int top = 0;

void init() {
    memset(dp, 0, sizeof(dp));
    rep(i, 0, 9) dp[1][i] = 1;
    rep(i, 2, 11)
	rep(j, 0, 9)
	    rep(k, 0, 9)
		if (abs(j - k) > 1) dp[i][j] += dp[i - 1][k];
}

void init(int x) {
    top = 0;
    for (; x; x /= 10)
	bits[++top] = x % 10;
}

int cal(int x) {
    int ans = 0;
    rep(i, 1, top - 1)
	rep(j, 1, 9) ans += dp[i][j];
    rep(i, 1, bits[top] - 1)
	ans += dp[top][i];
    repD(i, top - 1, 1) {
	rep(j, 0, bits[i] - 1)
	    if (abs(bits[i + 1] - j) > 1) ans += dp[i][j];
	if (abs(bits[i + 1] - bits[i]) < 2) break;
    }
    return ans;
}

int main() {
    a = gi, b = gi;
    init();
    init(a);
    int ansa = cal(a + 1);
    init(b);
    int ansb = cal(b);
    //printf("ansa=%d\n", ansa);
    //printf("ansb=%d\n", ansb);
    printf("%d\n", ansb - ansa);
    return 0;
}

