/*
    author : VFVrPQ
    problem : cf851-D, n(n<=5e5)个数,通过下面两种操作将其变成空或者gcd>1的最小代价
                1.删除一个数，花费x
                2.一个数加1(可以加无限次)，花费y
    solve : 还是筛法的模板啊，只要跟gcd有关的就可以套筛法。枚举gcd, (kd,(k+1)*d]这个区间分成前后两段，前一段用删数，后一段+1,前缀和统计。
            我比赛的时候d=5时,3,4都只加了1次,可能脑子混了。过了pp，但wa了。
    time : 2017-09-05-18.36.28
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e6+10;

LL num[N],a[N];

int main(){
    int maxx=0;
    int n;LL X,Y;
    cin>>n>>X>>Y;
    for (int i=0;i<n;i++){
        int x;scanf("%d",&x);num[x]++;
        maxx =max(maxx,x);
    }
    for (int i=1;i<N;i++) {
            a[i]=num[i]*i+a[i-1];
            num[i]=num[i]+num[i-1];
    }

    LL ans = X*n;
    for (int d=2;d<=1000000;d++){
        LL now=0;
        for (int k=0;k*d<maxx;k++){
            //(kd,(k+1)d]

            //+1
            int L = max((LL)k*d,(k+1)*d-(X/Y)-1);
            LL gs  = (num[(k+1)*d-1]-num[L]);
            LL gs2 = (num[(k+1)*d-1]-num[k*d]);
            now+=(LL)(gs*(k+1)*d-(a[(k+1)*d-1]-a[L]))*Y;
            now+=(LL)(gs2-gs)*X;
        }
        if (now<ans){
                ans=now;
               // cout<<d<<" "<<ans<<endl;
        }
    }
    cout<<ans;
    return 0;
}
