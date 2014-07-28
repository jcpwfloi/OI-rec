#include <iostream>
#include <cstring>
#include <cstdlib> 
#include <cstdio>
#include <algorithm>

#define INF 1e9

using namespace std;

int n,m,gs;

inline double dfs(double x,double y,int cnt) {
    if (cnt==1) return max(x/y,y/x);
    double rt=INF;
    for(int i=1;i<=(cnt>>1);i++) {
	rt=min(rt,max(dfs(x/cnt*i,y,i),dfs(x/cnt*(cnt-i),y,cnt-i)));
	rt=min(rt,max(dfs(x,y/cnt*i,i),dfs(x,y/cnt*(cnt-i),cnt-i)));
    }
    return rt;
}

inline void go() {
    scanf("%d%d%d",&n,&m,&gs);
    double ans=dfs(n,m,gs);
    printf("%.6lf\n",ans);
}

int main() {
        go();
	    return 0;
}
