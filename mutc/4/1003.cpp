#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int M = 998244353;

const int N = 1e6+10;
LL a[N],d[N],b[N];
int main(){
    int Case;scanf("%d",&Case);
    LL L,R,K;
    while (Case--){
        scanf("%lld%lld%lld",&L,&R,&K);

        for (LL i=L;i<=R;i++){
                a[i-L]=i;
                d[i-L]=1;
        }
        for (LL i=2;i*i<=R;i++) b[i]=0;

        for (LL i=2;i*i<=R;i++){
            if (b[i])continue;
            for (LL j=i+i;j*j<=R;j+=i){
                b[j]=1;
            }
            for (LL j = (L+i-1)/i*i;j<=R;j+=i)
            if (a[j-L]%i==0){
                LL cnt=0;
                while (a[j-L]%i==0){
                    cnt++;
                    a[j-L]/=i;
                }
                d[j-L]=d[j-L]*(cnt*K+1)%M;

            }
        }

        LL ans=0;
        for (LL i=L;i<=R;i++){
            if (a[i-L]>1){
                d[i-L]=d[i-L]*(K+1)%M;
            }
            ans=(ans+d[i-L])%M;
        }
        printf("%lld\n",ans);
    }
	return 0;
}
