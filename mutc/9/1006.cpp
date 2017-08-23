/*
    author : VFVrPQ
    problem : 2017MUTC9-1006
    solve :  枚举二进制位，把当前为0的和当前为1的分成两个集合,求一次最短路
    time : 2017-08-23-18.04.34
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5+10;
const int M = 1e9+7;
const LL INF = 1LL<<60;

vector< pair<int,int> > V[N];

int n,m;
LL d[N];
int vis[N];
int K;
int a[N];
int S,T;
LL dijkstra(int S,int T)
{
    //printf("T=%d\n",T);
    for (int i=0;i<n+2;i++) d[i]=INF,vis[i]=0;

    priority_queue< pair<LL,int> > Q;

    d[S]=0;
    Q.emplace(0LL,S);

    while (!Q.empty()){
        int u = Q.top().second; Q.pop();

        if (vis[u])continue;
        vis[u]=1;

        for (auto pa:V[u]){
            if (d[pa.first]>d[u]+pa.second){
                d[pa.first]=d[u]+pa.second;
                if (!vis[pa.first]){
                    Q.emplace(-d[pa.first],pa.first);
                }
            }
        }
    }

    //printf("%d,%d,d[T]=%lld\n",S,T,d[T]);
    return d[T];
}
void Delete(int T,int bit,int fz){
    for (int i=0;i<K;i++)if (!(a[i]>>bit&1^fz)){
        pair<int,int> x = make_pair(T,0);
        for (vector< pair<int,int> >::iterator it=V[a[i]].begin();it != V[a[i]].end();it++){
            if (*it == x) {
                    V[a[i]].erase(it);
                    break;
            }
        }
    }
}
int main()
{
    //freopen("1.txt","r",stdin);
    int Case;scanf("%d",&Case);
    for (int Ca=1;Ca<=Case;Ca++)
    {
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++)V[i].clear();
        for (int i=0;i<m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);u--;v--;
            V[u].emplace_back(v,w);
        }
        scanf("%d",&K);
        for (int i=0;i<K;i++) scanf("%d",&a[i]),a[i]--;

        S=n;T=n+1;
        LL ans=INF;
        for (int bit=20;bit>=0;bit--){
            for (int fz=0;fz<2;fz++){
                V[S].clear();
                V[T].clear();

                for (int i=0;i<K;i++)if ((a[i]>>bit&1)^fz){
                    V[S].emplace_back(a[i],0);
                }else{
                    V[a[i]].emplace_back(T,0);
                }
                if (V[S].size()==K || V[T].size()==K) {
                }else{
                    ans=min(ans,dijkstra(S,T));
                }
                //if (dijkstra(S,T)==0) printf("ans=0,bit=%d\n",bit);
                Delete(T,bit,fz);
            }
        }
        printf("Case #%d: %lld\n",Ca,ans);
    }
    return 0;
}
