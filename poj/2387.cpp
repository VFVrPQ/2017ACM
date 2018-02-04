#include <stdio.h>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N=1000+10;
const int INF = 1e9+7;
int n,m;

int g[N][N];
int dist[N];
int vis[N];
void dijkstra(int u){
    for (int i=1;i<=n;i++){
            dist[i]=INF;
            vis[i]=0;
    }
    dist[1]=0;
    vis[1]=1;

    for (int i=1;i<=n;i++){
        int k=-1;
        for (int j=1;j<=n;j++)if (vis[j]==1){
            if (k==-1 || dist[k]>dist[j]) k=j;
        }
        if (k==-1) break;
        vis[k]=-1;
        for (int j=1;j<=n;j++) if (vis[j]>=0){
            if (dist[j]>dist[k]+g[j][k]){
                dist[j]=dist[k]+g[j][k];
                vis[j]=1;
            }
        }
    }
}
int main()
{
    while (scanf("%d%d",&m,&n)!=EOF){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                g[i][j]=INF;
            }
        }
        for (int i=0;i<m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);
            g[u][v]=g[v][u]=min(w,g[u][v]);
        }
        dijkstra(1);
        printf("%d\n",dist[n]);
    }
    return 0;
}
