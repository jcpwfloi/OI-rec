#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 1010
using namespace std;
typedef long long LL;
LL F[MAXN][MAXN];
int n,prime[MAXN],tot;
bool mark[MAXN];
void ptm()
{
    for(int i=2;i<=1000;i++)
	        {
		            if(mark[i]==false)  prime[++tot]=i;
			            for(int j=1;j<=tot&&prime[j]*i<=1000;j++)
					        {
						                mark[prime[j]*i]=true;
								            if(i%prime[j]==0)  break;
									            }
				        }
}
void Dp()
{
        for(int i=0;i<=tot;i++)
	            F[i][0]=1;
	    for(int i=1;i<=n;i++)
		        F[0][i]=1;
	        for(int i=1;i<=tot;i++)
		            for(int j=1;j<=n;j++)
				        {
					                F[i][j]=F[i-1][j];
							            for(int k=prime[i];k<=j;k*=prime[i])
									                F[i][j]+=F[i-1][j-k];
								            }
}
int main()
{
    scanf("%d",&n);
    ptm();
    Dp();
    printf("%lld\n",F[tot][n]);
    return 0;
}
