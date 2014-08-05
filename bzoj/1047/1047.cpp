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

int const MAXN = 1001;

template <class T>

struct queue {
    T data[MAXN];
    int st, en;
    queue() {
	st = en = 0;
	memset(data, 0, sizeof(data));
    }
    void push_back(T x) {
	data[en++] = x;
    }
    void pop_front() {
	++st;
    }
    void pop_back() {
	--en;
    }
    T front() {
	return data[st];
    }
    T back() {
	return data[en - 1];
    }
    bool empty() {
	return st + 1 < en;
    }
};

int a, b, n;
int A[MAXN][MAXN];
int st[MAXN], en[MAXN];
queue<int> q1[MAXN]/*min*/, q2[MAXN];

int main() {
    a = gi, b = gi, n = gi;
    rep(i, 1, a) rep(j, 1, b) A[i][j] = gi;
    rep(j, 1, n) rep(i, 1, n) {
	int d = A[i][j];
	while (!q1[j].empty() && q1[j].back() >= d) q1[j].pop_back();
    }
    return 0;
}

