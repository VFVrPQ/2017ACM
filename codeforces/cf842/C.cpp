/*
    author : VFVrPQ
    problem : cf842-C, 给定一棵树(n<=2e5)，根为1，问i节点到根的路径上，除去一个点或者不除去，gcd最大是多少
    solve : 树形dp.dp[i][2]，0表示不除去，1表示已经除去了一个点，转移即可
    time : 2017-09-03-17.45.57
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 2e5+10;

int a[N];
int dp[N][2];
vector<int>V[N];
vector<int>W[N];
int b[N];
int re[N],h;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
void dfs(int u,int fa=-1){
    for (auto v:V[u]){
        if (v==fa)continue;
        dp[v][0] = gcd(dp[u][0],a[v]);

        dp[v][1] = dp[u][0];

        for (auto w:W[u]){
            int tmp = gcd(w,a[v]);
            if (!b[tmp]){
                b[tmp] = 1;
                re[h++] = tmp;
                W[v].push_back(tmp);
                dp[v][1] =max(dp[v][1],tmp);
            }
        }
        if (!b[ dp[u][0] ]){
            W[v].push_back(dp[u][0]);
        }
        while (h){
            h--;b[re[h]] =0;
        }
        //dp[v][1] = max(dp[u][0],gcd(dp[u][1],a[v]));//
        dfs(v,u);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++)scanf("%d",&a[i]);
    for (int i=0;i<n-1;i++){
        int x,y;scanf("%d%d",&x,&y);x--;y--;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dp[0][0]=a[0];
    W[0].push_back(0);
    dfs(0);
    for (int i=0;i<n-1;i++){
        printf("%d ",max(dp[i][0],dp[i][1]));
    }
    printf("%d\n",max(dp[n-1][0],dp[n-1][1]));
    return 0;
}
