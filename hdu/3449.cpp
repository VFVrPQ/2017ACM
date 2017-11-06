/*
    author : VFVrPQ
    problem : hdu3449,给n(<=50)个背包，每个背包pi价钱，有mi个物品，物品有两个属性pi价钱和vi价值。必须买了背包才能买背包内的物品，问给你w(m<=1e5)块钱，能达到的最大价值
    solve : 树形依赖背包,将背包看做pi价钱，0价值。再增加一个根节点，连向所有背包。直接套模板。
    time : 2017-11-06-22.07.35
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;
const int N = 1e5+10;

//#define DEBUG

int dp[3][N];
int p[600],val[600];
int cnt;
vector<int>V[600];

int add(int pp,int vv){
    p[cnt]=pp;val[cnt]=vv;V[cnt].clear();
    return cnt++;
}
//因为开600MLE，直接按深度开数组
void dfs(int u,int w,int dep){
    if (w<=0)return ;
    //assert(dep<3);
    for (int i=0;i<V[u].size();i++){
        //assert(dep<2);
        int v=V[u][i];

        for (int j=0;j<=w-p[v];j++) dp[dep+1][j]=dp[dep][j]+val[v];//dp[v][j]=dp[u][j]+val[v]
        dfs(v,w-p[v],dep+1);
        for (int j=p[v];j<=w;j++) dp[dep][j]=max(dp[dep][j],dp[dep+1][j-p[v]]);//dp[u][j]=max(dp[u][j],dp[v][j-p[v]])
    }
}
int main(){
    #ifdef DEBUG
        freopen("1.txt","r",stdin);
    #endif // DEBUG
    int n,w;
    while (scanf("%d%d",&n,&w)!=EOF){
        cnt=0;
        add(0,0);
        for (int i=0;i<n;i++){
            int p,m;scanf("%d%d",&p,&m);
            int u = add(p,0);
            V[0].push_back(u);

            for (int j=0;j<m;j++){
                int p,val;scanf("%d%d",&p,&val);

                int v = add(p,val);
                V[u].push_back(v);
            }
        }

        for (int j=0;j<3;j++)
            for (int i=0;i<=w;i++) dp[j][i]=0;
        dfs(0,w,0);
        printf("%d\n",dp[0][w]);
    }

    return 0;
}
