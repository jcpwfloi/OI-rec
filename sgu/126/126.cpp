#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

int a, b;

int main() {
    scanf("%d%d", &a, &b);
    if (!a || !b) {
	puts("0");
	return 0;
    }
    double temp = (a + b) / __gcd(a, b);
    if ((int)(log10(temp) / log10(2)) == log10(temp) / log10(2)) printf("%d\n", (int)(log10(temp) / log10(2))); else puts("-1");
    return 0;
}

