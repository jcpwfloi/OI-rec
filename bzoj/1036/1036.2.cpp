#include<cstdio>
#include<algorithm>

using namespace std;

namespace sgt {
    struct Node {
	int L, R, min, max;
    } T[T_MAX];
    inline void Update(int u) {
	T[u].min = min(T[lson].min, T[rson].min);
    }
    inline void Cover(int u, int C) {
	T[u].min += C;
	T[u].tag += C;
	T[u].max += C;
    }
    inline void Push(int u) {
    }
}

int main() {
    return 0;
}

