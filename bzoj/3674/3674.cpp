#include<cstdio>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstring>
#define rep(i, l, r) for (int i = l; i <= r; ++ i)

using namespace std;

typedef long long ll;

struct node {
    int l, r, v;
    int lson, rson;
};

int const MAXN = 400001;

node T[MAXN * 20];
int tot = 0;
int t[MAXN], optme[MAXN];
int n, m, nowtme;

int build(int l, int r) {
    int u = ++tot;
    T[u].l = l, T[u].r = r;
    if (l == r) {
	T[u].v = l;
	return u;
    }
    int m = (l + r) >> 1;
    T[u].lson = build(l, m);
    T[u].rson = build(m + 1, r);
    return u;
}

void modify(int lu, int &ru, int x, int v) {
    ru = ++tot;
    T[ru].l = T[lu].l, T[ru].r = T[lu].r;
    int m = (T[ru].l + T[ru].r) >> 1;
    if (T[lu].l == T[lu].r) {
	T[ru].v = v;
	return;
    }
    if (x <= m) {
	T[ru].rson = T[lu].rson;
	modify(T[lu].lson, T[ru].lson, x, v);
    } else {
	T[ru].lson = T[lu].lson;
	modify(T[lu].rson, T[ru].rson, x, v);
    }
}

void modify(int tme, int x, int v) { //A[x] = v
    t[tme] = ++tot;
    modify(t[tme - 1], t[tme], x, v);
}

int query(int u, int x) {
    int l = T[u].l, r = T[u].r;
    if (l == r) return T[u].v;
    int m = (l + r) >> 1;
    if (x <= m) return query(T[u].lson, x); else return query(T[u].rson, x);
}

int querytme(int tme, int x) {
    return query(t[tme], x);
}

int p(int x) {
    return querytme(nowtme, x);
}

void mdf(int x, int v) {
    modify(++nowtme, x, v);
}

int find(int u) {
    //return p[u] == u ? u : p[u] = find(p[u]);
    if (p(u) == u) return u;
    else {
	mdf(u, find(p(u)));
	return p(u);
    }
}

void travel(int x) {
    t[++nowtme] = t[optme[x]];
}

void merge(int a, int b) {
    //p[find(a)] = find(b);
    mdf(find(a), find(b));
}

int main() {
    int lastans = 0;
    scanf("%d%d", &n, &m);
    build(1, n);
    t[1] = 1;
    optme[0] = ++nowtme;
    rep(i, 1, m) {
	int op;
	scanf("%d", &op);
	if (op == 1) {
	    int a, b;
	    scanf("%d%d", &a, &b);
	    a ^= lastans;
	    b ^= lastans;
	    merge(a, b);
	} else if (op == 2) {
	    int x;
	    scanf("%d", &x);
	    x ^= lastans;
	    travel(x);
	} else if (op == 3) {
	    int a, b;
	    scanf("%d%d", &a, &b);
	    a ^= lastans;
	    b ^= lastans;
	    if (find(a) == find(b)) puts("1"), lastans = 1; else puts("0"),lastans = 0;
	}
	optme[i] = nowtme;
    }
    return 0;
}

