#include <cstdio>
#include <cstring>
#define maxn 4000000

int now, i, j , k , l , m ,n , e , a, b;
int v[maxn], first[maxn], next[maxn], ans[maxn];
int fa[maxn], que[maxn];;
int done[maxn], die[maxn];

int find(int a){
    if (fa[a] == a) return a;
    else return fa[a] = find(fa[a]);
}

void build(int a, int b){
    next[++e] = first[a];
    first[a] = e; v[e] = b;
    next[++e] = first[b];
    first[b] = e; v[e] = a;
}

void bfs(int a,int f){
    int i, j, t, w;
    t = 1, w = 1, que[1] = a, fa[a]=f;
    while (t <= w){
        for(i = first[que[t]]; i ; i = next[i]){
            if ((!done[v[i]]) && (!fa[v[i]])) {
                que[++w] = v[i];
                fa[v[i]] = f;
            }
        }
        t++;
    }
}

void merge(int a){
    int i,j,t;
    fa[a] = a;
    for(t = first[a]; t ; t = next[t]){
        if ((!done[v[t]]) && (fa[a]!=find(v[t]))){
            now--, j = fa[v[t]]; fa[j] = fa[a];
        }
    } now++;
}

int main(){
    scanf("%d %d",&n, &m);
    for(i = 1; i <= m; i++){
        scanf("%d %d", &a, &b);
        build(a+1, b+1);
    }
    scanf("%d", &m);
    for(i = 1; i <= m; i++){
        scanf("%d", &die[i]);
        die[i]++, done[die[i]]=1;
    }
    memset(fa, 0, sizeof(fa));
    now = 0;
    for(i = 1; i <= n; i++){
        if ((!done[i]) && (!fa[i])){
            bfs(i, i);
            now++;
        }
    }
    ans[m+1] = now;
    for(j = m; j >= 1; j--){
        k = die[j], done[k] = 0;
        merge(k);
        ans[j] = now;
    }
    for(i = 1; i <= m+1; i++) printf("%d\n",ans[i]);
    return 0;
}

