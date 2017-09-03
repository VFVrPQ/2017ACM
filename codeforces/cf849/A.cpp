/*
    author : VFVrPQ
    problem : cf849-A 水题。
    solve : 直接判断头尾和总长度是不是奇数就可以了（虽然我写了个dp还没过）
    time : 2017-09-03-17.23.00
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 100+10;

int n,a[N];
int dp[N][2][2];
int main(){
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    if (n%2==1 && a[0]%2==1 && a[n-1]%2==1){
        puts("YES");
    }else{
        puts("NO");
    }
    //dp[0][0]=1;
    //dp[0][1]=0;
    /*if (a[1]&1){
        dp[1][1][1]=1;
    }else {
        puts("NO");
        return 0;
    }
    for (int i=2;i<=n;i++){
        if (a[i]&1){
            dp[i][1][0] |= dp[i-1][1][1];
            dp[i][1][1] |= dp[i-1][1][0];

            dp[i][1][0] |= dp[i-1][0][0];
            dp[i][1][1] |= dp[i-1][0][1];

            dp[i][0][0] |= dp[i-1][1][0];
            dp[i][0][1] |= dp[i-1][1][1];
        }else {
            dp[i][1][0] |= dp[i-1][0][0];
            dp[i][1][1] |= dp[i-1][0][1];

            dp[i][0][0] |= dp[i-1][1][0];
            dp[i][0][1] |= dp[i-1][1][1];
        }
    }

    //for (int i=1;i<=n;i++) printf("%d %d\n",dp[i][0],dp[i][1]);
    if (dp[n][1][1] && (a[n]&1))puts("YES");
    else puts("NO");*/
    return 0;
}
