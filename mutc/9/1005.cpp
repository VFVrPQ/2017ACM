/*
author : VFVrPQ
problem : 2017MUTC9-1005
solve :
Time :
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int M = 1e9+7;

const int N = 1000+10;

int sta[N],h;
int vis[N];
int col,belong[N];
int Time,low[N],dfn[N];
int d[N];
vector<int>V[N],W[N];
int n,m;
void tarjan(int u){
    Time++;low[u]=dfn[u]=Time;
    sta[h++]=u;
    vis[u]=1;
    for (auto v:V[u]){
        if (!dfn[v]) tarjan(v);

        if (vis[v]>=0) low[u] = min(low[u],low[v]);
    }
    if (low[u]==dfn[u]){
        while (1){
            vis[ sta[h-1] ] =-1;
            belong[ sta[h-1] ] = col;
            h--;
            if (sta[h]==u) break;
        }
        col++;
    }
}
int h2,Q[N];
int main(){
    //freopen("1.txt","r",stdin);
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;i++) V[i].clear();
        for (int i=0;i<m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            u--;v--;
            V[u].push_back(v);
        }

        Time=0;
        for (int i=0;i<n;i++) dfn[i]=low[i]=0;
        memset(vis,0,sizeof vis);
        h=0;col=0;
        for (int i=0;i<n;i++) if (!dfn[i])tarjan(i);


        //printf("%d\n",n);
        //for (int i=0;i<n;i++) printf("%d:%d\n",i,belong[i]);

        for (int i=0;i<col;i++) W[i].clear();
        for (int i=0;i<n;i++){
            for (auto v:V[i]){
                if (belong[i]==belong[v])continue;
                W[ belong[i] ].push_back(belong[v]);
            }
        }
        memset(d,0,sizeof d);
        for (int i=0;i<col;i++){
            sort(W[i].begin(),W[i].end());
            W[i].erase( unique(W[i].begin(),W[i].end()), W[i].end());

            for (int v:W[i]){
                d[v]++;
            }
        }
        h2=0;int t2=0;
        for (int i=0;i<col;i++)
            if (d[i]==0){
                Q[t2++]=i;
            }
        //不懂~~~同一个u不能指向独立的两个数
        if (t2!=1) puts("Light my fire!");else{
            int flag=0;
            while (h2<t2){
                int u = Q[h2++];
                int cnt=0;
                for (auto v:W[u]){
                    d[v]--;
                    if (d[v]==0){
                        cnt++;
                        Q[t2++]=v;
                        if (cnt>=2){
                            flag=1;
                            break;
                        }
                    }
                }
                if (flag)break;
            }
            if (flag) puts("Light my fire!");
            else puts("I love you my love and our love save us!");
        }
    }
    return 0;
}
