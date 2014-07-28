#include<cstdio>
#include<algorithm>
#define gi gI()
#define rep(i, l, r) for (int i = l; i <= r; ++ i)

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

int n;
int A[1001];

int main() {
    n = gi;
    rep(i, 1, n) A[i] = gi;
    return 0;
}

