#include<cstdio>
#include<algorithm>

using namespace std;

int Q;

int Trailing(int n) {
    int cnt = 0;
    while (n) {
	cnt += n / 5;
	n /= 5;
    }
    return cnt;
}

int main() {
    scanf("%d", &Q);
    if (Q == 0) {
	puts("1");
	return 0;
    }
    else {
	int ans = 4 * Q / 5 * 5;
	while (Trailing(ans) < Q) ans += 5;
	if (Trailing(ans) == Q) printf("%d\n", ans);
	else printf("No solution\n");
    }
    return 0;
}

