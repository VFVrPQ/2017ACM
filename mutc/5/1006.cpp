#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        LL n,m;scanf("%lld%lld",&n,&m);

        if (m<n-1){
            printf("%lld\n",2*(m*m+n*(n*(n-1)/2-m-m*(m-1)/2)));
        }else
        if (m<n*(n-1)/2){
            printf("%lld\n",2*(n*(n-1)-m));
        }else{
            printf("%lld\n",n*(n-1));
        }
    }
    return 0;
}
