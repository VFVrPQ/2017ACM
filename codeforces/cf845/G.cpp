#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e5+10;

vector<int>V[N];
vector<int>W[N];
int vis[N];
int dis[N];
int n,m;
int tot,h[N*10];
void dfs(int u)
{
    vis[u]=1;
    for (int i=0;i<V[u].size();i++){
        int v=V[u][i];
        int w=W[u][i];

        if (vis[v]){
                h[tot++]=dis[v]^dis[u]^w;
                continue;
        }
        dis[v]=dis[u]^w;
        dfs(v);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        V[u].push_back(v);
        V[v].push_back(u);
        W[u].push_back(w);
        W[v].push_back(w);
    }

    dfs(1);

    int ans=dis[n];
    for (int i=1<<30;i;i>>=1){
        int k=-1;
        for (int j=0;j<tot;j++)
        if (i&h[j]){
            if (k==-1) k=j;
            else       h[j]^=h[k];
        }
        if (k!=-1 && (ans&i)) ans^=h[k];
        h[k]=0;
    }
    printf("%d\n",ans);
    return 0;
}
