/*
    author : VFVrPQ
    problem :
    solve :
    time :
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int a[N];
int b[N];
int c[N];
LL sum1[N],sum2[N];
int newb[N],newc[N];
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG

    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    //b[i],c[i]
    a[n+1]=0;
    for (int i=n;i>=1;i--){
        b[i]=max(b[i+1]+1,a[i+1]+1);
        if (a[i]>=b[i]) c[i]=0;
        else c[i]=b[i]-a[i];

        sum1[i]=c[i]+sum1[i+1];
    }
    newb[1]=1;
    newc[1]=0;
    for (int i=2;i<=n;i++){
        newb[i] = max(newb[i-1]+1,a[i-1]+1);
        if (a[i]>=newb[i]) newc[i]=0;
        else newc[i]=newb[i]-a[i];

        sum2[i]=newc[i]+sum2[i-1];
    }

    LL ans=1LL<<60;
    for (int i=1;i<=n;i++){
        LL now = sum1[i+1]+sum2[i-1];

        int Max = max(newb[i],b[i]);
        if (a[i]<Max) now+=Max-a[i];

        ans=min(ans,now);
    }
    cout<<ans<<endl;
    return 0;
}
