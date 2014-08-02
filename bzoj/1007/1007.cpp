#include<cstdio>
#include<algorithm>
#include<stack>
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

int const MAXN = 50001;

pair<pair<int, int>, int> A[MAXN];
stack<pair<pair<int, int>, int> > S;
stack<int> num;
int n;

int main() {
    n = gi;
    rep(i, 1, n) A[i].first.first = gi, A[i].first.second = gi, A[i].second = i;
    sort(A + 1, A + n + 1);
    rep(i, 1, n) {
	if (A[i].first.first == 0) {
	    continue;
	}
	if (S.empty()) {
	    S.push(A[i]);
	} else {
	    while ((int)S.size() >= 2) {
		pair<int, int> A2 = S.top().first;
		int temp2 = S.top().second;
		S.pop();
		pair<int, int> A1 = S.top().first;
		S.push(make_pair(A2, temp2));
		pair<int, int> A3 = A[i].first;
		if ((A3.second - A1.second) * (A2.first - A1.first) >= (A3.first - A1.first) * (A2.second - A1.second)) S.pop(); else break;
	    }
	    S.push(A[i]);
	}
    }
    while (!S.empty()) {
	num.push(S.top().second);
	S.pop();
    }
    while (!num.empty()) {
	printf("%d ", num.top());
	num.pop();
    }
    printf("\n");
    return 0;
}

