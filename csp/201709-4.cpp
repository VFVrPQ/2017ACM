#include<bits/stdc++.h>

using namespace std;

const int N = 1000+10;

vector<int> V[N];

int vis[N][N];//vis[I][j]=1表示从I出发能达到j；vis[I][j]表示从I出发不能到达j

void bfs(int st,int u){
    queue<int>Q;
    Q.push(u);
    vis[st][u]=1;
    while (!Q.empty()){
        u = Q.front(); Q.pop();
        for (int i=0;i<V[u].size();i++){
            int v=V[u][i];

            if (!vis[st][v]){
                vis[st][v]=1;
                Q.push(v);
            }
        }
    }
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        int u,v;scanf("%d%d",&u,&v);
        V[u].push_back(v);
    }
    memset(vis,0,sizeof vis);
    for (int i=1;i<=n;i++){
        bfs(i,i);
    }

    int ans=0;
    for (int j=1;j<=n;j++){
        int cnt=0;
        for (int i=1;i<=n;i++){
            cnt+=(vis[i][j]|vis[j][i]);
        }
        if (cnt==n) ans++;
    }
    cout<<ans<<endl;
    return 0;
}
