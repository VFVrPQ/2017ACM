/*
    author : VFVrPQ
    problem : 2017MUTC10-1011 Two Paths
    solve : 找第二短的路（可以往返走）；显然最多往返走一次。答案是 有条边不在最短路里的最短路，或者是 最短路上的某条边*3
    time : 2017-08-24-17.29.30
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 100000+10;
const LL INF  = 1LL<<60;
LL d[N][2];
int last[N],mark[N];
priority_queue< pair<LL,int> > Q;
int vis[N];
int n,m;
vector<int> V[N];

struct Edges{
    int u,v,w;
    Edges(){}
    Edges(int u,int v,int w):u(u),v(v),w(w){}
};
Edges edges[N*2];
void dijkstra(int u,int b){
    for (int i=0;i<n;i++) d[i][b]=INF,vis[i]=0;

    d[u][b]=0;
    Q.emplace(0,u);
    while (!Q.empty()){
        int u = Q.top().second;Q.pop();
        if (vis[u])continue;
        vis[u]=1;

        for (auto index:V[u]){
            int v = edges[index].v;
            int w = edges[index].w;
            if (d[v][b]>d[u][b]+w){
                d[v][b]=d[u][b]+w;
                last[v] = index;
                Q.emplace(-d[v][b],v);
            }
        }
    }
}
int main()
{
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++)V[i].clear();

        int cnt=0;
        for (int i=0;i<m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);u--;v--;
            edges[cnt] = Edges(u,v,w); V[u].push_back(cnt); cnt++;
            edges[cnt] = Edges(v,u,w); V[v].push_back(cnt); cnt++;
        }
        dijkstra(n-1,1); dijkstra(0,0);

        memset(mark,0,sizeof mark);
        int u = n-1;
        while (u){
            mark[ last[u]/2 ] = 1;
            u = edges[ last[u] ].u;
        }

        LL ans = INF;
        for (int i=0;i<m*2;i+=2){
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (mark[i/2]){
                ans = min(ans, d[u][0]+d[v][1]+3LL*w);
                ans = min(ans, d[u][1]+d[v][0]+3LL*w);
            }else{
                ans = min(ans, d[u][0]+d[v][1]+w);
                ans = min(ans, d[u][1]+d[v][0]+w);
            }
        }
        //for (int i=0;i<n;i++) printf("%lld ",c[i]);puts("***");
        printf("%lld\n",ans);
    }
    return 0;
}
