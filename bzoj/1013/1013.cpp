#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<cmath> 
#include<algorithm> 
#define MAXN 20 
#define eps 1e-10 
using namespace std; 

typedef long long ll;
inline ll gI() {
    ll p = 0, flag = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    while ('0' <= c && c <= '9') p = p * 10 + (c - '0'), c = getchar();
    return p * flag;
}

int dcmp(double p) 
{ 
        if(fabs(p)<eps)  return 0; 
	    return p>eps?1:-1; 
} 
double a[MAXN][MAXN],b[MAXN],x[MAXN],P[MAXN][MAXN]; 
int n; 
void read() 
{ 
        scanf("%d",&n); 
	    for(int i=1;i<=n+1;i++) 
		        for(int j=1;j<=n;j++) 
			                scanf("%lf",&P[i][j]); 
	        for(int i=1;i<=n;i++) 
		            for(int j=1;j<=n;j++) 
				            a[i][j]=2*P[n+1][j]-2*P[i][j],b[i]=b[i]-P[i][j]*P[i][j]+P[n+1][j]*P[n+1][j]; 
} 
void Gauss() 
{ 
        for(int i=1,j;i<=n;i++) 
	        { 
		            for(j=i;!dcmp(a[j][i]);j++); 
			            swap(b[i],b[j]); 
				            for(int k=i;k<=n;k++) 
						            swap(a[i][k],a[j][k]); 
					            for(j=i+1;j<=n;j++) 
							            if(dcmp(a[j][i])) 
									            { 
											                double p=a[i][i]/a[j][i]; 
													                for(int k=i;k<=n;k++) 
															                        a[j][k]=a[i][k]-a[j][k]*p; 
															                b[j]=b[i]-b[j]*p; 
																	            } 
						        } 
	    for(int i=n;i>=1;i--) 
		    { 
			        for(int j=i+1;j<=n;j++) 
				                b[i]=b[i]-x[j]*a[i][j]; 
				        x[i]=b[i]/a[i][i]; 
					    } 
} 
void print() 
{ 
    for(int i=1;i<=n;i++) 
	printf("%.3lf%c",x[i],i<n?' ':'\n'); 
} 
int main() { 
        read(); 
    Gauss(); 
    print(); 
    return 0; 
}
