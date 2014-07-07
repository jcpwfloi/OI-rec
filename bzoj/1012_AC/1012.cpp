#include<cstdio>
#include<algorithm>
#define lson u << 1
#define rson u << 1 | 1
#define INF 0x7FFFFFFF

using namespace std;

int M, D, len = 0, t = 0;

const int T_MAX = 600000;

namespace sgt {
	struct Node {
		int L, R, max, tag;
	} T[T_MAX];

	inline void Update(int u) {
		T[u].max = max (T[lson].max, T[rson].max);
	}

	inline void Cover(int u, int C) {
		T[u].max += C;
		T[u].tag += C;
	}

	inline void Push(int u) {
		if (T[u].tag) {
			Cover(lson, T[u].tag);
			Cover(rson, T[u].tag);
			T[u].tag = 0;
		}
	}

	inline int Query(int u, int L, int R) {
		if (L <= T[u].L && T[u].R <= R) {
			return T[u].max;
		}

		int ans = 0;

		Push(u);

		if (L <= T[lson].R) ans = max(ans, Query(lson, L, R));
		if (R >= T[rson].L) ans = max(ans, Query(rson, L, R));

		return ans;
	}

	inline void Edit(int u, int L, int R, int C) {
		if (L <= T[u].L && T[u].R <= R) {
			Cover(u, C);
			return;
		}

		Push(u);

		if (L <= T[lson].R) Edit(lson, L, R, C);
		if (R >= T[rson].L) Edit(rson, L, R, C);

		Update(u);
	}

	inline void Build(int u, int L, int R) {
		T[u].L = L;
		T[u].R = R;

		if (L == R) {
			T[u].max = 0;
			return;
		}

		int M = (L + R) >> 1;

		Build(lson, L, M);
		Build(rson, M+1, R);

		Update(u);
	}
}

int main(){
	scanf("%d %d\n", &M, &D);
	sgt::Build(1, 1, M);
	while (M--) {
		char cmdt;
		int v;
		scanf("%c %d\n", &cmdt, &v);
					//printf("%c %d\n", cmdt, v);
		if (cmdt == 'A') {
			int res = (v + t) % D;
			len ++;
			sgt::Edit(1, len, len, res);
						//printf("OK\n");
		} else if (cmdt == 'Q') {
			int res = sgt::Query(1, len-v+1, len);
			printf("%d\n", res);
			t = res;
		}
	}
	return 0;
}

