#include <iostream>
#include <cstring>
#include <cmath>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
using namespace std;

int T;
typedef long long LL;

int a[33],t[33];
LL dp[33][33][2];
LL dfs(int len,int cur,int s,int fp,int y)
{
    if(!cur)
        return s?y:1;
    if(!fp && dp[len][cur][s] != -1)
        return dp[len][cur][s];
    int n = fp?a[cur]:y-1;
    LL res = 0;
    for(int i=0;i<=n;i++)
    {
        t[cur] = i;
        if(len == cur && i == 0)
            res += dfs(len-1,cur-1,s,fp&&i==n,y);
        else if(s && cur <= (len+1)/2)
            res += dfs(len,cur-1,t[len-cur+1]==i,fp&&i==n,y);
        else
            res += dfs(len,cur-1,s,fp&&i==n,y);
    }
    if(!fp)
        dp[len][cur][s] = res;
    return res;
}
LL sum(LL x,LL y)
{
    int len = 0;
    while(x)
    {
        a[++len] = x % y;
        x /= y;
    }

    //printf("len=%d\n",len);
    return dfs(len,len,1,1,y);
}

const int N = 1e5+10;
LL L[N],R[N],l[N],r[N],ans[N];
int main()
{
    int Ca=1;
    scanf("%d",&T);

    for (int ca=1;ca<=T;ca++){
        scanf("%I64d%I64d%I64d%I64d",&L[ca],&R[ca],&l[ca],&r[ca]);
    }

    for (int i=2;i<=36;i++){
        memset(dp,-1,sizeof dp);
        for (int ca=1;ca<=T;ca++)if (l[ca]<=i && i<=r[ca]){
            ans[ca]+=sum(R[ca],i)-sum(L[ca]-1,i);
        }
    }
    for (int ca=1;ca<=T;ca++){
         printf("Case #%d: %I64d\n",ca,ans[ca]);
    }
    return 0;
}
