/*
    author : VFVrPQ
    problem : rqnoj 30,给一个矿洞和入口0，有n个岔道，从入口出发每个岔道必须留人（才能返回入口，并能挖取宝藏），给m个人，问最多可以挖多少宝藏
    solve : 树形依赖背包入门，O(nm),树形dp的时候dp当前节点u,将u的值传给son并必取son这个点，递归son，返回时将son和u的值合并（表示包含son这个子树和不包含son这个子树的合并）。
    time : 2017-11-06-20.08.31
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG
int dp[1111][111];
int n,m;
int a[1111];
vector<int> V[1111];
void dfs(int u,int fa,int m){
    if (m<=0) return ;
    for (int i=0;i<V[u].size();i++){
        int v = V[u][i];
        if (v==fa)continue;

        for (int i=0;i<m;i++) dp[v][i]=dp[u][i]+a[v];
        dfs(v,u,m-1);
        for (int i=1;i<=m;i++) dp[u][i]=max(dp[u][i],dp[v][i-1]);
    }
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)scanf("%d",&a[i]);
    for (int i=1;i<=n;i++){
        int x,y;scanf("%d%d",&x,&y);
        V[x].push_back(y);
        V[y].push_back(x);
    }

    dfs(0,-1,m);

    printf("%d\n",dp[0][m]);
    return 0;
}
