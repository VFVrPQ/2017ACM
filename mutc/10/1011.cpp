/*
    author : VFVrPQ
    problem : 2017MUTC10-1011 Two Paths
    solve : 找第二短的路（可以往返走）；显然最多往返走一次。答案就是第二短简单路和往返走一次的最小值（但不懂为什么往返走一次都要dp）
    time : 2017-08-24-17.29.30
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 1e9+7;
const int N = 100000+10;
const LL INF  = 1LL<<60;
LL d[N][2];
LL aw[N];
priority_queue< pair<LL, pair<LL,int>  > > Q;
int vis[N];
int n,m;
vector< pair<int,int> > V[N];
LL c[N];//hui tui
void dijkstra(int u){
    for (int i=0;i<n;i++) d[i][0]=d[i][1]=INF,vis[i]=0;

    d[u][0]=0;
    Q.emplace(make_pair(0,make_pair(-INF,u)));
    while (!Q.empty()){
        int u = Q.top().second.second;Q.pop();
        if (vis[u])continue;
        vis[u]=1;

        for (auto pa:V[u]){
            int v = pa.first;
            int w = pa.second;
            if (d[v][0]>=d[u][0]+w){
                d[v][1]=d[v][0];
                d[v][0]=d[u][0]+w;
                if (d[v][1]>d[u][1]+w){
                    d[v][1]=d[u][1]+w;
                }
                Q.push(make_pair(-d[v][0],make_pair(-d[v][1],v)));
            }else{
                if (d[v][1]>d[u][0]+w){
                    d[v][1]=d[u][0]+w;
                    Q.push(make_pair(-d[v][0],make_pair(-d[v][1],v)));
                }
            }
        }
    }


    priority_queue< pair<LL,int> > Q;
    for (int i=0;i<n;i++)
    {
        c[i]=d[i][0]+2*aw[i], vis[i]=0;
        Q.emplace(-c[i],i);
    }

    while (!Q.empty()){
        int u = Q.top().second; Q.pop();

        for (auto pa:V[u]){
            int v = pa.first;
            int w = pa.second;
            if (c[v]>c[u]+w){
                c[v]=c[u]+w;
                Q.emplace(-c[v],v);
            }
        }
    }
}
int main()
{
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++)V[i].clear(),aw[i]=INF;
        for (int i=0;i<m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);u--;v--;
            V[u].emplace_back(v,w);
            V[v].emplace_back(u,w);
            aw[u]=min(aw[u],(LL)w);
            aw[v]=min(aw[v],(LL)w);
        }
        dijkstra(0);

        //for (int i=0;i<n;i++) printf("%lld ",c[i]);puts("***");
        printf("%lld\n",min(d[n-1][1],c[n-1]));
    }
    return 0;
}
