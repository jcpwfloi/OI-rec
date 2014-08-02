#include<cstdio>
#include<algorithm>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define gi gI()
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

int n;

int const T_MAX = 400001;

struct Node {
    int L, R;
    bool h0, h1, v0, v1, c0, c1;
} T[T_MAX];

inline void Update(int u) {
    T[u].h0 = (T[lson].h0 && T[rson].h0) || (T[lson].c1 && T[rson].c0) ? 1 : 0;
    T[u].h1 = (T[lson].h1 && T[rson].h1) || (T[lson].c0 && T[rson].c1) ? 1 : 0;
    T[u].v0 = (T[lson].v0) || (((T[lson].h0 && T[lson].h1) || (T[lson].c0 && T[lson].c1)) && T[rson].v0) ? 1 : 0;
    T[u].v1 = (T[rson].v1) || (((T[rson].h0 && T[rson].h1) || (T[rson].c0 && T[rson].c1)) && T[lson].v1) ? 1 : 0;
    T[u].c0 = (T[lson].c0 && T[lson].h0) || (T[lson].h1 && T[rson].c0) ? 1 : 0;
    T[u].c1 = (T[lson].h0 && T[rson].c1) || (T[lson].c1 && T[rson].h0) ? 1 : 0;
}

inline void Cover(int u, int C){
}

void Edit(int u, int x, int C) {
    if (L == R) {
	Cover(u, C);
	return;
    }
    if (x <= T[lson].R) Edit(lson, x, C); else Edit(rson, x, C);
    Update(u);
}

int Query(int u, int L, int R, int op) {
}

void Build(int u, int L, int R) {
}

int main() {
    n = gi;
    return 0;
}

