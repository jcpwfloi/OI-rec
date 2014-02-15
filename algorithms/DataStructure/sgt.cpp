#include<cstdio>
#include<algorithm>

using namespace std;

namespace sgt {
	struct Node {
		int L, R, min, tag;
	} T[T_MAX];

	inline void Update(int u) {
		T[u].min = min(T[lson].min, T[rson].min);
	}

	inline void Cover(int u, int C) {
		T[u].min += C;
		T[u].tag += C:
	}

	inline void Push(int u) {
		if (T[u].tag) {
			Cover(lson, T[u].tag);
			Cover(rson, T[u].tag);
		}
	}
	
	inline int Query(int u, int L, int R) {
		if (L <= T[u].L && T[u].R <= R) {
			return T[u].min;
		}

		Push(u);

		int ans = 0x7FFFFFFF;
		
		if (L <= T[lson].R) ans = min (ans, Query(lson, L, R));
		if (R >= T[rson].L) ans = min (ans, Query(rson, L, R));

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
			T[u].min = A[L];
			return;
		}

		int M = (L + R) >> 1;

		Build(lson, L, M);
		Build(rson, M+1, R);

		Update(u);
	}
}

int main(){
	return 0;
}

