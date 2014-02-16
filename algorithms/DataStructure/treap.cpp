#include<cstdio>
#include<algorithm>

using namespace std;

namespace treap {
	struct Node {
		Node* ch[2];
		int r, v;
		inline int cmp(int x) {
			if (x == v) return -1;
			return x < v ? 0 : 1;
		}
		Node(int v) : v(v) {
			r = rand();
			ch[0] = ch[1] = NULL;
		}
	};

	inline void Rotate(Node* &o, int d) {
		Node* k = o -> ch[d^1];
		o -> ch[d^1] = k -> ch[d];
		k -> ch[d] = o;
		o = k;
	}

	inline void Insert(Node* &o, int x) {
		if (o == NULL) o = new Node(x);
		else {
			int d = o -> cmp(x);
			Insert(o -> ch[d], x);
			if (o -> ch[d] -> r > o -> r) Rotate(o, d^1);
		}
	}

	inline void Remove(Node*&o, int x) {
		int d = o -> cmp(x);
		if (d == -1) {
			if (o -> ch[0] == NULL) o = o -> ch[1];
			else if (o -> ch[1] == NULL) o = o -> ch[0];
			else {
				int d2 = (o -> ch[0] -> r > o -> ch[1] -> r ? 1 : 0);
				Rotate(o, d2);
				Remove(o -> ch[d2], x);
			}
		} else Remove(o -> ch[d], x);
	}
}

int main(){
	return 0;
}
