/*
    author : VFVrPQ
    problem : cf849-C, 简单的构造题，构造题目中公式=K的一种方案
    solve : 各个字符相互独立，且个数可算，搞一搞就好了。注意K=0,也要输出
    time : 2017-09-03-17.34.08
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

const int N = 100000+10;

int dp[N];
int last[N];
int main(){
    for (int i=0;i<N;i++) dp[i]=M;
    dp[0]=1;
    for (int i=1;i<N;i++){
        for (int j=1;j*(j-1)/2<=i;j++){
            if (dp[i]>dp[i-j*(j-1)/2]+1){
                dp[i]=dp[i-j*(j-1)/2]+1;
                last[i]=j;
            }
        }
    }

    int K,cnt=0;
    scanf("%d",&K);
    while (K){
        int tmp = last[K];
        for (int i=0;i<tmp;i++)printf("%c",'a'+cnt);cnt++;
        K = K - tmp*(tmp-1)/2;
    }
    printf("%c",'a'+cnt);
    return 0;
}
