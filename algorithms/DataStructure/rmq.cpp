#include<cstdio>
#include<algorithm>
#define maxn 100001

using namespace std;

int A[maxn];
int F[maxn][21];
int n;

namespace RMQ {
	inline void init() {
		for (int i = 1; i <= n; i++) F[i][0] = A[i];
		for (int k = 1; (1 << k) <= n; k++)
			for (int i = 1; i - 1 + (1 << k) <= n; i++) {
				F[i][k] = min(F[i][k - 1], F[i + (1 << (k - 1))][k - 1]);
			}
	}
	inline int Query(int l, int r) {
		int pow;
		for (pow = 0; (1 << pow) <= (r - l + 1)/2; pow++) ;
		return min(F[l][pow], F[r - (1 << pow) + 1][pow]);
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
	return 0;
}
