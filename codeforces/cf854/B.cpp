/*
    author : VFVrPQ
    problem : cf854-B,水题
    solve : 算一算得出结论，但要注意3*K超过int
    time : 2017-09-08-20.39.55
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    LL n,K;
    cin>>n>>K;

    printf("%d ",((K==n || K==0)? 0 : 1));
    //if (n>=3*K) puts("YES");
    printf("%d\n",((n>=3*K)? 2*K : n-K));
    return 0;
}
