#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int M = 998244353;
const int N = 6e5 + 10;

vector<int> V[N];
vector<int> W[N];

queue<int> Q;

int n;
int b[N],d[N];
LL t[2];
int last;
void dfs(int u,int f){
    b[last=u]=1;
    for (int i=0;i<V[u].size();i++){
        int v=V[u][i];
        if (!b[v]){
                t[f]=t[f]*W[u][i]%M;
                dfs(v,f^1);
        }
    }
}
int main()
{
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);

        for (int i=1;i<=2*n;i++) V[i].clear(),W[i].clear(),d[i]=0;
        for (int i=1;i<=n;i++){
            int v1,w1,v2,w2;scanf("%d%d%d%d",&v1,&w1,&v2,&w2);
            V[i].push_back(v1+n);W[i].push_back(w1);
            V[i].push_back(v2+n);W[i].push_back(w2);

            V[v1+n].push_back(i);W[v1+n].push_back(w1);
            V[v2+n].push_back(i);W[v2+n].push_back(w2);

            d[v1+n]++;d[v2+n]++;
        }

        for (int i=1;i<=2*n;i++) b[i]=0;
        while (!Q.empty())Q.pop();
        for (int i=n+1;i<=n+n;i++)if (d[i]==1){
            Q.push(i);
        }

        LL ans=1;
        while (!Q.empty()){
            int u=Q.front();Q.pop();b[u]=1;
            for (int i=0;i<V[u].size();i++){
                int v=V[u][i];
                if (b[v])continue;
                b[v]=1;
                ans=ans*W[u][i]%M;

                d[V[v][0]]--;if (d[V[v][0]]==1)Q.push(V[v][0]);
                d[V[v][1]]--;if (d[V[v][1]]==1)Q.push(V[v][1]);
            }
        }

        for (int i=1;i<=n;i++)if (!b[i]){
            t[0]=t[1]=1;
            dfs(i,0);
            for (int j=0;j<V[i].size();j++)
                if (V[i][j]==last) t[1]=t[1]*W[i][j]%M;//
            ans=ans*(t[0]+t[1])%M;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
